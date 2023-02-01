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
//

template <class T>
class mQueue {
private:
	T* items;
	int endOfLine;
	int arr_size;
	void sort(T* arr, int start, int end);
	int partition(T* arr, int start, int end);
	void resize();
public:
	void push_back(T item);	// add to back of line
	T pop_front();			// front in line is served
	void print();			// print objs
	mQueue();				// constructor
	~mQueue();				// destructor
	mQueue(const mQueue& other);			// copy constructor
	mQueue& operator=(const mQueue& other)	// copy assignment operator
	{
		if (this == &other) return *this;	// trying to copy the exact same thing?

		int size = other.items.size();		// what size other line?
		T* new_items = new T * [size];
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

