// Moss Limpert
// DSA 2
// Assignment 1
// 012723


#include "MQueue.h"
#include <iostream>

/// <summary>
/// Constructor
/// </summary>
template<class T>
mQueue<T>::mQueue()
{
	items = new T * [1];
	arr_size = 1;
	endOfLine = 0;
}

/// <summary>
/// Destructor
/// </summary>
template<class T>
mQueue<T>::~mQueue()
{
	delete[] items;
	items = nullptr;
}

/// <summary>
/// Copy constructor
/// </summary>
/// <param name="other">Queue to copy from</param>
template<class T>
mQueue<T>::mQueue(const mQueue& other)
{
	int size = other.items.size();
	arr_size = size;
	endOfLine = other.endOfLine;
	T* temp = new T * [size];

	for (int i = 0; i < size; i++)
	{
		temp[i] = other.items[i];
	}

	delete[] items;
	items = temp;
}

/// <summary>
/// Sorts the array to be in order
/// </summary>
/// <param name="arr">array to sort</param>
/// <param name="start">start index</param>
/// <param name="end">end index</param>
template<class T>
void mQueue<T>::sort(T* arr, int start, int end)
{
	if (start < end)
	{
		int partitionIndex = partition(arr, start, end);
		sort(arr, start, partitionIndex - 1);
		sort(arr, partitionIndex + 1, end);
	}
	return;
}

/// <summary>
/// Divides the array for a quick sort
/// </summary>
/// <param name="arr">array to sort</param>
/// <param name="start">start index</param>
/// <param name="end">end index</param>
/// <returns>index of the pivot number</returns>
template<class T>
int mQueue<T>::partition(T* arr, int start, int end)
{
	int index = 0;				// for going thru and filling new array
	T pivotElement = arr[end];	// picking last element as pivot
	int pivotIndex;

	// temporary array
	T* temp = new T * [end - start + 1];
	for (int i = start; i <= end; i++)
	{
		if (arr[i] < pivotElement)	// take everything smaller than the pivot and put
		{							// it in the new array
			temp[index] = arr[i];
			index++;
		}
	}
	temp[index] = pivotElement;	// put the pivot with the smaller stuff
	index++;
	// take all the larger stuff and put it in after
	for (int i = start; i < end; i++)
	{
		if (arr[i] > pivotElement)
		{
			temp[index] = arr[i];
			index++;
		}
	}
	// left of pivot is smaller than pivot, right is larger

	index = 0;
	for (int i = start; i <= end; i++)
	{
		if (arr[i] == pivotElement) pivotIndex = i;	// get pivot index
		arr[i] = temp[index];
		index++;
	}
	return pivotIndex;
}

/// <summary>
/// Resize the array and copy over elements
/// </summary>
template<class T>
void mQueue<T>::resize()
{
	int size = items.size();
	T* temp = new T * [size * 2];
	arr_size = size * 2;
	for (int i = 0; i < size; i++)	// only copy over what actually was in it
	{
		temp[i] = items[i];
	}
	delete[] items;
	items = temp;

	delete[] temp;
	temp = nullptr;
}

/// <summary>
/// Add a new item to the end of teh line
/// </summary>
/// <param name="item">Item to add</param>
template<class T>
void mQueue<T>::push_back(T item)
{
	if (items.at(arr_size - 1) == items.last())	// if teh last spot of the array holds
	{											// the last item, resize
		resize();
	}
	items[endOfLine] = item;	// add item to end of line
	endOfLine++;
}

/// <summary>
/// Pops the item off the front of the line
/// </summary>
/// <returns>The first item in line.</returns>
template<class T>
T mQueue<T>::pop_front()
{
	sort(items, 0, endOfLine);
	T pop = items[0];

	for (int i = 1; i < endOfLine; i++)
	{
		items[i - 1] = items[i];
	}
	endOfLine--;

	return items[0];
}

/// <summary>
/// Prints out all items in the queue
/// </summary>
template<class T>
void mQueue<T>::print()
{
	sort(items, 0, endOfLine);
	for (int i = 0; i < endOfLine; i++)
	{
		std::cout << "Item " << i << " in queue is: " << items[i] << std::endl;
	}
}
