#pragma once

// Binary Search Tree Node
template<class K, class V>
struct BSTNode
{
	K _key;				// 节点关键值
	V _value;			// 节点数据
	BSTNode* _left;		// 左孩子
	BSTNode* _right;	// 右孩子

	BSTNode(const K& key, const V& data)
		:_key(key)
		,_value(data)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<class K, class V>
class BSTree
{
	typedef BSTNode<K, V> Node;
public:
	BSTree()
		:_root(NULL)
	{}
	~BSTree()
	{}

	// 让学生练习实现，跟前面二叉树部分是一样的
	BSTree(const BSTree& t);
	BSTree&operator=(const BSTree& t);

public:
	BSTNode<K,V>* Find_R(const K& key)
	{
		return _Find(_root, key);
	}

	bool Insert_R(const K& key, const V& data)
	{
		return _Insert(_root, key, data);
	}

	bool Remove_R(const K& key)
	{
		return _Remove(_root, key);
	}

	void PrevOrder()
	{
		_PrevOrder(_root);
		cout<<endl;
	}

	Node* Find(const K& key)
	{
		Node* cur = _root;
		while(cur)
		{
			if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else
			{
				return cur;
			}
		}

		return NULL;
	}

	bool Remove(const K& key)
	{
		if (_root == NULL)
		{
			return false;
		}

		Node* parent = NULL;
		Node* del = _root;
		while (del)
		{
			if (del->_key > key)
			{
				parent = del;
				del = del->_left;
			}
			else if (del->_key < key)
			{
				parent = del;
				del = del->_right;
			}
			else
			{
				break;
			}
		}

		if (del)
		{
			// 左树为空，则用右树调补
			if (del->_left == NULL)
			{
				// 注意删除节点为根节点的情况
				if (_root != del)
				{
					if(del == parent->_left)
						parent->_left = del->_right;
					else
						parent->_right = del->_right;
				}
				else
				{
					_root = del->_right;
				}
				
			}
			else if (del->_right == NULL)
			{
				// 注意删除节点为根节点的情况
				if (_root != del)
				{
					if(del == parent->_left)
						parent->_left = del->_left;
					else
						parent->_right = del->_left;
				}
				else
				{
					_root = del->_right;
				}
			}
			else
			{
				// 查找右子树的中序遍历的第一个节点
				Node* subRight = del->_right; 
				Node* firstInOrder = del->_right;
				Node* parent = del;
				while(firstInOrder->_left)
				{
					parent = firstInOrder;
					firstInOrder = firstInOrder->_left;
				}

				swap(del->_key, firstInOrder->_key);
				swap(del->_value, firstInOrder->_value);

				if (firstInOrder == parent->_left)
				{
					parent->_left = firstInOrder->_right;
				}
				else
				{
					parent->_right = firstInOrder->_right;
				}

				del = firstInOrder;
			}

			delete del;
		}
		else
		{
			return false;
		}

		return true;
	}

	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}

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

		if (parent->_key < key)
			parent->_right = new Node(key, value);
		else
			parent->_left = new Node(key, value);

		return true;
	}

protected:
	void _PrevOrder(BSTNode<K,V>* root)
	{
		if (root)
		{
			_PrevOrder(root->_left);
		//	cout<<"[key:"<<root->_key<<","<<root->_value<<"]"<<"->";
			cout<<root->_key<<", ";
			_PrevOrder(root->_right);
		}
	}

	BSTNode<K,V>* _Find(BSTNode<K,V>* root, const K& key)
	{
		if (root)
		{
			if (root->_key > key)
			{
				return _Find(root->_left, key);
			}
			else if (root->_key < key)
			{
				return _Find(root->_right, key);
			}
			else
			{
				return root;
			}
		}

		return NULL;
	}

	bool _Insert(BSTNode<K,V>*& root, const K& key, const V& data)
	{
		if (root == NULL)
		{
			root = new BSTNode<K,V>(key, data);
			return true;
		}
		else
		{
			if (root->_key > key)
			{
				return _Insert(root->_left, key, data);
			}
			else if (root->_key < key)
			{
				return _Insert(root->_right, key, data);
			}
			else
			{
				return false;
			}
		}
	}
	
	bool _Remove(BSTNode<K,V>*& root, const K& key)
	{
		if (root)
		{
			if(root->_key > key)
			{
				return _Remove(root->_left, key);
			}
			else if(root->_key < key)
			{
				return _Remove(root->_right, key);
			}
			else
			{
				// 1.如果左or右子树为空，则用一个子树进行填补。
				// 2.如果左右均不为空，则使用右子树中序的第一个节点填补
				if (root->_left == NULL)
				{
					BSTNode<K,V>* del = root;
					root = root->_right;
					delete del;
				}
				else if(root->_right == NULL)
				{
					BSTNode<K,V>* del = root;
					root = root->_left;
					delete del;
				}
				else
				{
					// 查找右子树的中序遍历的第一个节点
					BSTNode<K,V>* right = root->_right;
					while (right->_left)
					{
						right = right->_left;
					}

					swap(root->_value, right->_value);
					swap(root->_key, right->_key);
					_Remove(root->_right, right->_key);
				}

				return true;
			}
		}

		return false;
	}

private:
	BSTNode<K,V>* _root;
};

void TestBSTree()
{	
	// 5 3 4 1 7 8 2 6 0 9
	BSTree<int, double> t;
	t.Insert(5,5);
	t.Insert(3,3);
	t.Insert(4,4);
	t.Insert(1,1);
	t.Insert(7,7);
	t.Insert(8,8);
	t.Insert(2,2);
	t.Insert(6,6);
	t.Insert(0,0);
	t.Insert(9,9);

	t.PrevOrder();

	BSTNode<int,double>* ret = t.Find(9);
	cout<<"Find 9 ?: "<<ret->_key<<endl;
	ret = t.Find(10);
	cout<<"Find 10 ?: "<<ret<<endl;

	t.Remove(8);
	t.Remove(1);
	t.Remove(5);

	t.Remove(0);
	t.Remove(1);
	t.Remove(2);
	t.Remove(3);
	t.Remove(4);
	t.Remove(5);
	t.Remove(6);
	t.Remove(7);
	t.Remove(8);
	t.Remove(9);
	t.Remove(10);


	t.PrevOrder();
}