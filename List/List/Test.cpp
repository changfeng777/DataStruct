#include <iostream>
using namespace std;

#include "List.hpp"

void Test1()
{
	List<int> l;
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.Print();
	
	l.PopBack();
	l.PopBack();
	l.PopBack();
	l.PopBack();
	l.Print();

	cout<<endl;
}

void Test2()
{
	List<int> l;
	l.PushFront(1);
	l.PushFront(2);
	l.PushFront(3);
	l.PushFront(4);
	l.Print();

	l.PopFront();
	l.PopFront();
	l.PopFront();
	l.PopFront();
	l.Print();
	cout<<endl;

}

void Test3()
{
	List<int> l;
	l.PushFront(1);
	l.PushFront(2);
	l.PushFront(3);
	l.PushFront(4);
	l.Print();

	Node<int>* ret = l.Find(2);
	l.Insert(ret, 0);
	l.Print();

	l.Erase(ret);
	l.Print();
	cout<<endl;
}

void Test4()
{
	List<int> l;
	l.PushFront(1);
	l.PushFront(2);
	l.PushFront(3);
	l.PushFront(4);
	l.Print();

	l.Reverse();
	l.Print();
	cout<<endl;
}

void Test5()
{
	List<int> l;
	l.PushFront(1);
	l.PushFront(2);
	l.PushFront(3);
	l.PushFront(4);
	l.Print();

	List<int> copy1(l);
	copy1.Print();

	List<int> copy2(l);
	copy2 = l;
	copy2.Print();

	cout<<endl;
}

int main()
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();

	return 0;
}