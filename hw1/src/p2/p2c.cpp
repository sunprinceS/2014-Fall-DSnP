#include<iostream>
#include<vector>

using namespace std;

template<class T>
class Compare
{ 
public:
	virtual bool operator()(const T& a,const T& b)const =0;
};

template<class T>
class Less:public Compare<T>
{
public:
	virtual	bool operator()(const T& a,const T& b)const {return a<b; }
};

template<class T>
class Greater:public Compare<T>
{
public:
	virtual	bool operator()(const T& a,const T& b)const {return a>b; }
};

template<class T>
void mySwap(T& a,T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

template <class T>
void selectionSort(vector<T>& array,const Compare<T>& compare)
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
	int strArrSize,doubleArrSize;

	cout << "How many strings? ";
	cin >> strArrSize;
	
	vector<string> strArr(strArrSize);
	for (int i = 0; i<strArrSize; ++i) {
		cin >> strArr[i];	
	}
	cout << "Before sort:" << endl;
	for (int i = 0; i < strArrSize; ++i) {
		cout << strArr[i] << " ";
	}
	cout << endl;

	selectionSort(strArr,Less<string>());
	cout << "Ascending sort:" << endl;
	for (int i = 0; i < strArrSize; ++i) {
		cout << strArr[i] << " ";
	}
	cout << endl <<endl;
	

	cout << "How many doubles?";
	cin >> doubleArrSize;
	vector<double> doubleArr(doubleArrSize);
	for (int i = 0; i<doubleArrSize; ++i) {
		cin >> doubleArr[i];	
	}
	cout << "Before sort:" << endl;
	for (int i = 0; i < doubleArrSize; ++i) {
		cout << doubleArr[i] << " ";
	}
	cout << endl;

	selectionSort(doubleArr,Greater<double>());
	cout << "Descending sort:" << endl;
	for (int i = 0; i < doubleArrSize; ++i) {
		cout << doubleArr[i] << " ";
	}
	cout << endl;
	return 0;
}

