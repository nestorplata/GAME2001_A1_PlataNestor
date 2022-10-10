#include <iostream>
#include "UnorderedArray.h";
using namespace std;

int main()
{
	//cout << "Bubble Sort Algorithm" << endl;
	//cout << "Selection Sort Algorithm" << endl;
	//cout << "Insertion Sort Algorithm" << endl;
	//cout << "Merge Sort Algorithm" << endl;

	UnorderedArray<int> array(5);
	array.push(80);
	array.push(64);
	array.push(99);
	array.push(76);
	array.push(5);




	cout << "Before Sorting: ";
	for (int i = 0; i < array.GetSize(); i++)
	{
		cout << " " << array[i];
	}
	cout << endl;

	// Call our sort
	array.BubbleSort();
	//array.SelectionSort();
	//array.InsertionSort();
	//array.MergeSort();

	cout << "After sorting: ";
	for (int i = 0; i < array.GetSize(); i++)
	{
		cout << " " << array[i];
	}

	cout << endl << endl;

	return 0;
}