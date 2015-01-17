#include "p1a.h"

using namespace std;

void P1a::printSize()const
{
	cout << "The size of class P1a is " << sizeof(*this) << endl;
}

void P1a::printStaticArraySize()const
{
	P1a arr1b_1[5];
	
	cout << "============== " << endl;
	cout << "Address of arr1b_1[5] are: "  <<endl;
	cout << "&arr1b_1[0]: " << &arr1b_1[0] <<endl;
	cout << "&arr1b_1[1]: " << &arr1b_1[1] <<endl;
	cout << "&arr1b_1[2]: " << &arr1b_1[2] <<endl;
	cout << "&arr1b_1[3]: " << &arr1b_1[3] <<endl;
	cout << "&arr1b_1[4]: " << &arr1b_1[4] <<endl;
}
void P1a::printDynamicArraySize()const
{
	P1a* arr1b_2 = new P1a[5];
	
	cout << "============== " << endl;
    cout << "Address of arr1b_2[5] are: "  <<endl;
    cout << "&arr1b_2[0]: " << &arr1b_2[0] <<endl;
    cout << "&arr1b_2[1]: " << &arr1b_2[1] <<endl;
    cout << "&arr1b_2[2]: " << &arr1b_2[2] <<endl;
    cout << "&arr1b_2[3]: " << &arr1b_2[3] <<endl;
    cout << "&arr1b_2[4]: " << &arr1b_2[4] <<endl;
	cout << "&arr1b_2:  " << &arr1b_2 << endl;
}
void P1a::printPointerArraySize()const
{
	P1a** arr1b_3 = new P1a*[5];
	for(size_t i=0;i<5;++i)
		arr1b_3[i] = new P1a;

	cout << "============== " << endl;
	cout << "Address of arr1b_3[5] are: "  <<endl;
	cout << "&arr1b_3[0]: " << &arr1b_3[0] <<endl;
	cout << "&arr1b_3[1]: " << &arr1b_3[1] <<endl;
	cout << "&arr1b_3[2]: " << &arr1b_3[2] <<endl;
	cout << "&arr1b_3[3]: " << &arr1b_3[3] <<endl;
	cout << "&arr1b_3[4]: " << &arr1b_3[4] <<endl;

	cout << "Contents of arr1b_3[5] are: "  <<endl;
	cout << "arr1b_3[0]: " << arr1b_3[0] <<endl;
	cout << "arr1b_3[1]: " << arr1b_3[1] <<endl;
	cout << "arr1b_3[2]: " << arr1b_3[2] <<endl;
	cout << "arr1b_3[3]: " << arr1b_3[3] <<endl;
	cout << "arr1b_3[4]: " << arr1b_3[4] <<endl;
	cout << "&arr1b_3:  " << &arr1b_3 << endl;
}
