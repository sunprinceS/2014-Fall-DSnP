/****************************************************************************
  FileName     [ calcGNum.cpp ]
  PackageName  [ calc ]
  Synopsis     [ Define member functions for class GNum ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2007-2014 LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/
#include <iostream>
#include <ctype.h>
#include <cassert>
#include "util.h"
#include "calcGNum.h"

using namespace std;
// TODO: Initialize the static data members of class GNum
//       (Note: let default _base = 10)
// TODO: Define the member functions of class GNum

ostream& operator << (ostream& os, const GNum& n)
{ 
	string result;
	if(baseConvert(n._num,result,n._base))
 	{
		cout << '#' << result;
	}
	else
	{
		cerr << "ERROR occur in baseConvert" << endl;
		exit(-1);
	}
   return os;
}
int GNum::_base = 10;
CalcMap GNum::_varMap;
