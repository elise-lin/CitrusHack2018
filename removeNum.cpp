#include <iostream>
using namespace std;

int main() {
	int array [6] = {0,1,2,3,4,5};
	int size = 6;
	int deleteMe;
	
	//output array to see where we start
	for (int i = 0; i < size; ++i) {
		cout << array[i] << " ";
	}
	
	//ask user which element to delete
	cout << endl;
	cout << "Which element to delete: ";
	cin >> deleteMe;
	cout << endl;
	
	//shift deleteMe to the end of the array
	for(int i = deleteMe; i < size - 1; ++i) {
		array[i] = array[i+1];
	}
	
	//delete last element
	array[size-1] = 0;
	size = size-1;
	
	//output array
	for (int i = 0; i < size; ++i) {
		cout << array[i] << " ";
	}
	

	
	return 0;
}
