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
	// �ڵ�����
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	// ��ɫ
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
		// 1.���ڵ���ֱ�Ӵ����ڵ�
		if (_root == NULL)
		{
			// ���ڵ��Ǻ�ɫ��
			_root = new Node(key, value, BLACK);
			return true;
		}

		// 2.���Ҳ����λ�ã�������ڵ�
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

		// 3.������ɫ�����ṹ����ɫ�����������Ĺ���
		while(cur != _root && parent->_colour == RED)
		{
			Node* grandfather = parent->_parent;
			// ���ڵ����游������
			if (parent == grandfather->_left)
			{
				// 1.����ڵ������Ϊ��ɫ--���1
				// 2.������ڵ�/������ڵ�Ϊ��--���2
				// 3.curΪp���Һ��ӣ�����pΪ�ᣬ��������ת��ת��Ϊ���2
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
		// �����Һ���
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		// 1.�Һ��ӵ��������������ڵ����
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		// 2.���ڵ����Һ��ӵ���
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
		// ��������
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

		// ����һ��·���Ϻ�ɫ�ڵ������
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

		// 3.����Ƿ���������ĺ�ڵ�
		if (root->_colour == RED && root->_parent->_colour == RED)
		{
			cout<<"������ڵ�"<<root->_key<<endl;
			return false;
		}

		if (root->_colour == BLACK)
		{
			++count;
		}

		// 4.����ɫ�ڵ�������Ƿ����
		if (root->_left ==  NULL
			&& root->_right == NULL
			&& k != count)
		{
			cout<<"��ɫ�ڵ�����������"<<root->_key<<endl;
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