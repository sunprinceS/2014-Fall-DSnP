/****************************************************************************
  FileName     [ p3.amgr.cpp ]
  PackageName  [ HW1 ]
  Synopsis     [ For problem 3 of HW1 in DSnP class ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2014 DVLab, GIEE, NTU, Taiwan ]
****************************************************************************/

#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include "p3.amgr.h"

using namespace std;

unsigned A::_count=0;

// TODO: Implement class A's constructors and desctructor
A::A()
{
	this->_data = "";
	++_count;
}
A::A(const string& s)
{
	this->_data = s;
	++_count;
}
A::~A()
{
	this->_data.clear();
	--_count;
}

void AMgr::cleanAll()
{
   // TODO: clean up all the data in AMgr::_amap and AMgr::_alist
	_amap.clear();
	_alist.clear();
}

// If _amap or _alist is not empty, it will be cleaned anyway.
void AMgr::import(ifstream& inf)
{
   if (!checkEmpty()) {
      cout << "Warning: Database is not empty. Erasing..."; cout.flush();
      cleanAll();
      cout << " done." << endl;
   }

   #define BUF_LEN 65536
   char buf[BUF_LEN];
   unsigned lineNo = 0;
   do {
      // Read one line at a time, and parse this line into string tokens
      // The parsed string tokens are stored in vector<string> strs
      inf.getline(buf, BUF_LEN);
      stringstream ss((string(buf)));
      istream_iterator<string> bb(ss);
      istream_iterator<string> ee;//eof
      vector<string> strs(bb, ee);
	  /*range constructor
	  Constructs a container with as many elements as the range [first,last),
	  with each element constructed from its corresponding element in that range, 
	  in the same order.*/

      // Store the parsed string tokens to both _amap and _alist
      for (size_t i = 0, s = strs.size(); i < s; ++i) {
         newEntry(strs[i], lineNo, i);
      }

      lineNo++;
   } while (!inf.eof());
}

// TODO:
// 1. Check is there is already an entry (str, A*) in _amap
// 2. If not, create a new A*, map (str, A*), and store this A* to _alist
// 3. Record the (lineNo, wordNo) to A::_occurence
void AMgr::newEntry(const string& str, unsigned lineNo, unsigned wordNo)
{
	bool withoutKey=true;
	for(AMap::const_iterator iter=this->_amap.begin();iter!=_amap.end();++iter)
	{
		if(iter->first == str)
		{
			withoutKey = false;
			/*record the occurrence*/
			iter->second->addOccurence(lineNo,wordNo);
			break;
		}
	}
	if(withoutKey)
	{
		A* newelement = new A(str);
		newelement->addOccurence(lineNo,wordNo);
		this->_amap.insert(AMap::value_type(str,newelement));
		_alist.push_back(newelement);
	}
}

// TODO: Implement the ostream& operator<< for AMgr and A.
// A sample input/output can be found at p3.in and p3.out.ref
// 
ostream& operator << (ostream& os, const AMgr& am)
{
	cout << "Total distinct words: " << am._alist.size() << endl;
	for(unsigned int i=0;i<am._alist.size();++i)
	{
		os << "[" << i << "] "; 
		os << *(am._alist[i]) << endl << endl;
	}
	return os;
}

ostream& operator << (ostream& os, const A& a)
{
	cout << a._data << endl;
	for(unsigned int i=0;i<a._occurence.size();++i)
	{
		os <<"( " << (a._occurence[i]).first <<", " << a._occurence[i].second <<" )" << "\t";
	}
	return os;
}

