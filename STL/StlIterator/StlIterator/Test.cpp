#include <iostream>
using namespace std;

#include "StlIterator.hpp"
#include "List.hpp"
#include "Vector.hpp"

// ≤‚ ‘DistanceÀ„∑®
void Test3()
{
	List<int> l1;
	l1.PushBack(1);
	l1.PushBack(2);
	l1.PushBack(3);
	l1.PushBack(4);

	cout<<"List Distance: "<<Distance(l1.Begin(), l1.End())<<endl;

	Vector<int> v1;
	v1.PushBack(1);
	v1.PushBack(2);
	v1.PushBack(3);
	v1.PushBack(4);
	v1.PushBack(5);

	cout<<"Vector Distance: "<<Distance(v1.Begin(), v1.End())<<endl;
}

// ≤‚ ‘AdvanceÀ„∑®
void Test4()
{
	List<int> l1;
	l1.PushBack(1);
	l1.PushBack(2);
	l1.PushBack(3);
	l1.PushBack(4);

	List<int>::Iterator listIt = l1.Begin();
	Advance(listIt, 3);
	cout<<"List Advance ? 3 : "<<*listIt<<endl;

	Vector<int> v1;
	v1.PushBack(1);
	v1.PushBack(2);
	v1.PushBack(3);
	v1.PushBack(4);
	v1.PushBack(5);

	Vector<int>::Iterator vecIt = v1.Begin() + 1;
	Advance(vecIt, 3);
	cout<<"Vector Advance ? 5 : "<<*vecIt<<endl;
} 

int main()
{
	//Test1();
	//Test2();
	Test3();
	Test4();

	return 0;
}