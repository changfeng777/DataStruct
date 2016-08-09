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

		return true;
	}

	// 递归实现插入
	bool Insert_R(const K& key, const V& value)
	{
		bool isRotate = false;
		return _Insert_R(_root, key, value, isRotate);
	}

	bool _Insert_R(Node*& root, const K& key, const V& value, bool& isRotate)
	{
		bool ret = false;
		if (root == NULL)
		{
			root = new Node(key, value);
			ret = true;
		}
		else if (root->_key > key)
		{
			ret = _Insert_R(root->_left, key, value, isRotate);
			if (!isRotate)
			{
				root->_bf--;
			}

			if (root->_bf == -2)
			{
				if (root->_left->_bf == -1)
					_RotateR(root);
				else
					_RotateLR(root);

				isRotate = true;
			}
		}
		else if (root->_key < key)
		{
			ret = _Insert_R(root->_right, key, value, isRotate);
			if (!isRotate)
				root->_bf++;

			if (root->_bf == 2)
			{
				if (root->_right->_bf == 1)
					_RotateL(root);
				else
					_RotateRL(root);

				isRotate = true;
			}
		}
		else
		{
			ret = false;
			isRotate = true;
		}

		return ret;
	}

	// 未实现，学生自己下去练习实现
	bool Remove(const K& key);

	Node* Find(const K& key)
	{
		Node* cur = _root;
		while(cur)
		{
			if (cur->_key < key)
				cur = cur->_right;
			else if (cur->_key > key)
				cur = cur->_left;
			else
				return cur;
		}

		return NULL;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}

	bool IsBlanceTree()
	{
		return _IsBlanceTree(_root) < 2;
	}

protected:
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

		parent->_bf = subR->_bf = 0;
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

		subL->_bf = parent->_bf = 0;
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

	// 这样处理在一些场景下平衡因子会有问题
	void _RotateLR(Node*& parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		_RotateL(parent->_left);
		_RotateR(parent);

		//
		// SubLR的平衡因子可能为-1/1/0，
		// 根据三种不同的情况,对平衡因子进行相应的修正
		// 具体参看课件
		//
		if (bf == -1)
		{
			subL->_bf = 0;
			parent->_bf = 1;
		}
		else if (bf == 1)
		{
			subL->_bf = -1;
			parent->_bf = 0;
		}
	}
	
	void _RotateRL(Node*& parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		_RotateR(parent->_right);
		_RotateL(parent);

		//
		// SubRL的平衡因子可能为-1/1/0，
		// 根据三种不同的情况,对平衡因子进行相应的修正
		// 具体参看课件
		//
		if (bf == 1)
		{
			subR->_bf = 0;
			parent->_bf = -1;
		}
		else if (bf == -1)
		{
			subR->_bf = 1;
			parent->_bf = 0;
		}
		else
		{
			subR->_bf = parent->_bf = 0;
		}
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;

		_InOrder(root->_left);
		//cout<<root->_key<<":"<<root->_value<<" ";
		cout<<root->_key<<" ";
		_InOrder(root->_right);
	}

	int _Height(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		int left = _Height(root->_left)+1;
		int right = _Height(root->_right)+1;

		return left > right ? left : right ;
	}

	// 检查是否平衡，并且检查树的平衡因子
	bool _IsBlanceTree(Node* root)
	{
		if (root == NULL)
			return 0;

		int left = _Height(root->_left);
		int right = _Height(root->_right);

		if (abs(root->_bf) != abs(left -right))
		{
			cout<<"平衡因子有问题"<<root->_key<<endl;
			return false;
		}

		return abs(left-right) < 2;
	}

protected:
	Node* _root;
};

void TestAVLTree()
{
	AVLTree<int, int> t1;
	int a1[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
	for (int  i = 0; i < sizeof(a1)/sizeof(int); ++i)
	{
		t1.Insert(a1[i], a1[i]);
	}

	t1.InOrder();

	// t3存在插入的特殊双旋场景，测试AVL树是否正确
	AVLTree<int, int> t3;
	int a3[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
	for (int  i = 0; i < sizeof(a3)/sizeof(int); ++i)
	{
		t3.Insert(a3[i], a3[i]);
	}

	t3.InOrder();

	cout<<"t1是否平衡?:"<<t1.IsBlanceTree()<<endl;
	cout<<"t3是否平衡?:"<<t3.IsBlanceTree()<<endl;
}
