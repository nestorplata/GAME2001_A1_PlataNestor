#include <iostream>
//#include "UnorderedArray.h"
#include "OrderedArray.h"

using namespace std;

int main()
{
	OrderedArray<int> array(3);

	array.push(3);
	array.push(3);
	array.push(53);
	array.push(53);
	array.push(83);
	array.push(83);
	array.push(82);
	array.push(82);
	array.push(23);
	array.push(23);
	// 3, 23, 53, 82, 83
	// 3, 23, 112, 82, 83
	array.pop();
	//// 3, 23, 112, 82
	array.remove(2);
	// 3, 23, 82
	cout << "Ordered array contents: ";

	for (int i = 0; i < array.GetSize(); i++)
	{
		cout << array[i] << " ";
	}

	cout << endl;


	cout << "Serach for 53 was found at index: ";
	cout << array.search(53) << endl; // -1
	cout << "Serach for 23 was found at index: ";
	cout << array.search(23) << endl; // 1
}