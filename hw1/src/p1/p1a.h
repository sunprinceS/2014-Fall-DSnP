#ifndef P1A_H
#define P1A_H
#include<iostream>
#include<string>

using namespace std;

class P1a
{
public:
	P1a(){};
	P1a(const string& s):_str(s) {};
	void assign(const string&);
	void print() const;
	P1a& append(const P1a&);
	void printSize()const;
	void printStaticArraySize()const;
	void printDynamicArraySize()const;
	void printPointerArraySize()const;
private:
	int	_dummy;
	string _str;
};
#endif
