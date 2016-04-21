#pragma once

enum Colour
{
	RED,
	BLACK,
};

template <class K, class V>
struct RBTreeNode
{
	// Key/Value
	K _key;
	V _value;
	// 节点链接
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	// 颜色
	Colour _colour;			

	RBTreeNode(const K& key, const V& value, Colour colour = RED)
		:_key(key)
		,_value(value)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_colour(colour)
	{}
};

template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root(NULL)
	{}

	~RBTree()
	{
		Destory();
		_root = NULL;
	}

public:
	bool Insert(const K& key, const V& value)
	{
		// 1.根节点则直接创建节点
		if (_root == NULL)
		{
			// 根节点是黑色的
			_root = new Node(key, value, BLACK);
			return true;
		}

		// 2.查找插入的位置，并插入节点
		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(key, value);
		if (parent->_key > key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}

		// 3.根据颜色调整结构及颜色，满足红黑树的规则
		while(cur != _root && parent->_colour == RED)
		{
			Node* grandfather = parent->_parent;
			// 父节点是祖父的左孩子
			if (parent == grandfather->_left)
			{
				// 1.叔叔节点存在且为红色--情况1
				// 2.无叔叔节点/或叔叔节点为黑--情况2
				// 3.cur为p的右孩子，则以p为轴，进行左单旋转，转换为情况2
				Node* uncle = grandfather->_right;
				if(uncle && uncle->_colour == RED)
				{
					parent->_colour = BLACK;
					uncle->_colour = BLACK;
					grandfather->_colour = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if(cur == parent->_right)
					{
						_RotateL(parent, _root);
						parent = cur;
					}

					grandfather->_colour = RED;
					parent->_colour = BLACK;
					_RotateR(grandfather, _root);
				}
			}
			else
			{
				Node* uncle = grandfather->_left;
				if(uncle && uncle->_colour == RED)
				{
					parent->_colour = BLACK;
					uncle->_colour = BLACK;
					grandfather->_colour = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if(cur == parent->_left)
					{
						_RotateR(parent, _root);
						parent = cur;
					}

					grandfather->_colour = RED;
					parent->_colour = BLACK;
					_RotateL(grandfather, _root);

				}
			}
		}

		_root->_colour = BLACK;

		return true;
	}

	void _RotateR(Node* parent, Node*& root)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}

		subL->_right = parent;

		if (parent == _root)
		{
			_root = subL;
		}
		else if (parent->_parent->_left == parent)
		{
			parent->_parent->_left = subL;
		}
		else
		{
			parent->_parent->_right = subL;
		}

		subL->_parent = parent->_parent;
		parent->_parent = subL;
	}

	void _RotateL(Node* parent, Node*& root)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}

		subR->_left = parent;

		if (parent == _root)
		{
			_root = subR;
		}
		else if (parent->_parent->_left == parent)
		{
			parent->_parent->_left = subR;
		}
		else
		{
			parent->_parent->_right = subR;
		}

		subR->_parent = parent->_parent;
		parent->_parent = subR;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}

	bool IsBalance()
	{
		return _IsBalance(_root);
	}

	void Destory()
	{
		_Destory(_root);
		_root = NULL;
	}

protected:
	void _Destory(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		_Destory(root->_left);
		_Destory(root->_right);

		delete root;
	}

	bool _IsBalance(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		int left = _IsBalance(root->_left)+1;
		int right = _IsBalance(root->_right)+1;

		if (left > right && left > 2*right)
		{
			return false;
		}

		if(left < right && left*2 < right)
		{
			return false;
		}

		return true;
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);
	}

protected:
	Node* _root;
};

void TestRBTree()
{
	RBTree<int, int> t1;

	int a[] = {10, 7, 8, 15, 5, 6, 11, 13, 12};
	for (size_t i = 0; i < sizeof(a)/sizeof(int); ++i)
	{
		t1.Insert(a[i], i);
	}

	t1.InOrder();

	cout<<"t1 IsBalance:"<<t1.IsBalance()<<endl;

	// 测试是否平衡
	srand(time(0));
	RBTree<int, int> t2;
	for (size_t i = 1; i < 1000; ++i)
	{
		t2.Insert(rand()%1000, i);

		if (i %100 == 0)
		{
			t2.InOrder();
			cout<<"t2 IsBalance:"<<t2.IsBalance()<<endl;
			t2.Destory();
		}
	}
}