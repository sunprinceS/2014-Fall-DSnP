#include<iostream>
#include<vector>

using namespace std;

void mySwap(int&,int&);
bool compare(const int&,const int&);
void selectionSort(vector<int>& array)
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
	for (int i = 0; i<arrSize; ++i) {
		cin >> arr[i];	
	}

	cout << "Before sort:" << endl;
	for (int i = 0; i < arrSize; ++i) {
		cout << arr[i] << "  ";
	}
	cout << endl;

	selectionSort(arr);
	cout << "After sort:" << endl;
	for (int i = 0; i < arrSize; ++i) {
		cout << arr[i] << "  ";
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
bool compare(const int& a,const int& b)
{
	if(a<b)
		return 1;
	else
		return 0;
}
