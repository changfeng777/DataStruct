#pragma once

// Binary Search Tree Node
template<class K, class D>
struct BSTNode
{
	K _key;				// 节点关键值
	D _data;			// 节点数据
	BSTNode* _left;		// 左孩子
	BSTNode* _right;	// 右孩子

	BSTNode(const K& key, const D& data)
		:_key(key)
		,_data(data)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<class K, class D>
class BSTree
{
public:
	BSTree()
		:_root(NULL)
	{}
	~BSTree()
	{}
	BSTree(const BSTree& t);
	BSTree&operator=(const BSTree& t);

public:
	BSTNode<K,D>* Find(const K& key)
	{
		return _Find(_root, key);
	}

	bool Insert(const K& key, const D& data)
	{
		return _Insert(_root, key, data);
	}

	bool Remove(const K& key)
	{
		return _Remove(_root, key);
	}

	void PrevOrder()
	{
		_PrevOrder(_root);
		cout<<endl;
	}
protected:
	void _PrevOrder(BSTNode<K,D>* root)
	{
		if (root)
		{
			_PrevOrder(root->_left);
		//	cout<<"[key:"<<root->_key<<","<<root->_data<<"]"<<"->";
			cout<<root->_key<<", ";
			_PrevOrder(root->_right);
		}
	}

	BSTNode<K,D>* _Find(BSTNode<K,D>* root, const K& key)
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

	bool _Insert(BSTNode<K,D>*& root, const K& key, const D& data)
	{
		if (root == NULL)
		{
			root = new BSTNode<K,D>(key, data);
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
	
	bool _Remove(BSTNode<K,D>*& root, const K& key)
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
					BSTNode<K,D>* del = root;
					root = root->_right;
					delete del;
				}
				else if(root->_right == NULL)
				{
					BSTNode<K,D>* del = root;
					root = root->_left;
					delete del;
				}
				else
				{
					// 查找右子树的中序遍历的第一个节点
					BSTNode<K,D>* right = root->_right;
					while (right->_left)
					{
						right = right->_left;
					}

					swap(root->_data, right->_data);
					swap(root->_key, right->_key);
					_Remove(root->_right, right->_key);
				}

				return true;
			}
		}

		return false;
	}

private:
	BSTNode<K,D>* _root;
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

	t.PrevOrder();
}