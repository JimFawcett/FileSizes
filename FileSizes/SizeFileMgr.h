#ifndef FILEMGR_H
#define FILEMGR_H
///////////////////////////////////////////////////////////////////////
// SizeFileMgr.h - Find sizes of files matching specified patterns   //
// Ver 1.1                                                           //
// Jim Fawcett, CSE687 - Object Oriented Design, Fall 2018           //
///////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * SizeFileMgr uses the services of FileSystem to find files and stores its findings
 * efficiently in DataStore.
 * - Finds all files, matching a set of patterns, along with their paths.
 * - Stores each fully qualified filename and size, using DataStore.
 *
 * Required Files:
 * ---------------
 * SizeFileMgr.h, SizeFileMgr.cpp
 * FileSystem.h, FileSystem.cpp,
 *
 * Maintenance History:
 * --------------------
 * Ver 1.1 : 10 Aug 2018
 * - added reverse display
 * - refactored code
 * Ver 1.0 : 09 Aug 2018
 * - first release
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>

class SizeFileMgr
{
public:
  using Path = std::string;
  using Pattern = std::string;
  using Patterns = std::vector<Pattern>;
  using File = std::string;
  using Size = size_t;
  using DataStore = std::multimap<Size, File, std::greater<Size>>;
  using const_iterator = DataStore::const_iterator;

  SizeFileMgr(const Path& path);
  bool changePath(const Path& path);
  void addPattern(const std::string& patt);
  void search();
  void find(const Path& path);
  const_iterator begin() { return store_.begin(); }
  const_iterator end() { return store_.end(); }
  void display();
  bool processCmdLine(int argc, char** argv);
  void recursive(bool recurse) { recursive_ = recurse; }
  bool isRecursive() { return recursive_; }
  void numFiles(size_t num) { numFiles_ = num; }
  size_t numFiles() { return numFiles_; }
private:
  void showProcessed();
  void forwardDisplay();
  void reverseDisplay();
  Path path_;
  Patterns patterns_;
  DataStore store_;
  bool recursive_ = false;
  size_t numFiles_ = 0;
  bool reverse_ = false;
  size_t largest_ = 0;
  size_t smallest_ = 100000000;
};

#endif
