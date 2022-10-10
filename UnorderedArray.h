#pragma once
#include <cassert>
#include "TemplateCustomArray.h"

template<class T>
class UnorderedArray : public TemplateCustomArray<T>
{
public:
	using TemplateCustomArray<T>::SetSize;
	using TemplateCustomArray<T>::SetGrowSize;
	using TemplateCustomArray<T>::SetMaxSize;
	using TemplateCustomArray<T>::SetM_array;
	using TemplateCustomArray<T>::GetSize;
	using TemplateCustomArray<T>::GetMaxSize;
	using TemplateCustomArray<T>::GetGrowSize;
	using TemplateCustomArray<T>::GetM_array;
	using TemplateCustomArray<T>::ArrayValue;
	using TemplateCustomArray<T>::Expand;


	UnorderedArray(int size, int growBy = 1)
	{
		SetM_array(NULL);
		SetMaxSize(0);
		SetGrowSize(0);
		SetSize(0);

		if (size)	// Is this a legal size for an array?
		{
			SetMaxSize(size);
			SetM_array(new T[GetMaxSize()]);		// Dynamically allocating an array to m_maxSize
			memset(GetM_array(), 0, sizeof(T) * GetMaxSize());	// Explicitly set 0 to all elements in the array

			SetGrowSize(((growBy > 0) ? growBy : 0));
		}
	}
	// Insertion
	// Fast insertion for UnorderedArray -- Big-O is O(1)
	void push(T val)
	{
		assert(GetM_array() != nullptr); // Debugging purposes

		if (GetSize() >= GetMaxSize())	// Check if the array has to expand to accommodate the new data.
		{
			Expand();
		}

		// My array has space for a new value. Let's add it!
		GetM_array()[GetSize()] = val;
		SetSize(GetSize() + 1);
	}

	int search(T val)
	{
		assert(GetM_array() != nullptr);

		// Brute-force Search
		for (int i = 0; i < GetSize(); i++)
		{
			if (GetM_array()[i] == val)
			{
				return i;	// Return the index of where the item is located in the array
			}
		}

		return -1;
	}

	void BubbleSort()
	{
		assert(GetM_array() != nullptr);

		T temp;

		// Start at the end of the array and move backwards
		for (int k = GetSize() - 1; k > 0; k--)
		{
			for (int i = 0; i < k; i++)	 // Compare elements until k is reached
			{
				// Compare 2 adjacent elements
				if (GetM_array()[i] > GetM_array()[i + 1])
				{
					// Swap the elements
					temp = GetM_array()[i];
					ArrayValue(i,GetM_array()[i + 1]);
					ArrayValue(i + 1, temp);
				}
			}
		}
	}

	void SelectionSort()
	{
		assert(GetM_array() != nullptr);

		T temp;	// Swapping
		int min = 0;	// Hold the index of the current smallest value

		// The lowest position to swap elements into
		for (int k = 0; k < GetSize(); k++)
		{
			min = k;	// Set the value at index k as a "default" minimum value

			// Iterate through the array to find smallest value, if there is one.
			for (int i = k + 1; i < GetSize(); i++)
			{
				// Compare the value at the current index vs the current "min" index
				if (GetM_array()[i] < GetM_array()[min])
				{
					// Store the index to the smallest element
					min = i;
				}
			}

			// Swap the lowest element with the lowest available index
			if (GetM_array()[k] > GetM_array()[min])
			{
				// Swap
				temp = GetM_array()[k];
				ArrayValue(k, GetM_array()[min]);
				ArrayValue(min, temp);
			}
		}
	}

	void InsertionSort()
	{
		assert(GetM_array() != nullptr);

		T temp;
		int i = 0;

		// Iterate through all elements to be sorted starting with index of 1, increasing as more of the array is sorted
		for (int k = 1; k < GetSize(); k++)
		{
			temp = GetM_array()[k];
			i = k;

			// Shifting of elements if necessary. Create a space for an elements
			// to be inserted in the correct location.
			while (i > 0 && GetM_array()[i - 1] >= temp) //compare temp value with previous index, if prev is larger then stop
			{
				// Push elements to the right
				ArrayValue(i,GetM_array()[i - 1]);
				i--;
			}

			// Place the item in temp into the correct location found by the last loop (i)
			ArrayValue(i, temp);
		}
	}

	void MergeSort()
	{
		assert(GetM_array() != nullptr);

		T* tempArray = new T[GetSize()]; //create the temparray needed for mergesort
		assert(tempArray != nullptr);

		MergeSort(tempArray, 0, GetSize() - 1);
		delete[] tempArray;
	}

private:
	void MergeSort(T* tempArray, int lowerBound, int upperBound)
	{
		// Base case, if lowerbound=upperbound then there is only 1 element left
		if (lowerBound == upperBound)
		{
			return;
		}

		// Determine the middle of the array
		int mid = (lowerBound + upperBound) >> 1;

		MergeSort(tempArray, lowerBound, mid);	// Mergesort the lower half of the array recursively
		MergeSort(tempArray, mid + 1, upperBound); // Mergesort the upper half of the array recursively

		// Merge by using the temparray, compare values and place sorted pieces back into m_array
		Merge(tempArray, lowerBound, mid + 1, upperBound);
	}
	void Merge(T* tempArray, int low, int mid, int upper)
	{
		// passed in values: lowerbound, Mid+1, Upperbound
		int tempLow = low, tempMid = mid - 1;
		int index = 0;

		// comparing 2 sections of the split array, which of the 2 values is smaller? move it into the temp array
		while (low <= tempMid && mid <= upper)
		{
			if (GetM_array()[low] < GetM_array()[mid])
			{
				tempArray[index++] = GetM_array()[low++];	// Left half lower value is the lowest, put it in temparray, increment
			}
			else
			{
				tempArray[index++] = GetM_array()[mid++];	// Right half lower value is the lowest, put it in temparray, increment
			}
		}

		//clean up remaining values
		while (low <= tempMid) // Clean up lower half, putting in the remaining values into temparray
		{
			tempArray[index++] = GetM_array()[low++];
		}
		while (mid <= upper) // Clean up upper half, putting in the remaining values into temparray
		{
			tempArray[index++] = GetM_array()[mid++];
		}

		// Place the stored tempArray into the main array in the correct locations
		for (int i = 0; i < upper - tempLow + 1; i++)
		{
			ArrayValue(tempLow + i,  tempArray[i]);
		}
	}


};