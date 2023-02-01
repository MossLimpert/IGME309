/*--------------------------------------------------------------------------------------------------
Made by: Alberto Bobadilla
on: 2017/06/02
Modified by: Moss Limpert
on: 2023/28/01	(YYYY/DD/MM)
--------------------------------------------------------------------------------------------------*/
#ifndef __MAIN_H_
#define __MAIN_H_
#include <iostream>
#include <deque>
#include "Alberto.h"
#define uint unsigned int
#include "MQueue.h"

struct Foo
{
	int content = 0;
	Foo(int a_content) : content(a_content) {};
	friend std::ostream& operator<<(std::ostream& os, Foo other)
	{
		os << other.content;
		return os;
	}
};
#endif //__MAIN_H_
