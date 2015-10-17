#pragma once
#include <assert.h>

template<class T>
struct __ListNode
{
	__ListNode()
		:_next(NULL)
		,_prev(NULL)
	{}

	__ListNode(const T& x)
		:_data(x)
		,_next(NULL)
		,_prev(NULL)
	{}

	T _data;				// �������
	__ListNode<T>* _prev;	// ָ��ǰһ������ָ��
	__ListNode<T>* _next;	// ָ���һ������ָ��
};

// List�ĵ�����
template<class T>
class __ListIterator
{
public:
	typedef __ListIterator<T> Iterator;

	// List�Ǹ�˫�������������ĵ�������һ��˫�����������
	typedef BidirectionalIteratorTag IteratorCategory;
	typedef T ValueType;
	typedef ptrdiff_t  DifferenceType;
	typedef T* Pointer;
	typedef T& Reference;
	typedef __ListNode<T>* LinkType;

	// ָ��ڵ��ָ��
	LinkType _node;

	__ListIterator(LinkType node = NULL)
		:_node(node)
	{}

	bool operator==(const __ListIterator<T>& x) const
	{ 
		return _node == x._node;
	}
	bool operator!=(const __ListIterator<T>& x) const
	{ 
		return _node != x._node;
	}

	Reference operator*() const
	{ 
		return _node->_data;
	}

	Pointer operator->() const
	{
		return &(operator*());
	}

	__ListIterator<T>& operator++()
	{ 
		_node = _node->_next;
		return *this;
	}

	__ListIterator<T> operator++(int)
	{
		__ListIterator<T> tmp(_node);
		_node = _node->_next;
		return tmp;
	}

	__ListIterator<T>& operator--()
	{ 
		_node = _node->_prev;
		return *this;
	}

	__ListIterator<T>& operator--(int)
	{ 
		__ListIterator<T> tmp(_node);
		_node = _node->_prev;
		return tmp;
	}
};

//
// ���Ϊ˫��ѭ������
//
template<class T>
class List
{
public:
	typedef __ListIterator<T> Iterator;

	typedef T ValueType;
	typedef __ListNode<T>* LinkType; 

	List()
	{
		_head._prev = &_head;
		_head._next = &_head;
	}

	~List()
	{
		Clear();
	}

public:
	// ��posǰ����һ���ڵ�
	void Insert(Iterator pos, const ValueType& x)
	{
		LinkType tmp = new __ListNode<T>(x);
		LinkType prev = pos._node->_prev;
		LinkType cur = pos._node;

		prev->_next = tmp;
		tmp->_prev = prev;

		tmp->_next = cur;
		cur->_prev = tmp;
	}

	void PushBack(const T& x)
	{
		Insert(End(), x);
	}

	void PushFront(const T& x)
	{
		Insert(Begin(), x);
	}

	// ɾ��posָ��Ľڵ㣬����pos֮���һ���ڵ�
	Iterator Erase(Iterator pos)
	{
		LinkType prev = pos._node->_prev;
		LinkType next = pos._node->_next;

		prev->_next = next;
		next->_prev = prev;

		delete pos._node;

		return Iterator(next);
	}

	void PopBack()
	{
		Erase(--End());
	}

	void PopFront()
	{
		Erase(Begin());
	}

	Iterator Begin()
	{
		return _head._next;
	}

	Iterator End()
	{
		return &_head;
	}

	void Clear()
	{
		Iterator begin = Begin();
		while(begin != End())
		{
			LinkType tmp = begin._node;
			++begin;
			delete tmp;
		}
	}

private:
	//
	// �ڱ�λ��ͷ��㣬������Ϊ��������end
	//
	__ListNode<T> _head;	
};

// 1.����List������
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

	// ������ʧЧ
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