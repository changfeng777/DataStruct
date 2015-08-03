#pragma once
#include <assert.h>

template<class T>
class Node
{
	template<class T> friend class SList; // 声明为友元

public:
	Node(const T& x)
		:_data(x)
		,_next(0)
	{}

	const T& GetData()
	{
		return _data;
	}

private:
	T _data;		// 数据
	Node* _next;	// 指向下个节点的指针
};

template<class T>
class SList
{
public:
	SList()
		:_head(0)
		,_tail(0)
	{}

	~SList()
	{
		Clear();
	}

public:
	void PushBack(const T& x)
	{
		if (!_head)
		{
			_head = new Node<T>(x);
			_tail = _head;
		}
		else
		{
			_tail->_next = new Node<T>(x);
			_tail = _tail->_next;
		}
	}

	void PushFront(const T& x)
	{
		if (!_head)
		{
			_head = new Node<T>(x);
			_tail = _head;
		}
		else
		{
			Node<T>* n = new Node<T>(x);
			n->_next = _head;
			_head = n;
		}
	}

	void PopBack()
	{
		// 没有节点
		if (!_head)
			return;

		// 一个节点
		if (_tail == _head)
		{
			delete _head;
			_head = 0;
			_tail = 0;
		}
		else
		{
			// 找到尾节点的前一个节点
			Node<T>* prev = _head;
			Node<T>* cur = _head->_next;
			while (cur != _tail)
			{
				prev = cur;
				cur = cur->_next;
			}
			
			delete _tail;
			prev->_next = 0;
			_tail = prev;
		}
	}

	void PopFront()
	{
		// 没有节点
		if(!_head)
			return;

		// 一个节点 
		if (_head == _tail)
		{
			delete _head;
			_head = 0;
			_tail = 0;
		}
		else
		{
			Node<T>* n = _head;
			_head = _head->_next;

			delete n;
		}
	}

	// 在pos后面插入一个节点
	void Insert(Node<T>* pos, const T& x)
	{
		assert(pos);

		Node<T>* newNode = new Node<T>(x);
		newNode->_next = pos->_next;
		pos->_next = newNode;

		// 若pos是尾节点，则处理_tail指针
		if (pos == _tail)
		{
			_tail = newNode;
		}
	}

	Node<T>* Find(const T& x)
	{
		Node<T>* n = _head;
		while (n)
		{
			if (n->_data == x)
			{
				return n;
			}

			n = n->_next;
		}

		return 0;
	}

	void Erase(Node<T>* pos)
	{
		assert(pos);

		// 尾节点则删尾
		if (pos == _tail)
		{
			PopBack();
			return;
		}

		// 头结点则删头
		if (pos == _head)
		{
			PopFront();
			return;
		}

		// 否则删除当前节点的下一个节点
		Node<T>* delNode = pos->_next;
		pos->_data = delNode->_data;
		pos->_next = delNode->_next;
		delete delNode;
	}

	void Clear()
	{
		Node<T>* n = _head;
		while(n)
		{
			Node<T>* tmp = n;
			n = n->_next;
			delete tmp; 
		}

		_head = 0;
		_tail = 0;
	}

	void Print()
	{
		Node<T>* n = _head;
		while(n)
		{
			cout<<n->_data<<"->";
			n = n->_next;
		}

		cout<<"NULL"<<endl;
	}

	size_t Size()
	{
		size_t size = 0;
		Node<T>* n = _head;
		while(n)
		{
			n = n->_next;
			++size;
		}

		return size;
	}

	const T& Front()
	{
		return _head->_data;
	}

	const T& Back()
	{
		return _tail->_data;
	}
	
	bool Empty()
	{
		return _head == 0;
	}

private:
	Node<T>* _head;		// 链表头
	Node<T>* _tail;		// 链表尾
};