#include <iostream>
using namespace std;

#include "List.hpp"
#include "Vector.hpp"

void PrintList(List<int>& l1)
{
	List<int>::Iterator it = l1.Begin();
	for (; it != l1.End(); ++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}

void Test1()
{
	List<int> l1;
	l1.PushBack(1);
	l1.PushBack(2);
	l1.PushBack(3);
	l1.PushBack(4);
	l1.PushBack(5);
	l1.PushBack(6);
	l1.PushBack(7);
	l1.PushBack(8);
	PrintList(l1);

	// 迭代器失效
	List<int>::Iterator it = l1.Begin();
	while(it != l1.End())
	{
		if (*it % 2 == 0)
			it = l1.Erase(it);
		else
			++it;
	}
	PrintList(l1);	
}

void PrintVector(Vector<int>& v)
{
	Vector<int>::Iterator it = v.Begin();
	for (; it != v.End(); ++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}

void Test2()
{
	Vector<int> v1;
	v1.PushBack(1);
	v1.PushBack(2);
	v1.PushBack(3);
	v1.PushBack(4);
	v1.PushBack(5);
	v1.PushBack(6);
	v1.PushBack(7);
	v1.PushBack(8);

	PrintVector(v1);

	// 迭代器失效
	Vector<int>::Iterator it = v1.Begin();
	while(it != v1.End())
	{
		if (*it % 2 == 0)
			it = v1.Erase(it);
		else
			++it;
	}
	PrintVector(v1);
}

int main()
{
	Test1();
	Test2();

	return 0;
}