#include <iostream>
#include "p1a.h"
using namespace std;

void P1a::assign(const string& s)

{
	this->_str=s;
}
void P1a::print() const
{
	cout << this->_str << endl;
}
P1a& P1a::append(const P1a& p)
{
	this->_str+=p._str;
	return *this;
}
