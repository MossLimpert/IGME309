// Moss Limpert
// DSA 2
// Assignment 1
// 012723

// TODO:
// pushback - adds new things to the end of queue. items with a higher priority get moved
// further towards the front of the queue
// 
// popfront - remove whatever is at the front of the queue
// 
// print - print out all queue members
// size - current number of things in queue
// 
// https://www.geeksforgeeks.org/templates-cpp/
// https://www.programiz.com/cpp-programming/class-templates
// https://en.cppreference.com/w/cpp/language/rule_of_three
// https://www.youtube.com/watch?v=Hoixgm4-P4M
// https://www.geeksforgeeks.org/cpp-program-for-quicksort/
//

#include <iostream>

template <class T> class mQueue {
private:
	T* items;		// array of items in line
	int endOfLine;	// item after the last object in line
	int arr_size;	// maximum fill of array 
	/// <summary>
	/// Sorts the array to be in order
	/// </summary>
	/// <param name="arr">array to sort</param>
	/// <param name="start">start index</param>
	/// <param name="end">end index</param>
	void sort(T* arr, int start, int end)
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
	int partition(T* arr, int start, int end)
	{
		int index = 0;				// for going thru and filling new array
		T pivotElement = arr[end];	// picking last  element as pivot
		int pivotIndex = 0;

		// temporary array
		T* temp = new T [end - start + 1];
		for (int i = start; i <= end; i++)
		{
			if (arr[i] > pivotElement)	// take everything smaller than the pivot and put
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
			if (arr[i] < pivotElement)
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
	void resize()
	{
		int size = arr_size * 2;
		T* temp = new T[size];
		
		for (int i = 0; i < endOfLine; i++)	// only copy over what actually was in it
		{
			temp[i] = items[i];
		}
		arr_size = size;
		//delete[] items;
		items = temp;

		delete[] temp;
		temp = nullptr;
	}

public:
	/// <summary>
	/// Add a new item to the end of the line
	/// </summary>
	/// <param name="item">Item to add</param>
	void push_back(T item)	// add to back of line
	{
		if (endOfLine == arr_size)	// if teh last spot of the array holds
		{							// the last item, resize
			resize();
		}
		items[endOfLine] = item;	// add item to end of line
		endOfLine++;

		sort(items, 0, endOfLine - 1);
	}

	/// <summary>
	/// Pops the item off the front of the line
	/// </summary>
	/// <returns>The first item in line.</returns>
	T pop_front()			// front in line is served
	{
		T pop = items[0];
		if (endOfLine != 0)
		{
			for (int i = 1; i < endOfLine; i++)
			{
				items[i - 1] = items[i];
			}
			endOfLine--;
		}
		return pop;	// i will have user check for empty before popping in main
	}

	/// <summary>
	/// Prints out all items in the queue
	/// </summary>
	void print()			// print objs
	{
		if (!is_empty())
		{
			for (int i = 0; i < endOfLine; i++)
			{
				std::cout << "Item " << i << " in queue is: " << items[i] << std::endl;
			}
		}
		else std::cout << "Queue is empty!" << std::endl;
	}
	
	/// <summary>
	/// Constructor
	/// </summary>
	mQueue()				// constructor
	{
		items = new T [2];
		arr_size = 2;
		endOfLine = 0;	
	}
	
	/// <summary>
	/// Destructor
	/// </summary>
	~mQueue()				// destructor
	{
		delete[] items;
		items = nullptr;
	}

	/// <summary>
	/// Gets current size of array (Number of items inside)
	/// </summary>
	/// <returns>number of items in array</returns>
	int get_size()
	{
		return arr_size;
	}

	int get_count()
	{
		return endOfLine;
	}

	/// <summary>
	/// Test to see if the array is empty
	/// </summary>
	/// <returns>Bool true if array is empty</returns>
	bool is_empty()
	{
		if (endOfLine == 0) return true;
		else return false;
	}

	/// <summary>
	/// Copy constructor
	/// </summary>
	/// <param name="other">Queue to copy from</param>
	mQueue(const mQueue& other)			// copy constructor
	{
		int size = other.items.arr_size;
		T* temp = new T * [size];

		for (int i = 0; i < size - 1; i++)
		{
			temp[i] = other.items[i];
		}

		arr_size = size;
		endOfLine = other.endOfLine;
		delete[] items;
		items = temp;
	}

	mQueue& operator=(const mQueue& other)	// copy assignment operator
	{
		if (this == &other) return *this;	// trying to copy the exact same thing?

		int size = other.items.size();		// what size other line?
		T* new_items = new T[size];
		for (int i = 0; i < size; i++)		// populate
		{
			new_items[i] = other.items[i];
		}
		delete[] items;						// get rid of old one
		items = new_items;

		delete[] new_items;
		new_items = nullptr;

		return *this;
	}
};
