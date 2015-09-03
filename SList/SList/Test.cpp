#include <iostream>
using namespace std;
#include <list>

#include "SList.hpp"

// ≤‚ ‘PushBack&PushFront
void Test1()
{
	// ≤‚ ‘Õ∑≤Â
	SList<int> sl1;
	sl1.PushBack(1);
	sl1.PushBack(2);
	sl1.PushBack(3);

	sl1.Print();
	if (sl1.Size() == 3 && sl1.Front() == 1)
	{
		cout<<"Test PushBack Success"<<endl;
	}


	sl1.Clear();

	// ≤‚ ‘Œ≤≤Â
	sl1.PushFront(1);
	sl1.PushFront(2);
	sl1.PushFront(3);
	sl1.Print();

	if (sl1.Size() == 3 && sl1.Back() == 1)
	{
		cout<<"Test PushFront Success"<<endl;
	}

	cout<<endl;
}

// ≤‚ ‘PopBack&PopFront
void Test2()
{
	// ≤‚ ‘Õ∑Œ≤…æ
	SList<int> sl1;
	sl1.PushBack(1);
	sl1.PushBack(2);
	sl1.PushBack(3);

	sl1.Print();
	sl1.PopBack();
	sl1.PopBack();
	sl1.PopBack();
	if (sl1.Empty())
	{
		cout<<"Test PopBack Success"<<endl;
	}

	sl1.Clear();

	// ≤‚ ‘Õ∑…æ
	sl1.PushBack(1);
	sl1.PushBack(2);
	sl1.PushBack(3);

	sl1.Print();
	sl1.PopFront();
	sl1.PopFront();
	sl1.PopFront();
	if (sl1.Empty())
	{
		cout<<"Test PopFront Success"<<endl;
	}

	cout<<endl;
}

// ≤‚ ‘Find&Insert
void Test3()
{
	// ≤‚ ‘Õ∑Œ≤…æ
	SList<int> sl1;
	sl1.PushBack(1);
	sl1.PushBack(2);
	sl1.PushBack(3);
	Node<int>* ret = sl1.Find(3);
	if (ret)
	{
		sl1.Insert(ret, 4);
	}

	sl1.Print();

	if (sl1.Find(5) == false && sl1.Size()==4 && sl1.Back() == 4)
	{
		cout<<"Test Find & Insert Success"<<endl;
	}

	cout<<endl;
}

// ≤‚ ‘Erase
void Test4()
{
	SList<int> sl1;
	sl1.PushBack(1);
	sl1.PushBack(2);
	sl1.PushBack(3);
	sl1.PushBack(4);
	sl1.Print();

	Node<int>* ret = sl1.Find(2);
	if (ret)
	{
		sl1.Erase(ret);
	}

	ret = sl1.Find(4);
	if (ret)
	{
		sl1.Erase(ret);
	}

	sl1.Print();
	if (sl1.Size()==2 && sl1.Back() == 3)
	{
		cout<<"Test Erase Node Success"<<endl;
	}

	cout<<endl;
}

void Test5()
{
	SList<int> sl1;
	sl1.PushBack(1);
	sl1.PushBack(2);
	sl1.PushBack(3);
	sl1.PushBack(4);
	sl1.PushBack(5);
	sl1.Print();

	Node<int>* ret = sl1.Find(2);
	sl1.Erase(ret);

	ret = sl1.Find(1);
	sl1.Erase(ret);

	ret = sl1.Find(5);
	sl1.Erase(ret);

	sl1.Print();

	cout<<"Test Erase Success"<<endl;
}

void Test6()
{	
	SList<int> sl1;
	sl1.PushBack(1);
	sl1.PushBack(2);
	sl1.PushBack(3);
	sl1.PushBack(4);
	sl1.PushBack(5);
	sl1.Print();

	SList<int> sl2(sl1);
	sl2.Print();

	SList<int> sl3(sl2);
	sl3 = sl1;
	sl3.Print();

	cout<<"Test Copy Success"<<endl;
}

int main()
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	return 0;
}