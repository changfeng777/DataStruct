#pragma once
#include <assert.h>
//template<class T>
//class List;

template<class T>
class Node
{
	template<class T>
	friend class List;

	//friend class List<T>;
public:
	Node(const T& x)
		:_data(x)
		,_next(NULL)
		,_prev(NULL)
	{}

private:
	T _data;		// 结点数据
	Node<T>* _prev;	// 指向前一个结点的指针
	Node<T>* _next;	// 指向后一个结点的指针
};

template<class T>
class List
{
public:
	List()
		:_head(NULL)
	{}

	~List()
	{
		Clear();
	}

public:
	// 头插/头删/尾插/尾删
	void PushBack(const T& x);
	void PopBack();
	void PushFront(const T& x);
	void PopFront();

	// 插入/查找/删除
	void Insert(Node<T>* pos, const T& x);
	Node<T>* Find(const T& x);
	void Erase(Node<T>* n);
	void Reverse();

	// 清除/打印
	void Clear();
	void Print();

private:
	Node<T>* _head;	// 指向链表头的指针
	Node<T>* _tail;	// 指向链表尾的指针
};

template<class T>
void List<T>::PushBack(const T& x)
{
	// 1.没有节点
	// 2.多个节点
	if (_head == NULL)
	{
		_head = new Node<T>(x);
		_tail = _head;
	}
	else
	{
		Node<T>* tmp = new Node<T>(x);
		_tail->_next = tmp;
		tmp->_prev = _tail;
		_tail = tmp;
	}
}

template<class T>
void List<T>::PopBack()
{
	// 1.没有节点
	// 2.一个节点
	// 3.多个节点
	if (_head == NULL)
	{
		return;
	}
	else if(_head == _tail)
	{
		delete _head;
		_head = NULL;
		_tail = NULL;
	}
	else
	{	
		Node<T>* del = _tail;
		_tail = _tail->_prev;
		_tail->_next = NULL;
		delete del;
	}
}

template<class T>
void List<T>::PushFront(const T& x)
{
	// 1.没有节点
	// 2.多个节点
	if (_head == NULL)
	{
		_head = new Node<T>(x);
		_tail = _head;
	}
	else
	{
		Node<T>* tmp = new Node<T>(x);
		tmp->_next = _head;
		_head->_prev = tmp;
		_head = tmp;
	}
}

template<class T>
void List<T>::PopFront()
{
	// 1.没有节点
	// 2.一个节点
	// 3.多个节点
	if (_head == NULL)
	{
		return;
	}
	else if(_head == _tail)
	{
		delete _head;
		_head = NULL;
		_tail = NULL;
	}
	else
	{	
		Node<T>* del = _head;
		_head = _head->_next;
		_head->_prev = NULL;
		delete del;
	}
}

template<class T>
void List<T>::Insert(Node<T>* pos, const T& x)
{
	assert(pos);

	Node<T>* tmp = new Node<T>(x);

	// 1.若pos位置是尾节点，插入节点并更新尾。
	if (pos == _tail)
	{
		pos->_next = tmp;
		tmp->_prev = pos;
		_tail = tmp;
		return;
	}

	// 2.在当前节点后面插入一个节点，并更新前后指针，注意更新顺序。
	Node<T>* next = pos->_next;
	tmp->_next = next;
	next->_prev = tmp;

	pos->_next = tmp;
	tmp->_prev = pos;
}

template<class T>
Node<T>* List<T>::Find(const T& x)
{
	Node<T>* begin = _head;
	while (begin)
	{
		if(begin->_data == x)
		{
			return begin;
		}

		begin = begin->_next;
	}

	return NULL;
}

template<class T>
void List<T>::Erase(Node<T>* n)
{
	assert(n);

	if (n == _head)
	{
		PopFront();
	}
	else if (n == _tail)
	{
		PopBack();
	}
	else
	{
		Node<T>* prev = n->_prev;
		Node<T>* next = n->_next;
		prev->_next = next;
		next->_prev = prev;
		delete n;
	}
}

template<class T>
void List<T>::Reverse()
{
	// 没有节点 or 一个节点则直接返回
	if (_head == _tail)
	{
		return;
	}

	Node<T>* newHead = _head;
	Node<T>* newTail = _head;

	Node<T>* begin = _head->_next;
	while(begin)
	{
		Node<T>* tmp = begin;
		begin = begin->_next;

		tmp->_next = newHead;
		newHead->_prev = tmp;
		newHead = tmp;
	}

	newTail->_next = NULL;
	newHead->_prev = NULL;

	_head = newHead;
	_tail = newTail;
}

template<class T>
void List<T>::Clear()
{
	Node<T>* begin = _head;
	while (begin)
	{
		Node<T>* del = begin;
		begin = begin->_next;
		delete del;
	}
}

template<class T>
void List<T>::Print()
{
	Node<T>* begin = _head;
	while (begin)
	{
		cout<<begin->_data<<"->";
		begin = begin->_next;
	}
	cout<<"NULL"<<endl;
}