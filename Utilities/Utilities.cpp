///////////////////////////////////////////////////////////////////////////////////////
// Utilities.cpp - Provide small set of utility functions                            //
//                                                                                   //
// Application:   Project #1, CSE687 - Object Oriented Design, Spring 2014           //
// Platform:      Dell XPS 2720, Win 8.1, Visual Studio 2013                         //
// Author:        Jim Fawcett, CST 4-187, Syracuse University                        //
//                (315) 443-3948, jfawcett@twcny.rr.com                              //
///////////////////////////////////////////////////////////////////////////////////////

#define IN_DLL  // don't use this define in files that use Utilities
#include "Utilities.h"
#include <iostream>

void title(const std::string& title, char underline)
{
  std::cout << "\n  " << title;
  std::cout << "\n " << std::string(title.size() + 2, underline);
}

#ifdef TEST_UTILITIES

void main()
{
  title("this is a title");
}

#endif
