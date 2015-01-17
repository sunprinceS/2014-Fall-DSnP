/****************************************************************************
  FileName     [ util.h ]
  PackageName  [ util ]
  Synopsis     [ Define the prototypes of the exported utility functions ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2007-2014 LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/
#ifndef UTIL_H
#define UTIL_H

#include <istream>

using namespace std;

// In myString.cpp
extern int myStrNCmp(const string& s1, const string& s2, unsigned n);
extern size_t myStrGetTok(const string& str, string& tok, size_t pos = 0,
                          const char del = ' ');
extern bool myStr2Int(const string& str,int& num);
extern bool myStr2Int(const string& str, int& num,const int base);
extern bool isValidVarName(const string& str);
extern bool isValidNum(const string& str,const int base=10);
extern bool baseConvert(int num,string& result,const int base=10);

// In myGetChar.cpp
extern char myGetChar(istream&);
extern char myGetChar();


#endif // UTIL_H
