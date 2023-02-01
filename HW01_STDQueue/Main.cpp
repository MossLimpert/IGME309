#include "Main.h"

//template <typename T>
//void Print(std::deque<T> a_queue)
//{
//	std::cout << "Begining of queue......." << std::endl;
//	uint count = a_queue.size();
//	for (uint i = 0; i < count; ++i)
//	{
//		std::cout << a_queue[i];
//		std::cout << std::endl;
//	}
//	std::cout << "End of queue............" << std::endl;
//}

int main(void)
{
	//mQueue<int> queue = mQueue<int>();
	//std::deque<int> myQueue;
	//Push elements
	//myQueue.push_back(0);
	//std::cout << "	just pushed +++++" << std::endl;
	//myQueue.push_back(1);
	//std::cout << "	just pushed +++++" << std::endl;
	//myQueue.push_back(2);
	//std::cout << "	just pushed +++++" << std::endl;

	// make a new queue A01
	mQueue<int> queue = mQueue<int>();

	//a01 push elements
	queue.push_back(3);
	queue.push_back(4);
	queue.push_back(7);
	queue.push_back(2);
	//a01 print elements
	queue.print();
	//a01 pop element
	std::cout << "pop: " << queue.pop_front() << std::endl;
	queue.print();
	//a01 pop queue
	std::cout << "pop: " << queue.pop_front() << std::endl;
	//a01 push more elements
	queue.push_back(12);
	queue.push_back(5);
	queue.push_back(8);
	queue.print();
	std::cout << "pop: " << queue.pop_front() << std::endl;
	std::cout << "pop: " << queue.pop_front() << std::endl;
	std::cout << "clearing queue" << std::endl;
	for (int i = 0; i < queue.get_size(); i++)
	{
		if (queue.get_count() != 0)
		{
			std::cout << "pop: " << queue.pop_front() << std::endl;
		}
	}
	queue.print();

	mQueue<AlbertoClass> albertoQueue = mQueue<AlbertoClass>();

	// WORKING WITH ALBERTOS SEEMS TO NOT WORK

	//std::deque<AlbertoClass> myAlbertoQueue;
	/*for (uint i = 30; i < 40; ++i)
	{
		AlbertoClass alberto(i);
		albertoQueue.push_back(alberto);
		std::cout << "	just pushed +++++" << std::endl;
	}*/
	//std::cout << "	Content" << std::endl;
	//for (uint i = 0; i < 10; ++i)
	//{
	//	std::cout << myAlbertoQueue[i] << std::endl;
	//}
	//albertoQueue.print();
	std::cout << "Press Enter to finish." << std::endl;


	
	getchar();
}