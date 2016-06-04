#pragma once
#include <assert.h>

#include "Iterator/Iterator.hpp"
#include "Allocator/Allocator.hpp"

template<class T>
struct __ListNode
{
	__ListNode(const T& x = T())
		:_data(x)
		,_next(NULL)
		,_prev(NULL)
	{}

	T _data;				// �������
	__ListNode<T>* _prev;	// ָ��ǰһ������ָ��
	__ListNode<T>* _next;	// ָ���һ������ָ��
};

// List�ĵ�����
template<class T, class Ref, class Ptr>
class __ListIterator
{
public:
	typedef __ListIterator<T, T&, T*> Iterator;

	// ����Ref��Ptrģ�������Ҫ��Ϊ�˷��㸴�õķ�ʽʵ��const���͵ĵ�����ConstIterator
	typedef __ListIterator<T, const T&, const T*> ConstIterator;
	typedef __ListIterator<T, Ref, Ptr> Self;


	// List�Ǹ�˫�������������ĵ�������һ��˫�����������
	typedef BidirectionalIteratorTag IteratorCategory;
	typedef T ValueType;
	typedef ptrdiff_t  DifferenceType;
	typedef Ptr Pointer;
	typedef Ref Reference;
	typedef __ListNode<T>* LinkType;

	// ָ��ڵ��ָ��
	LinkType _node;

	__ListIterator(LinkType node = NULL)
		:_node(node)
	{}

	bool operator==(const Self& x) const
	{ 
		return _node == x._node;
	}
	bool operator!=(const Self& x) const
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

	Self& operator++()
	{ 
		_node = _node->_next;
		return *this;
	}

	Self operator++(int)
	{
		Self tmp(_node);
		_node = _node->_next;
		return tmp;
	}

	Self& operator--()
	{ 
		_node = _node->_prev;
		return *this;
	}

	Self& operator--(int)
	{ 
		Self tmp(_node);
		_node = _node->_prev;
		return tmp;
	}
};

//
// ���Ϊ˫��ѭ������
//
template<class T, class _Alloc = Alloc>
class List
{
public:
	// 
	// �����������const�����������õ�����
	//
	typedef __ListIterator<T, T&, T*> Iterator;
	typedef __ListIterator<T, const T&, const T*> ConstIterator;
	typedef ReverseIterator<Iterator> ReverseIterator;

	typedef T ValueType;
	typedef __ListNode<T>* LinkType;

	// �ض���ռ�������
	typedef SimpleAlloc<__ListNode<T>, _Alloc> DataAllocator;

	__ListNode<T>* BuyNode(const T& x = T())
	{
		__ListNode<T>* node = DataAllocator::Allocate();
		Construct(node, x);

		return node;
	}

	void DestoryNode(__ListNode<T>* node)
	{
		Destroy(node);
		DataAllocator::Deallocate(node);
	}

	List()
		:_head(BuyNode())
	{
		_head->_prev = _head;
		_head->_next = _head;
	}

	~List()
	{
		Clear();
	}

public:
	// ��posǰ����һ���ڵ�
	void Insert(Iterator pos, const ValueType& x)
	{
		LinkType tmp = BuyNode(x);
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

		//delete pos._node;
		DestoryNode(pos._node);

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
		return _head->_next;
	}

	Iterator End()
	{
		return _head;
	}

	ConstIterator Begin() const
	{
		return _head->_next;
	}

	ConstIterator End() const
	{
		return _head;
	}

	ReverseIterator RBegin() { return ReverseIterator(End()); }

	ReverseIterator REnd() { return ReverseIterator(Begin()); }

	void Clear()
	{
		Iterator begin = Begin();
		while(begin != End())
		{
			LinkType del = begin._node;
			++begin;
			//delete del;
			DestoryNode(del);
		}
	}

private:
	//
	// �ڱ�λ��ͷ��㣬������Ϊ��������end
	//
	__ListNode<T>* _head;	
};

// 1.����List������Iterator
void PrintList1(List<int>& l1)
{
	List<int>::Iterator it = l1.Begin();
	for (; it != l1.End(); ++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}

// 2.����List������ConstIterator
void PrintList2(const List<int>& l1)
{
	List<int>::ConstIterator it = l1.Begin();
	for (; it != l1.End(); ++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}

// 2.����List������ReverseIterator
void PrintList3(List<int>& l1)
{
	List<int>::ReverseIterator it = l1.RBegin();
	for (; it != l1.REnd(); ++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}

void TestList()
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

	// ������ʧЧ
	List<int>::Iterator it = l1.Begin();
	while(it != l1.End())
	{
		if ((*it) == 0)
			it = l1.Erase(it);
		else
			++it;
	}

	PrintList1(l1);
	PrintList2(l1);	
	PrintList3(l1);
}