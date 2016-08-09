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
						_RotateL(parent);
						swap(cur, parent);
					}

					grandfather->_colour = RED;
					parent->_colour = BLACK;
					_RotateR(grandfather);
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
						_RotateR(parent);
						swap(cur, parent);
					}

					grandfather->_colour = RED;
					parent->_colour = BLACK;
					_RotateL(grandfather);

				}
			}
		}

		_root->_colour = BLACK;

		return true;
	}

	void _RotateL(Node* parent)
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

		Node* ppNode = parent->_parent;
		parent->_parent = subR;

		if (ppNode == NULL)
		{
			_root = subR;
			subR->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;

			subR->_parent = ppNode;
		}
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

		Node* ppNode = parent->_parent;
		parent->_parent = subL;

		parent = subL;

		if (ppNode == NULL)
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;

			subL->_parent = ppNode;
		}
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}

	bool IsBlance()
	{
		if (_root == NULL)
			return true;

		if (_root->_colour == RED)
			return false;

		// 计算一条路径上黑色节点的数量
		int k = 0;
		Node* cur = _root;
		while(cur)
		{
			if (cur->_colour == BLACK)
				++k;

			cur = cur->_left;
		}

		int count = 0;
		return _IsBlance(_root, k, count);
	}

	bool _IsBlance(Node* root, const int k, int count)
	{
		if (root == NULL)
			return true;

		// 3.检查是否存在连续的红节点
		if (root->_colour == RED && root->_parent->_colour == RED)
		{
			cout<<"连续红节点"<<root->_key<<endl;
			return false;
		}

		if (root->_colour == BLACK)
		{
			++count;
		}

		// 4.检查黑色节点的数量是否相等
		if (root->_left ==  NULL
			&& root->_right == NULL
			&& k != count)
		{
			cout<<"黑色节点的数量不相等"<<root->_key<<endl;
			return false;
		}

		return _IsBlance(root->_left, k, count)
			&& _IsBlance(root->_right, k, count);
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

	cout<<"t1 IsBlance:"<<t1.IsBlance()<<endl;
}