#pragma once
#include <assert.h>

template<class T>
class Node
{
	template<class T> friend class SList; // ����Ϊ��Ԫ

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
	T _data;		// ����
	Node* _next;	// ָ���¸��ڵ��ָ��
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
		// û�нڵ�
		if (!_head)
			return;

		// һ���ڵ�
		if (_tail == _head)
		{
			delete _head;
			_head = 0;
			_tail = 0;
		}
		else
		{
			// �ҵ�β�ڵ��ǰһ���ڵ�
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
		// û�нڵ�
		if(!_head)
			return;

		// һ���ڵ� 
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

	// ��pos�������һ���ڵ�
	void Insert(Node<T>* pos, const T& x)
	{
		assert(pos);

		Node<T>* newNode = new Node<T>(x);
		newNode->_next = pos->_next;
		pos->_next = newNode;

		// ��pos��β�ڵ㣬����_tailָ��
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

		// β�ڵ���ɾβ
		if (pos == _tail)
		{
			PopBack();
			return;
		}

		// ͷ�����ɾͷ
		if (pos == _head)
		{
			PopFront();
			return;
		}

		// ����ɾ����ǰ�ڵ����һ���ڵ�
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
	Node<T>* _head;		// ����ͷ
	Node<T>* _tail;		// ����β
};