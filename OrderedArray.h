#pragma once
#include <cassert>

#include "TemplateCustomArray.h"

template<class T>
class OrderedArray : public TemplateCustomArray<T>
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
	using TemplateCustomArray<T>::Expand;


	OrderedArray(int size, int growBy = 1)
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

	void push(T val)
	{
		bool is_repeated = false;
		for (int j = 0; j < GetSize(); j++)
		{
			if (GetM_array()[j] == val)
			{
				is_repeated = true;
			}
		}
		if (!is_repeated)
		{
			assert(GetM_array() != nullptr);

			if (GetSize() >= GetMaxSize())
			{
				Expand();
			}

			int i, k;	// i - Index to be inserted. k - Used for shifting purposes
			// Step 1: Find the index to insert val
			for (i = 0; i < GetSize(); i++)
			{
				if (GetM_array()[i] > val)
				{
					break;
				}
			}

			// Step 2: Shift everything to the right of the index(i) forward by one. Work backwards
			for (k = GetSize(); k > i; k--)
			{
				GetM_array()[k] = GetM_array()[k - 1];
			}

			// Step 3: Insert val into the array at index
			GetM_array()[i] = val;

			SetSize(GetSize() + 1);
		}


		// return i;
	}



	int search(T searchKey1)
	{
		// Call to binary search recursive function
		// Binary Search: searchKey, initial lowerBound, initial upperBound
		return binarySearch(searchKey1, 0, GetSize() - 1);
	}

	//Non binary

	int search2(T searchKey)
	{
		assert(GetM_array() != nullptr);

		// Helper variables.
		int lowerBound = 0;
		int upperBound = GetSize() - 1;
		int current = 0;

		while (1)	// <-- Replaced with recursion
		{
			current = (lowerBound + upperBound) >> 1;	//bitwise operation; divides by 2

			// Binary search steps:
			// Step 1: Check if the middle is the value we are looking for.
			if (GetM_array()[current] == searchKey)
			{
				// Found the item in the middle of the array. Return the index
				return current;
			}
			// Step 2: Check that we've exhausted all options. Can't find the item
			else if (lowerBound > upperBound)
			{
				return -1;
			}
			// Step 3: Check which half of the array the value is in.
			else
			{
				if (GetM_array()[current] < searchKey)
				{
					lowerBound = current + 1;	// Value may be in the upper half
				}
				else
				{
					upperBound = current - 1;	// Value may be in the lower half
				}
			}
		}

		return -1;	// Catch all return from danger.
	} 

	int binarySearch(T searchKey, int lowerBound, int upperBound)
	{
		assert(GetM_array() != nullptr);
		assert(lowerBound >= 0);
		assert(upperBound < GetSize());

		// Bitwise divide by 2
		int current = (lowerBound + upperBound) >> 1;

		// Check 1 "Base case": Did we find the searchKey at the current index?
		if (GetM_array()[current] == searchKey)
		{
			// We found it! Return the index
			return current;
		}
		// Check 2 "Base base": Are we done searching? 
		else if (lowerBound > upperBound)
		{
			// Did not find searchKey within m_array
			return -1;
		}
		// Check 3: Which half of the array is searchKey in?
		else
		{
			if (GetM_array()[current] < searchKey)
			{
				// Search the upper half of the array
				return binarySearch(searchKey, current + 1, upperBound);
			}
			else
			{
				// Search the lower half of the array
				return binarySearch(searchKey, lowerBound, current - 1);
			}
		}

		return -1;
	}
};