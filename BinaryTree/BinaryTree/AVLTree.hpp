#pragma once

namespace NonRecursion
{
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
			cout<<endl;
		}

		bool IsBlanceTree()
		{
			return _IsBlanceTree(_root) < 2;
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

		// 这样处理在一些场景下平衡因子会有问题
		/*void _RotateLR(Node*& parent)
		{
			_RotateL(parent->_left);
			_RotateR(parent);
		}
		
		void _RotateRL(Node*& parent)
		{
		_RotateR(parent->_right);
		_RotateL(parent);
		}
		*/

		void _RotateLR(Node*& parent)
		{
			// 1.先左单旋转
			Node* subL = parent->_left;
			Node* subLR = subL->_right;
			Node* subLRL = subLR->_left;

			subL->_right = subLRL;
			if (subLRL)
				subLRL->_parent = subL;

			subLR->_left = subL;
			subL->_parent = subLR;

			if (subLR->_bf == -1)
				cout<<"场景2"<<endl;

			// 如果新插入节点在subLR的左边，则subLR->_bf == -1/0时，则subL->_bf = 0。
			// （此处请参考课件旋转图）
			if(subLR->_bf == -1 || subLR->_bf == 0)
				subL->_bf = 0;
			else if (subLR->_bf == 1)
				subL->_bf = -1;
			else
				cout<<"平衡因子异常"<<endl;

			// 2.右单旋转
			Node* subLRR = subLR->_right;
			parent->_left = subLRR;
			if (subLRR)
				subLRR->_parent = parent;

			subLR->_right = parent;
			subLR->_parent = parent->_parent;
			parent->_parent = subLR;

			// 同上
			// （此处请参考课件旋转图）
			if (subLR->_bf == 0 || subLR->_bf == 1)
				parent->_bf = 0;
			else if (subLR->_bf  == -1)
				parent->_bf = 1;
			else
				cout<<"平衡因子异常"<<endl;

			subLR->_bf = 0;

			parent = subLR;
		}

		void _RotateRL(Node*& parent)
		{
			// 1.先右单旋转
			Node* subR = parent->_right;
			Node* subRL = subR->_left;
			Node* subRLR = subRL->_right;

			subR->_left = subRLR;
			if (subRLR)
				subRLR->_parent = subR;
			subRL->_right = subR;
			subR->_parent = subRL;

			if (subRL->_bf == 1)
				cout<<"场景2"<<endl;

			if (subRL->_bf == 0 || subRL->_bf == 1)
				subR->_bf = 0;
			else if (subRL->_bf == -1)
				subR->_bf = 1;
			else
				cout<<"平衡因子异常"<<endl;
			
			// 2.再左单旋转
			Node* subRLL = subRL->_left;
			parent->_right = subRLL;
			if (subRLL)
				subRLL->_parent = parent;

			subRL->_left = parent;
			subRL->_parent = parent->_parent;
			parent->_parent = subRL;

			if (subRL->_bf == 0 || subRL->_bf == -1)
				parent->_bf = 0;
			else if (subRL->_bf == 1)
				parent->_bf = -1;
			else
				cout<<"平衡因子异常"<<endl;

			subRL->_bf = 0;

			parent = subRL;
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

		int _IsBlanceTree(Node* root)
		{
			if (root == NULL)
			{
				return 0;
			}

			int left = _Height(root->_left);
			int right = _Height(root->_right);

			if (abs(root->_bf) != abs(left -right))
			{
				cout<<"平衡因子有问题"<<endl;
			}

			return abs(left-right) <= 1;
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

		AVLTree<int, int> t2;
		int a2[] = {164, 34, 7, 112, 92, 26, 18, 143, 152, 9, 21, 3, 123};
		for (int  i = 0; i < sizeof(a2)/sizeof(int); ++i)
		{
			t2.Insert(a2[i], a2[i]);
		}

		t2.InOrder();

		AVLTree<int, int> t3;
		int a3[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
		for (int  i = 0; i < sizeof(a3)/sizeof(int); ++i)
		{
			t3.Insert(a3[i], a3[i]);
		}

		t3.InOrder();

		cout<<"t1是否平衡?:"<<t1.IsBlanceTree()<<endl;
		cout<<"t2是否平衡?:"<<t2.IsBlanceTree()<<endl;
		cout<<"t3是否平衡?:"<<t3.IsBlanceTree()<<endl;
	}
}

namespace Recursion
{
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
			bool isRotate = false;
			return _Insert(_root, key, value, isRotate);
		}

		bool _Insert(Node*& root, const K& key, const V& value, bool& isRotate)
		{
			bool ret = false;
			if (root == NULL)
			{
				root = new Node(key, value);
				ret = true;
			}
			else if (root->_key > key)
			{
				ret = _Insert(root->_left, key, value, isRotate);
				if (!isRotate)
				{
					root->_bf--;
				}

				if (root->_bf == -2)
				{
					if (root->_left->_bf == -1)
					{
						_RotateR(root);
					}
					else
					{
						_RotateLR(root);
					}

					isRotate = true;
				}
			}
			else if (root->_key < key)
			{
				ret = _Insert(root->_right, key, value, isRotate);
				if (!isRotate)
					root->_bf++;

				if (root->_bf == 2)
				{
					if (root->_right->_bf == 1)
					{
						_RotateL(root);
					}
					else
					{
						_RotateRL(root);
					}

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
			cout<<endl;
		}

		bool IsBlanceTree()
		{
			return _IsBlanceTree(_root) < 2;
		}

	protected:
		void _RotateL(Node*& parent)
		{
			// 提升右孩子
			Node* subR = parent->_right;
			Node* subRL = subR->_left;

			// 1.右孩子的左子树交给父节点的右
			parent->_right = subRL;

			// 2.父节点变成右孩子的左
			subR->_left = parent;

			parent->_bf = subR->_bf = 0;
			parent = subR;
		}

		void _RotateR(Node*& parent)
		{
			// 提升左孩子
			Node* subL = parent->_left;
			Node* subLR = subL->_right;
			
			parent->_left = subLR;

			subL->_right = parent;

			subL->_bf = parent->_bf = 0;
			parent = subL;
		}

		// 这样处理在一些场景下平衡因子会有问题
		/*void _RotateLR(Node*& parent)
		{
			_RotateL(parent->_left);
			_RotateR(parent);
		}
		
		void _RotateRL(Node*& parent)
		{
		_RotateR(parent->_right);
		_RotateL(parent);
		}
		*/

		void _RotateLR(Node*& parent)
		{
			// 1.先左单旋转
			Node* subL = parent->_left;
			Node* subLR = subL->_right;
			Node* subLRL = subLR->_left;

			subL->_right = subLRL;

			subLR->_left = subL;

			if (subLR->_bf == -1)
				cout<<"场景2"<<endl;

			// 如果新插入节点在subLR的左边，则subLR->_bf == -1，则subL->_bf = 0。反之
			// （此处请参考课件旋转图）
			if(subLR->_bf <= 0)
				subL->_bf = 0;
			else
				subL->_bf = -1;

			// 2.右单旋转
			Node* subLRR = subLR->_right;
			parent->_left = subLRR;

			subLR->_right = parent;

			// 如果新插入节点在subLR的右，则subLR->_bf == 1，则parent->_bf = 0。反之
			// （此处请参考课件旋转图）
			if (subLR->_bf <= 1)
				parent->_bf = 0;
			else
				parent->_bf = 1;

			subLR->_bf = 0;

			parent = subLR;
		}

		void _RotateRL(Node*& parent)
		{
			// 1.先右单旋转
			Node* subR = parent->_right;
			Node* subRL = subR->_left;
			Node* subRLR = subRL->_right;

			subR->_left = subRLR;
			subRL->_right = subR;

			if (subRL->_bf == 1)
				cout<<"场景2"<<endl;

			if (subRL->_bf >= 0)
				subR->_bf = 0;
			else
				subR->_bf = 1;
			
			// 2.先左单旋转
			Node* subRLL = subRL->_left;
			parent->_right = subRLL;
			subRL->_left = parent;

			if (subRL->_bf <= 0)
				parent->_bf = 0;
			else
				parent->_bf = -1;

			subRL->_bf = 0;

			parent = subRL;
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

		int _IsBlanceTree(Node* root)
		{
			if (root == NULL)
			{
				return 0;
			}

			int left = _IsBlanceTree(root->_left)+1;
			if (left > 1)
				return left;

			int right = _IsBlanceTree(root->_right)+1;
			if (right > 1)
				return right;

			return abs(left-right);
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

		AVLTree<int, int> t2;
		int a2[] = {164, 34, 7, 112, 92, 26, 18, 143, 152, 9, 21, 3, 123};
		for (int  i = 0; i < sizeof(a2)/sizeof(int); ++i)
		{
			t2.Insert(a2[i], a2[i]);
		}

		t2.InOrder();

		AVLTree<int, int> t3;
		int a3[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
		for (int  i = 0; i < sizeof(a3)/sizeof(int); ++i)
		{
			t3.Insert(a3[i], a3[i]);
		}

		t3.InOrder();

		cout<<"t1是否平衡?:"<<t1.IsBlanceTree()<<endl;
		cout<<"t2是否平衡?:"<<t2.IsBlanceTree()<<endl;
		cout<<"t3是否平衡?:"<<t3.IsBlanceTree()<<endl;
	}
}