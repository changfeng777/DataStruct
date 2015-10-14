#include <iostream>
using namespace std;

#include "List.hpp"

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

	// µü´úÆ÷Ê§Ð§
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

int main()
{
	Test1();

	return 0;
}