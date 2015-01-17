#include<iostream>
#include<vector>

using namespace std;

class Compare
{
public:
	virtual bool operator()(const int& a,const int& b)const =0;
};

class Less:public Compare
{
public:
	virtual	bool operator()(const int& a,const int& b)const {return a<b; }
}
;
class Greater:public Compare
{
public:
	virtual bool operator()(const int& a,const int& b)const {return a>b; }
};

void mySwap(int&,int&);
void selectionSort(vector<int>& array,const Compare& compare)
{ 
	for (size_t i = 0, n = array.size(); i < n - 1; ++i) {
		size_t pivot = i;
		for (size_t j = i+1; j < n; ++j) {
			if (!compare(array[pivot], array[j]))
				pivot = j;
		}
		if (pivot != i)
			mySwap(array[pivot], array[i]);
	}
}

int main()
{  
	int arrSize;
	cout << "How many numbers? ";
	cin >> arrSize;
	
	vector<int> arr(arrSize);
	vector<int> arrA(arrSize);
	vector<int> arrD(arrSize);
	for (int i = 0; i<arrSize; ++i) {
		cin >> arr[i];	
	}
	arrA = arrD = arr;
	cout << "Before sort:" << endl;
	for (int i = 0; i < arrSize; ++i) {
		cout << arr[i] << "  ";
	}
	cout << endl;

	selectionSort(arrA,Less());
	cout << "Ascending sort:" << endl;
	for (int i = 0; i < arrSize; ++i) {
		cout << arrA[i] << "  ";
	}
	cout << endl;

	selectionSort(arrD,Greater());
	cout << "Descending sort:" << endl;
	for (int i = 0; i < arrSize; ++i) {
		cout << arrD[i] << "  ";
	}
	cout << endl;
	return 0;
}

void mySwap(int& a,int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}
