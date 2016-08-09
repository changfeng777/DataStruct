#pragma once


// M路平衡B树

template<class K, size_t M = 3>
struct BTreeNode
{
	// KV结构
	//pair<K,V> _kvs[M];

	// 关键字、孩纸
	// 关键字和孩纸都多给一个，先插入节点再进行分裂
	// 简化了分裂逻辑，但是效率会低一些
	K _keys[M];	
	BTreeNode<K, M>* _subs[M+1];		

	size_t _size;						// 关键字个数

	BTreeNode<K, M>* _parent;			// 父亲

	BTreeNode()
		:_parent(NULL)
		,_size(0)
	{
		for (size_t i = 0; i < M+1; ++i)
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

	// pair<Node*, int> Node*为节点指针，int为关键字位置，-1则表示不存在
	pair<Node*, int> Find(const K& key)
	{
		Node* parent = NULL;
		Node* cur = _root;
		while(cur)
		{
			size_t i = 0;
			while(i < cur->_size)
			{
				if (cur->_keys[i] == key)
					return pair<Node*, int>(cur, i);
				else if (cur->_keys[i] < key)
					++i;
				else
					break;
			}

			parent = cur;
			cur= cur->_subs[i];
		}

		// 没有找到key则返回叶子节点，下标值为-1，这样方便Insert/Remove时复用
		return pair<Node*, int>(parent, -1);
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

		pair<Node*, int> ret = Find(key);
		if (ret.second != -1)
		{
			return false;
		}

		// 在cur节点中插入k和sub，最开始sub为空
		// 分裂后把中间节点和分裂出来的节点同样的逻辑往父节点插入
		// 如果插入后cur节点<M，则满足条件，否则一直网上分裂，直到根节点
		//
		K  k = key;
		Node* cur = ret.first;
		Node* sub = NULL;
		while (1)
		{
			_InsertKey(cur, k, sub);
			if (cur->_size < M)
				return true;

			int boundary = M/2;
			k = cur->_keys[boundary];

			// 分裂出新节点
			Node* tmp = new Node();
			// 拷贝key
			int index = 0;
			for (int i = boundary+1; i < cur->_size; ++i)
			{
				tmp->_keys[index++] = cur->_keys[i];
				tmp->_size++;
				cur->_keys[i] = K();
			}
			// 拷贝子节点，注意子节点要多一个
			index = 0;
			for (int i = boundary+1; i <= cur->_size; ++i)
			{
				tmp->_subs[index] = cur->_subs[i];
				if (tmp->_subs[index])
					tmp->_subs[index]->_parent = tmp;
				cur->_subs[i] = NULL;
				++index;
			}
			cur->_size /= 2;

			// 如果已经到根节点，则
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

			// 把k、sub当成新增节点向上层插入
			cur = cur->_parent;
			sub = tmp;
		}

		return true;
	}

	void _InsertKey(Node* cur, const K& key, Node* sub)
	{
		int i = cur->_size-1;
		while(i >= 0)
		{
			if (cur->_keys[i] > key)
			{
				cur->_keys[i+1] = cur->_keys[i];
				// 子节点挪动后面的那一位
				cur->_subs[i+2] = cur->_subs[i+1];
				--i;
			}
			else
			{
				break;
			}
		}

		cur->_keys[i+1] = key;
		cur->_subs[i+2] = sub;
		cur->_size++;
		if (sub)
			sub->_parent = cur;
	}

	void InOrder()
	{
		_InOrder(_root);
	}

	void _InOrder(Node* cur)
	{
		if (cur == NULL)
		{
			return;
		}

		for (size_t i = 0; i < cur->_size; ++i)
		{
			_InOrder(cur->_subs[i]);
			cout<<cur->_keys[i]<<" ";
		}

		_InOrder(cur->_subs[cur->_size]);
	}

protected:
	Node* _root;
};

void TestBTree()
{
	int a[] = {53, 75, 139, 49, 145, 36, 101};
	BTree<int, 5> t1;
	for (int i = 0; i < sizeof(a)/sizeof(int); ++i)
	{
		t1.Insert(a[i]);
	}

	t1.InOrder();
}