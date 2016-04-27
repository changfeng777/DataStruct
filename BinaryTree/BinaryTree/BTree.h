#pragma once

#include "Common.h"

// M·ƽ��B��

template<class K, size_t M = 3>
struct BTreeNode
{
	// �ؼ���--ps:_keys[M-1]λ�ò���ʵ�ʵ�ֵ����Ҫ���ڷ���ʱ���㴦��
	K _keys[M];							
	BTreeNode<K, M>* _subs[M];			// ����
	size_t _size;						// �ؼ��ָ���

	BTreeNode<K, M>* _parent;			// ����
	bool _isLeaf;						// �Ƿ���Ҷ�ӽڵ�

	BTreeNode()
		:_parent(NULL)
		,_isLeaf(true)
		,_size(0)
	{
		for (size_t i = 0; i < M; ++i)
		{
			_subs[i] = NULL;
		}
	}
};

template<class K, size_t M = 3>
class BTree
{
	typedef BTreeNode<K, M> Node;

public:
	BTree()
		:_root(NULL)
	{}

	// Pair<Node*, int> Node*Ϊ�ڵ�ָ�룬intΪ�ؼ���λ�ã�-1���ʾ������
	Pair<Node*, int> Find(const K& key)
	{
		Node* parent = NULL;
		Node* cur = _root;
		while(cur)
		{
			size_t i = 0;
			while(i < cur->_size && cur->_keys[i] < key)
			{
				++i;
			}

			if (cur->_keys[i] == key)
			{
				return Pair<Node*, int>(cur, i);
			}

			parent = cur;
			cur= cur->_subs[i];
		}

		// û���ҵ�key�򷵻�Ҷ�ӽڵ㣬�±�ֵΪ-1����������Insert/Removeʱ����
		return Pair<Node*, int>(parent, -1);
	}

	bool Insert(const K& key)
	{
		if (_root == NULL)
		{
			_root = new Node();
			_root->_keys[0] = key;
			_root->_size = 1;
			return true;
		}

		Pair<Node*, int> ret = Find(key);
		if (ret._second != -1)
		{
			return false;
		}

		K  k = key;
		Node* cur = ret._first;
		Node* sub = NULL;
		while (cur)
		{
			_InsertKey(cur, k, sub);
			if (cur->_size < M)
				return true;

			// ����
			int boundary = M/2;
			k = cur->_keys[boundary];

			// ���ѳ��½ڵ�
			Node* tmp = new Node();
			int index = 0;
			for (int i = boundary+1; i < cur->_size; ++i)
			{
				tmp->_keys[index] = cur->_keys[i];
				tmp->_subs[index] = cur->_subs[i];
				if (tmp->_subs[index])
					tmp->_subs[index]->_parent = tmp;

				++index;
				tmp->_size++;
				cur->_subs[i] = NULL;
			}

			cur->_size /= 2;

			if (cur->_parent == NULL)
			{
				_root = new Node;
				_root->_keys[0] = k;
				_root->_size = 1;
				_root->_subs[0] = cur;
				_root->_subs[1] = tmp;
				tmp->_parent = cur->_parent = _root;
				return true;
			}

			// ��k��sub���������ڵ����ϲ����
			cur = cur->_parent;
			sub = tmp;
		}

		return true;
	}

	void _InsertKey(Node* cur, const K& key, Node* sub)
	{
		int i = cur->_size - 1;
		while(i >= 0)
		{
			if (cur->_keys[i] > key)
			{
				cur->_keys[i+1] = cur->_keys[i];
				cur->_subs[i+1] = cur->_subs[i];
				++i;
			}
			else
			{
				break;
			}
		}

		cur->_keys[i+1] = key;
		cur->_subs[i+1] = sub;
		cur->_size++;
		if (sub)
			sub->_parent = cur;
	}

protected:
	Node* _root;
};

void TestBTree()
{
	int a[] = {53, 75, 139, 49, 145, 36, 101};
	BTree<int> t1;
	for (int i = 0; i < sizeof(a)/sizeof(int); ++i)
	{
		t1.Insert(a[i]);
	}
}