#pragma once
#include <cassert>

template<class T>
class TemplateCustomArray //unordered
{
public:
	TemplateCustomArray()= default;
	// Constructor
	TemplateCustomArray(int size, int growBy = 1) :
		m_array(NULL), m_maxSize(0), m_growSize(0), m_numElements(0)
	{
		if (size)	// Is this a legal size for an array?
		{
			m_maxSize = size;
			m_array = new T[m_maxSize];		// Dynamically allocating an array to m_maxSize
			memset(m_array, 0, sizeof(T) * m_maxSize);	// Explicitly set 0 to all elements in the array

			m_growSize = ((growBy > 0) ? growBy : 0);
		}
	}

	// Destructor
	~TemplateCustomArray()
	{
		if (m_array != nullptr)
		{
			delete[] m_array;
			m_array = nullptr;
		}
	}
	// Insertion -- Big-O = O(N)

	// Insertion
	// Fast insertion for UnorderedArray -- Big-O is O(1)
	virtual void push(T val) = 0;
	virtual int search(T val) = 0;


	void pop()
	{
		if (m_numElements > 0)
		{
			m_numElements--;	// Reduce the total number of elements by 1. Ignoring the last element.
		}
	}
	// Remove an item given an index
	// (Almost) Brute-force execution -- Big-O = O(N)
	void remove(int index)
	{
		assert(m_array != nullptr);

		if (index >= m_numElements)
		{
			// I am trying to remove something outside of the bounds of the array
			return;	// <-- Maybe could do some form of exception handling
		}

		for (int i = index; i < m_numElements; i++)
		{
			// Start at the index we want to remove.
			// Shift everything after index back by one.
			if (i + 1 < m_numElements)	// Confines the loop into the array
			{
				m_array[i] = m_array[i + 1];
			}
		}
		m_numElements--;
	}

	T& operator[](int index)
	{
		assert(m_array != nullptr && index < m_numElements);
		return m_array[index];
	}
	// Clear
	void clear()
	{
		m_numElements = 0;	 // Ignore (or forgets) all current items in the array
	}

	// Gets and Sets
	int GetSize()
	{
		return m_numElements;
	}
	int GetMaxSize()
	{
		return m_maxSize;
	}
	int GetGrowSize()
	{
		return m_growSize;
	}
	T* GetM_array()
	{
		return m_array;
	}
	void SetGrowSize(int val)
	{
		assert(val >= 0);
		m_growSize = val;
	}
	void SetSize(int value)
	{
		m_numElements = value;
	}
	void SetMaxSize(int MS)
	{
		m_maxSize = MS;
	}
	void SetM_array(T* arrayn)
	{
		m_array = arrayn;
	}
	void ArrayValue(int pos, int value)
	{
		m_array[pos] = value;
	}

protected:
	// Private functions
		// Expansion
	bool Expand()
	{
		if (m_growSize <= 0)
		{
			// LEAVE!
			return false;
		}

		// Create the new array
		T* temp = new T[m_maxSize + m_growSize];
		assert(temp != nullptr);

		// Copy the contents of the original array into the new array
		memcpy(temp, m_array, sizeof(T) * m_maxSize);

		// Delete the old array
		delete[] m_array;

		// Clean up variable assignments
		m_array = temp;
		temp = nullptr;
		//m_growSize = m_growSize * 2;
		m_maxSize += m_growSize;

		return true;
	}

	// Private Variables
	T* m_array;			// Pointer to the beginning of the array

	int m_maxSize;		// Maximum size of the array
	int m_growSize;		// Amount the array can grow through expansion
	int m_numElements;	// Number of items currently in my array
};