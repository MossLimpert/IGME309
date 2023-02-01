// A01_Limpert.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MQueue.h"

int main()
{
    mQueue<int> queue = mQueue<int>();

    queue.push_back(3);
    queue.push_back(4);
    queue.push_back(7);
    queue.print();
}

