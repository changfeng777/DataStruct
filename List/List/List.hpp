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
	T _data;		// �������
	Node<T>* _prev;	// ָ��ǰһ������ָ��
	Node<T>* _next;	// ָ���һ������ָ��
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
	// ͷ��/ͷɾ/β��/βɾ
	void PushBack(const T& x);
	void PopBack();
	void PushFront(const T& x);
	void PopFront();

	// ����/����/ɾ��
	void Insert(Node<T>* pos, const T& x);
	Node<T>* Find(const T& x);
	void Erase(Node<T>* n);
	void Reverse();

	// ���/��ӡ
	void Clear();
	void Print();

private:
	Node<T>* _head;	// ָ������ͷ��ָ��
	Node<T>* _tail;	// ָ������β��ָ��
};

template<class T>
void List<T>::PushBack(const T& x)
{
	// 1.û�нڵ�
	// 2.����ڵ�
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
	// 1.û�нڵ�
	// 2.һ���ڵ�
	// 3.����ڵ�
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
	// 1.û�нڵ�
	// 2.����ڵ�
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
	// 1.û�нڵ�
	// 2.һ���ڵ�
	// 3.����ڵ�
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

	// 1.��posλ����β�ڵ㣬����ڵ㲢����β��
	if (pos == _tail)
	{
		pos->_next = tmp;
		tmp->_prev = pos;
		_tail = tmp;
		return;
	}

	// 2.�ڵ�ǰ�ڵ�������һ���ڵ㣬������ǰ��ָ�룬ע�����˳��
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
	// û�нڵ� or һ���ڵ���ֱ�ӷ���
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