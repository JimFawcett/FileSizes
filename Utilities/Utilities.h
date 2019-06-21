#ifndef UTILITIES_H
#define UTILITIES_H
///////////////////////////////////////////////////////////////////////////////////////
// Utilities.h - Provide small set of utility functions                              //
//                                                                                   //
// Application:   Project #1, CSE687 - Object Oriented Design, Spring 2014           //
// Platform:      Dell XPS 2720, Win 8.1, Visual Studio 2013                         //
// Author:        Jim Fawcett, CST 4-187, Syracuse University                        //
//                (315) 443-3948, jfawcett@twcny.rr.com                              //
///////////////////////////////////////////////////////////////////////////////////////
/* 
 * Package Operations:
 * -------------------
 * Utilities implements only one function - more are planned.  It is configured to
 * be packaged as either a DLL or a static library.
 *
 * Required Files:
 * ---------------
 * Utilities.h, Utilities.cpp
 * 
 * Build Process:
 * --------------
 * From the Visual Studio Developer's Command Prompt:
 * devenv VSHelp.sln /rebuild debug
 *
 * Maintenance History:
 * --------------------
 * -Ver 1.0 : 1 Mar 2015
 *  first release
 */
#include <string>

#ifdef IN_DLL
  #define DECL __declspec(dllexport)
#else
  #define DECL __declspec(dllimport)
#endif

#ifdef STATIC_LIB
  #pragma warning(disable : 4005)  // disable redefinition warning
  #define DECL                     // that's what we want to do
#endif

DECL void title(const std::string& title, char underline = '-');

#endif
