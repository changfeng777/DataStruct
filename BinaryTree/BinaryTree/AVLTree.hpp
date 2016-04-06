#pragma once

template<class K, class V>
struct AVLTreeNode
{
	// Key/Value
	K _key;
	V _value;

	// 左右孩子及父指针
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	// 平衡因子
	int _bf;

	AVLTreeNode(const K& key = K(), const V& value = V())
		:_key(key)
		,_value(value)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_bf(0)
	{}
};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}

	~AVLTree()
	{}

public:
	bool Insert(const K& key, const V& value)
	{
		// 1.空树
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}

		// 2.查找位置
		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{	
			if (key > cur->_value)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				// 已经存在则返回false
				return false;
			}
		}

		// 3.插入节点
		bool isRotate = false;
		Node* tmp = new Node(key, value);
		if (key < parent->_key)
		{
			parent->_left = tmp;
			tmp->_parent = parent;
		}
		else
		{
			parent->_right = tmp;
			tmp->_parent = parent;
		}

		// 4.更新平衡因子，调整树
		cur = tmp;
		while (parent)
		{
			if (parent->_left == cur)
				--parent->_bf;
			else
				++parent->_bf;

			//
			// 1.bf == 0则直接退出
			// 2.bf==1/-1则说明上层需要调整，则继续向上更新bf
			// 3.bf==2/-2则说明需要调整
			//
			if (parent->_bf == 0)
			{
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = cur->_parent;
			}
			else
			{
				isRotate = true;
				if (parent->_bf == -2)
				{
					if (cur->_bf == -1)
						_RotateR(parent);
					else
						_RotateLR(parent);
				}
				else
				{
					if (cur->_bf == 1)
						_RotateL(parent);
					else
						_RotateRL(parent);
				}

				break;
			}
		}

		// 5.如果进行了旋转调整，则将parent进行重新连接
		if (isRotate)
		{
			Node* ppNode = parent->_parent;
			if (ppNode == NULL)
			{
				_root = parent;
			}
			else
			{
				if(ppNode->_key < parent->_key)
					ppNode->_right = parent;
				else
					ppNode->_left = parent;

			}
		}

		return true;
	}

	bool Remove(const K& key);

	Node* Find(const K& key)
	{
		Node* cur = _root;
		while(cur)
		{
			if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}

		return NULL;
	}

	void InOrder()
	{
		_InOrder(_root);
	}

protected:
	void _RotateL(Node*& parent)
	{
		// 提升右孩子
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		// 1.右孩子的左子树交给父节点的右
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		// 2.父节点变成右孩子的左
		subR->_left = parent;
		subR->_parent = parent->_parent;
		parent->_parent = subR;

		parent->_bf = subR->_bf = 0;
		parent = subR;
	}

	void _RotateR(Node*& parent)
	{
		// 提升左孩子
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		subL->_right = parent;
		subL->_parent = parent->_parent;
		parent->_parent = subL;

		subL->_bf = parent->_bf = 0;
		parent = subL;
	}

	void _RotateLR(Node*& parent)
	{
		_RotateL(parent->_left);
		_RotateR(parent);
	}

	void _RotateRL(Node*& parent)
	{
		_RotateR(parent->_right);
		_RotateL(parent);
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;

		_InOrder(root->_left);
		cout<<root->_key<<":"<<root->_value<<" ";
		_InOrder(root->_right);
	}

protected:
	Node* _root;
};

void TestAVLTree()
{
	AVLTree<int, int> t;
	int a[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
	for (int  i = 0; i < sizeof(a)/sizeof(int); ++i)
	{
		t.Insert(a[i], a[i]);
	}

	t.InOrder();
}