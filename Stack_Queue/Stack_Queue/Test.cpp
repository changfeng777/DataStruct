#include <iostream>
using namespace std;

#include "Queue.hpp"
void TestQueue()
{
	Queue<int> q;
	q.Push(1);
	q.Push(2);
	q.Push(3);
	q.Push(4);
	q.Push(5);

	q.Print();

	q.Pop();
	q.Pop();
	q.Pop();
	q.Pop();
	
	q.Print();
}

#include "Stack.hpp"
//#include "StackAdapter.hpp"
#include "Maze.hpp"

void TestStack()
{
	Stack<int> s1;
	cout<<"Stack is Empty:"<<s1.Empty()<<endl;

	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Push(4);
	s1.Push(5);

	cout<<s1.Top()<<endl;
	s1.Pop();

	cout<<s1.Top()<<endl;
	s1.Pop();

	cout<<s1.Top()<<endl;
	s1.Pop();

	cout<<s1.Top()<<endl;
	s1.Pop();

	cout<<s1.Top()<<endl;
	s1.Pop();
	s1.Print();
}

#include "StackQueueTopic.hpp"
// 1
void TestTopic1()
{
	Stack_Min1<int> s1;
	s1.Push(3);
	s1.Push(2);
	s1.Push(1);
	s1.Push(4);

	cout<<"Min:"<<s1.Min()<<endl;

	s1.Pop();
	s1.Pop();
	cout<<"Min:"<<s1.Min()<<endl;

	s1.Pop();
	cout<<"Min:"<<s1.Min()<<endl;

	Stack_Min1<int> s2;
	s2.Push(3);
	s2.Push(2);
	s2.Push(1);
	s2.Push(4);

	cout<<"Min:"<<s2.Min()<<endl;

	s2.Pop();
	s2.Pop();
	cout<<"Min:"<<s2.Min()<<endl;

	s2.Pop();
	cout<<"Min:"<<s2.Min()<<endl;
}

// 2¡¢3
void TestTopic23()
{
	QueueBy2Stack<int> q;
	q.Push(1);
	q.Push(2);
	q.Push(3);
	q.Push(4);

	q.Pop();
	q.Pop();

	StackBy2Queue<int> s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);

	s.Pop();
	s.Pop();
}

// 4 
void TestTopic4()
{
	vector<int> v1, v2;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);

	v2.push_back(4);
	v2.push_back(5);
	v2.push_back(3);
	v2.push_back(2);
	v2.push_back(1);

	cout<<"Is Vaild Order£¿£º"<<IsVaildStackOrder(v1, v2)<<endl;
}

int main()
{
	//TestQueue();
	//TestStack();
	//TestMaze();

	//TestTopic1();
	//TestTopic23();
	TestTopic4();

	return 0;
}