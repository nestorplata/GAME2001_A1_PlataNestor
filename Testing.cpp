#include <iostream>
#include "OrderedArray.h"
#include "UnorderedArray.h";
using namespace std;

int main()
{
	OrderedArray<int> OrderedArray(3);

	OrderedArray.push(3);
	OrderedArray.push(3);
	OrderedArray.push(53);
	OrderedArray.push(53);
	OrderedArray.push(83);
	OrderedArray.push(83);
	OrderedArray.push(82);
	OrderedArray.push(82);
	OrderedArray.push(23);
	OrderedArray.push(23);
	// 3, 23, 53, 82, 83
	// 3, 23, 112, 82, 83
	OrderedArray.pop();
	//// 3, 23, 112, 82
	OrderedArray.remove(2);
	// 3, 23, 82
	cout << "Ordered array contents: ";

	for (int i = 0; i < OrderedArray.GetSize(); i++)
	{
		cout << OrderedArray[i] << " ";
	}

	cout << endl;


	cout << "Serach for 53 was found at index: ";
	cout << OrderedArray.search(53) << endl; // -1
	cout << "Serach for 23 was found at index: ";
	cout << OrderedArray.search(23) << endl; // 1

	//Unordered

	UnorderedArray<int> UnorderedArray(5);
	UnorderedArray.push(80);
	UnorderedArray.push(64);
	UnorderedArray.push(99);
	UnorderedArray.push(76);
	UnorderedArray.push(5);

	

	cout << std::endl << "Unordered Array Contents :"<< std::endl;
	cout << "Before Sorting: ";
	for (int i = 0; i < UnorderedArray.GetSize(); i++)
	{
		cout << " " << UnorderedArray[i];
	}
	cout << endl;

	// Call our sort

	//array.SelectionSort();
	//array.InsertionSort();
	//array.MergeSort();

	UnorderedArray.BubbleSort();
	cout << "After Bubble sorting: ";
	for (int i = 0; i < UnorderedArray.GetSize(); i++)
	{
		cout << " " << UnorderedArray[i];
	}

	UnorderedArray.MergeSort();
	cout << endl<<"After Merge sorting: ";
	for (int i = 0; i < UnorderedArray.GetSize(); i++)
	{
		cout << " " << UnorderedArray[i];
	}

	cout << endl << endl;

	return 0;
}