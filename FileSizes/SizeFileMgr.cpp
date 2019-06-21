///////////////////////////////////////////////////////////////////////
// SizeFileMgr.cpp - Find sizes of files matching specified patterns //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Fall 2018           //
///////////////////////////////////////////////////////////////////////

#include "SizeFileMgr.h"
#include "FileSystem.h"
#define STATIC_LIB
#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <algorithm>

void usage()
{
  std::cout << "\n  usage: FileSizes path [/s] [pattern]* [numFiles]";
  std::cout << "\n    path = relative or absolute path of starting directory";
  std::cout << "\n    /s for recursive search";
  std::cout << "\n    pattern is a pattern string of the form *.h, *.log, etc.";
  std::cout << "\n    numFiles is the number of files displayed";
  std::cout << "\n  Example: FileSizes ../.. /s *.h *.cpp *.txt 25";
  std::cout << "\n";
}
bool SizeFileMgr::processCmdLine(int argc, char** argv)
{
  if (argc < 2)
  {
    usage();
    return false;
  }
  path_ = FileSystem::Path::getFullFileSpec(argv[1]);
  if (!FileSystem::Directory::exists(path_))
  {
    std::cout << "\n  " << path_ << " does not exist\n";
    return false;
  }
  std::cout << "\n  FileSizes";
  std::cout << "\n    " << path_;
  for (int i = 2; i < argc; ++i)
  {
    std::cout << ", " << argv[i];
    if (std::string(argv[i]) == "/s")
    {
      recursive_ = true;
    }
    else if (std::string(argv[i]) == "/r")
    {
      reverse_ = true;
    }
    else if (argv[i][0] == '/')
    {
      std::cout << "\n  unknown option";
    }
    else
    {
      size_t numFiles = atoi(argv[i]);
      if (numFiles == 0)
      {
        addPattern(argv[i]);
      }
      else
      {
        numFiles_ = numFiles;
      }
    }
  }
  std::cout << "\n";
  return true;
}

SizeFileMgr::SizeFileMgr(const Path& path = "") : path_(path)
{
  patterns_.push_back("*.*");
}

bool SizeFileMgr::changePath(const Path& path)
{
  if (FileSystem::Directory::exists(path))
  {
    path_ = path;
    return true;
  }
  return false;
}

void SizeFileMgr::addPattern(const std::string& patt)
{
  if (patterns_.size() == 1 && patterns_[0] == "*.*")
    patterns_.pop_back();
  patterns_.push_back(patt);
}

void SizeFileMgr::search()
{
  std::string fullPath = FileSystem::Path::getFullFileSpec(path_);
  if (recursive_)
    find(fullPath);
  else
  {
    for (auto patt : patterns_)
    {
      std::vector<std::string> files = FileSystem::Directory::getFiles(fullPath, patt);
      for (auto file : files)
      {
        std::string fileSpec = fullPath + "\\" + file;
        FileSystem::FileInfo fi(fileSpec);
        Size size = fi.size();
        if (size > largest_) largest_ = size;
        if (size < smallest_) smallest_ = size;
        std::pair<size_t, std::string> item = { size, fileSpec };
        store_.insert(item);
      }
    }
  }
}

void SizeFileMgr::find(const Path& path)
{
  for (auto patt : patterns_)
  {
    std::vector<std::string> files = FileSystem::Directory::getFiles(path, patt);
    for (auto f : files)
    {
      std::string fileSpec = path + "\\" + f;
      FileSystem::FileInfo fi(fileSpec);
      Size size = fi.size();
      if (size > largest_) largest_ = size;
      if (size < smallest_) smallest_ = size;
      std::pair<size_t, std::string> item = { size, fileSpec };
      store_.insert(item);
    }
  }
  std::vector<std::string> subdirs = FileSystem::Directory::getDirectories(path);
  for (auto d : subdirs)
  {
    if (d != "." && d != "..")
    {
      //std::cout << "\n  -- found dir: " << d;
      find(path + "\\" + d);
    }
  }
}

void SizeFileMgr::showProcessed()
{
  std::cout << "\n\n    Processed " << store_.size() << " files";
  size_t numDisplayed = std::min<size_t>(numFiles_, store_.size());
  if (numDisplayed == 0)
    numDisplayed = store_.size();
  std::cout << "\n    Displayed " << numDisplayed << " files";
  std::cout << "\n    largest size  = " << largest_;
  std::cout << "\n    smallest size = " << smallest_;
}
void SizeFileMgr::forwardDisplay()
{
  size_t count = 0;
  for (auto iter = store_.begin(); iter != store_.end(); ++iter)
  {
    ++count;
    if (count > numFiles_ && numFiles_ > 0)
      break;
    std::cout << "\n " << std::setw(15) << iter->first << " " << iter->second;
  }
  showProcessed();
  std::cout << "\n";
}

void SizeFileMgr::reverseDisplay()
{
  size_t count = 0;
  for (auto iter = store_.rbegin(); iter != store_.rend(); ++iter)
  {
    ++count;
    if (count > numFiles_ && numFiles_ > 0)
      break;
    std::cout << "\n " << std::setw(15) << iter->first << " " << iter->second;
  }
  showProcessed();
  std::cout << "\n";
}

void SizeFileMgr::display()
{
  if (reverse_)
    reverseDisplay();
  else
    forwardDisplay();
}



#ifdef TEST_SIZEFILEMGR

#include <map>
#include <iostream>
#include <functional>
#include "../Utilities/Utilities.h"

using Size = size_t;
using Path = std::string;
using File = std::string;

int main(int argc, char* argv[])
{
  SizeFileMgr fm;
  if (!fm.processCmdLine(argc, argv))
  {
    std::cout << "\n    command line parsing failed\n\n";
    return 1;
  }

  fm.search();
  fm.display();

  std::cout << "\n\n";
  return 0;
}

#endif
