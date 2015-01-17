/****************************************************************************
  FileName     [ myString.cpp ]
  PackageName  [ util ]
  Synopsis     [ Customized string processing functions ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2007-2014 LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/
#include <string>
#include <ctype.h>
#include <cstring>
#include <cassert>
#include <iostream>
#include <cstdlib>

using namespace std;

// 1. strlen(s1) must >= n
// 2. The first n characters of s2 are mandatory, they must be case-
//    insensitively compared to s1. Return less or greater than 0 if unequal.
// 3. The rest of s2 are optional. Return 0 if EOF of s2 is encountered.
//    Otherwise, perform case-insensitive comparison until non-equal result
//    presents.
//
int
myStrNCmp(const string& s1, const string& s2, unsigned n)
{
   assert(n > 0);
   unsigned n2 = s2.size();
   if (n2 == 0) {return -1;}
   unsigned n1 = s1.size(); 
   assert(n1 >= n);
   for (unsigned i = 0; i < n1; ++i) {
      if (i == n2) {return (i < n)? 1 : 0;}
      char ch1 = (isupper(s1[i]))? tolower(s1[i]) : s1[i];
      char ch2 = (isupper(s2[i]))? tolower(s2[i]) : s2[i];
      if (ch1 != ch2)
	  {return (ch1 - ch2);}
   }
   return (n1-n2);
}


// Parse the string "str" for the token "tok", beginning at position "pos",
// with delimiter "del". The leading "del" will be skipped.
// Return "string::npos" if not found. Return the past to the end of "tok"
// (i.e. "del" or string::npos) if found.
//
size_t
myStrGetTok(const string& str, string& tok, size_t pos = 0,
            const char del = ' ')
{
   size_t begin = str.find_first_not_of(del, pos);
   if (begin == string::npos) { tok = ""; return begin; }
   size_t end = str.find_first_of(del, begin);
   tok = str.substr(begin, end - begin);
   return end;
}

// Convert string "str" to integer "num". Return false if str does not appear
// to be a number
bool
myStr2Int(const string& str, int& num)
{
   num = 0;
   size_t i = 0;
   int sign = 1;
   if (str[0] == '-') { sign = -1; i = 1; }
   bool valid = false;
   for (; i < str.size(); ++i) {
      if (isdigit(str[i])) {
         num *= 10;
         num += int(str[i] - '0');
         valid = true;
      }
      else return false;
   }
   num *= sign;
   return valid;
}


bool
myStr2Int(const string& str, int& num,const int base)
{
   num = 0;
   size_t i = 0;
   int sign = 1;
   //str[0] is '#'
   if (str[1] == '-') { sign = -1; i = 2; }
   else {i=1;}
   bool valid = false;
   for (; i < str.size(); ++i) {
      if (isdigit(str[i])) {
         num *= base;
         num += int(str[i] - '0');
         valid = true;
      }
	  // base >=11
	  else if(str[i]>=97 && str[i] <=122){
	  	  num*=base;
		  num += int(str[i] - 'a') +10;
		  valid = true;
	  }
      else return false;
   }
   num *= sign;
   return valid;
}
bool
baseConvert(int num,string& result,const int base)
{
	string tmp;
	if(num > 0)
	{
		if(base>=2 && base <= 10)
		{
			while(num!=0)
			{
				tmp.push_back(char((num % base)+48));
				num /= base;
			}
		}
		else if(base >=11 && base <=36)
		{
			while(num!=0)
			{
				short unit = num %base;
				if(unit >=0 && unit <=9)
				{
					tmp.push_back(char(unit+48));
				}
				else
				{
					tmp.push_back(char(unit+87));
				}
					num /= base;
			}
		}

	}
	else if(num < 0)
	{
		num *= -1; 
		if(base >=2 && base <=10)
		{
			while(num!=0)
			{
				tmp.push_back(char((num % base)+48));
				num /= base;
			}
		}
		else if(base >=11 && base <=36)
		{
			while(num!=0)
			{
				short unit = num %base;
				if(unit >=0 && unit <=9)
				{
					tmp.push_back(char(unit+48));
				}
				else
				{
					tmp.push_back(char(unit+87));
				}
				num /= base;
			}
		}
		tmp.push_back('-');
	}
	else{result.push_back('0');return true;}
	//reverse
	for(size_t i=0;i<tmp.size();++i)
	{
		result.push_back(tmp[tmp.size()-i-1]);
	}
	return true;
}

// Valid var name is ---
// 1. starts with [a-zA-Z_]
// 2. others, can only be [a-zA-Z0-9_]
// return false if not a var name
bool
isValidVarName(const string& str)
{
   size_t n = str.size();
   if (n == 0) return false;
   if (!isalpha(str[0]) && str[0] != '_')
      return false;
   for (size_t i = 1; i < n; ++i)
      if (!isalnum(str[i]) && str[i] != '_')
         return false;
   return true;
}
bool isValidNum(const string& str,const int base)
{
	//num prefix
   if(str[0]!='#'){return false;}
   
   
   bool validNum = true;
   char baseCh_10LB = '0'-1; 
   char baseCh_10UB = '9'+1;
   char baseChLB = 0;
   char baseChUB = 0;
   // above 2 will init later
   if(base>=2 && base <= 10)
   {
		baseCh_10UB = '0'+base; //'<base>'
   }
   else if(base >=11 && base <= 36)
   {
	    baseChLB = 'a'-1;
	    baseChUB = 'a'+(base-10);
   }
   else{ cerr << "Illegal base..." << endl; exit(-1); }
   // baseCh_10LB < ... < baseCh_10UB
   // baseChLB < ...< baseChUB
 
   //decide validNum
   
   int shift = (str[1] == '-')?1:0;
   for(size_t i =1+shift;i<str.size();++i )
   {
	   if(!((str[i]>baseCh_10LB && str[i]<baseCh_10UB)||(str[i]>baseChLB && str[i]<baseChUB)))
	   {
		   validNum =false ;
		   break;
	   }
   }
   return validNum;
}
