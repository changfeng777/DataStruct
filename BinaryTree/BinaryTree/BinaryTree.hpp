/******************************************************************************************
Copyright (c) Bit Software, Inc.(2013), All rights reserved.

Purpose: 实现二叉树的基本操作     

Author: xjh

Reviser: yyy

Created Time: 2015-8-6
******************************************************************************************/
#pragma once

#include<queue>
#include<stack>

// 一般二叉树实现接口实现

template<class T>
struct BinaryTreeNode
{
	T _data;					// 数据
	BinaryTreeNode<T>* _left;	// 左孩子
	BinaryTreeNode<T>* _right;	// 右孩子

	BinaryTreeNode(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<class T>
class BinaryTree
{
public:
	BinaryTree()
		:_root(NULL)
	{}

	BinaryTree(T array[], size_t size)
	{
		// 1.创建二叉树
		int index = 0;
		_CreateTree(_root, array, size, index);
	}

	

	//
	// 实现深拷贝二叉树
	//
	BinaryTree(const BinaryTree<T>& t)
	{
		this->_root = _CopyTree(t._root);
	}

	/*BinaryTree<T>& operator=(const BinaryTree<T>& t)
	{
		if (this != &t)
		{
			this->Destory();
			this->_root = _CopyTree(t._root);
		}

		return *this;
	}*/

	BinaryTree<T>& operator=(BinaryTree<T> t)
	{
		swap(_root, t._root);
		return *this;
	}

	~BinaryTree()
	{
		Destory();
	}

	// 2.遍历二叉树(前序、中序、后序、层序)
	void PrevOrder()
	{
		cout<<"PrevOrder:";
		_PrevOrder(_root);
		cout<<endl;
	}

	void InOrder()
	{
		cout<<"InOrder:";
		_InOrder(_root);
		cout<<endl;
	}
	void PostOrder()
	{
		cout<<"PostOrder:";
		_PostOrder(_root);
		cout<<endl;
	}

	void LevelOrder()
	{
		cout<<"LevelOrder:";
		if (_root == NULL)
			return;

		// 1.入队列根节点
		queue<BinaryTreeNode<T>*> q;
		q.push(_root);

		// 队列为空时遍历完成
		while (!q.empty())
		{
			BinaryTreeNode<T>* root = q.front();
			if (root->_left)
			{
				q.push(root->_left);
			}

			if (root->_right)
			{
				q.push(root->_right);
			}

			cout<<root->_data<<" ";
			q.pop();
		}
		cout<<endl;
	}

	// 非递归实现前/中/后序遍历
	void PrevOrder_NonR()
	{
		cout<<"PrevOrder_NonR:";
		stack<BinaryTreeNode<T>*> s;
		if (_root)
		{
			s.push(_root);
		}

		while (!s.empty())
		{
			//
			// 先访问根节点，先入右节点再入左节点，
			// 出栈时才能先访问到左节点，再访问到右节点。
			//
			BinaryTreeNode<T>* root = s.top();
			cout<<root->_data<<" ";
			s.pop();

			if (root->_right)
			{
				s.push(root->_right);
			}

			if (root->_left)
			{
				s.push(root->_left);
			}
		}

		cout<<endl;
	}

	void InOrder_NonR()
	{
		cout<<"InOrder_NonR:";
		stack<BinaryTreeNode<T>*> s;

		BinaryTreeNode<T>* cur = _root;

		while (cur || !s.empty())
		{
			// 1.先将左节点全部入栈
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			//
			// 2.栈不为空时，访问栈顶节点。
			// 将cur指向栈顶节点的右子树，继续中序遍历右子树。
			//
			if (!s.empty())
			{
				BinaryTreeNode<T>* top = s.top();
				cout<<top->_data<<" ";
				s.pop();
				cur = top->_right;
			}
		}

		cout<<endl;
	}

	void PostOrder_NonR()
	{
		cout<<"PostOrder_NonR:";
		stack<BinaryTreeNode<T>*> s;
		BinaryTreeNode<T>* cur = _root;
		BinaryTreeNode<T>* prevVisited = NULL;

		while (cur || !s.empty())
		{
			// 入栈做孩子节点
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			// 2.右节点为空/之前右节点已经访问过了的时候访问当前的栈顶节点
			BinaryTreeNode<T>* top = s.top();
			if (top->_right == NULL || prevVisited == top->_right)
			{
				cout<<top->_data<<" ";
				s.pop();
				prevVisited = top;
			}
			else
			{
				cur = top->_right;
			}
		}

		cout<<endl;
	}


	// 3.查找
	BinaryTreeNode<T>* Find(const T& x)
	{
		return _Find(_root, x);
	}

	int Height()
	{
		return _Height(_root);
	}

	int Size()
	{
		return _Size(_root);
	}

	void Destory()
	{
		_Destory(_root);
		_root = NULL;
	}

protected:
	// 构建二叉树
	void _CreateTree(BinaryTreeNode<T>*& root, T array[], size_t size, int& index)
	{
		if (index < size && array[index] != '#')
		{
			root = new BinaryTreeNode<T>(array[index]);
			_CreateTree(root->_left, array, size, ++index);
			_CreateTree(root->_right, array, size, ++index);
		}
	}

	void _PrevOrder(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
			return;

		cout<<root->_data<<" ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}

	void _InOrder(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
			return;

		_InOrder(root->_left);
		cout<<root->_data<<" ";
		_InOrder(root->_right);
	}

	void _PostOrder(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
			return;

		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout<<root->_data<<" ";
	}

	BinaryTreeNode<T>* _Find(BinaryTreeNode<T>* root, const T& x)
	{
		if (root == NULL)
			return  NULL;

		if (root->_data == x)
			return root;

		BinaryTreeNode<T>* ret = NULL;
		if (ret = _Find(root->_left, x))
		{
			return ret;
		}

		if (ret = _Find(root->_right, x))
		{
			return ret;
		}

		return NULL;
	}

	int _Height(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		int leftHeight = _Height(root->_left) + 1;
		int rightHeight = _Height(root->_right) + 1;

		return leftHeight > rightHeight ? leftHeight : rightHeight;
	}

	int _Size(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		return _Size(root->_left) + _Size(root->_right) + 1;
	}

	// 拷贝二叉树
	BinaryTreeNode<T>* _CopyTree(BinaryTreeNode<T>* root)
	{
		BinaryTreeNode<T>* newRoot = NULL;
		if (root)
		{
			newRoot = new BinaryTreeNode<T>(root->_data);
			newRoot->_left = _CopyTree(root->_left);
			newRoot->_right = _CopyTree(root->_right);
		}

		return newRoot;
	}


	void _Destory(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
			return;
		
		_Destory(root->_left);
		_Destory(root->_right);

		delete root;
	}

private:
	BinaryTreeNode<T>* _root;	// 根节点
};

// 测试二叉树
void TestBinaryTree()
{
	cout<<"TestBinaryTree:"<<endl;

	int array[20] = {1, 2, 3, '#', '#', 4, '#', '#', 5, 6};
	BinaryTree<int> tree(array, 10);

	tree.PrevOrder();
	tree.PrevOrder_NonR();
	tree.InOrder();
	tree.InOrder_NonR();
	tree.PostOrder();
	tree.PostOrder_NonR();
	tree.LevelOrder();

	BinaryTreeNode<int>* ret = tree.Find(3);
	cout<<"Find 3?: "<<ret->_data<<endl;

	ret = tree.Find(10);
	cout<<"Find 10?: "<<ret<<endl;

	cout<<"Height:"<<tree.Height()<<endl;

	BinaryTree<int> treeCopy1 = tree;
	treeCopy1.PrevOrder();

	BinaryTree<int> treeCopy2;
	treeCopy2 = tree;
	treeCopy2.PrevOrder();
}

// 二叉树三叉链结构--带
template<class T>
struct BinaryTreeNode_P
{
	T _data;							// 数据
	BinaryTreeNode_P<T>* _left;		// 左孩子
	BinaryTreeNode_P<T>* _right;	// 右孩子
	BinaryTreeNode_P<T>* _parent;	// 父节点

	BinaryTreeNode_P(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
	{}
};

template<class T>
class BinaryTree_P
{
public:
	BinaryTree_P(T array[], size_t size)
	{
		int index = 0;
		_CreateTree(_root, array, size, index);
	}
protected:
	// 构建二叉树
	void _CreateTree(BinaryTreeNode_P<T>*& root, T array[], size_t size, int& index)
	{
		if (index < size && array[index] != '#')
		{
			root = new BinaryTreeNode_P<T>(array[index]);
			_CreateTree(root->_left, array, size, ++index);
			// 更新父节点
			if (root->_left)
				root->_left->_parent = root;

			_CreateTree(root->_right, array, size, ++index);

			// 更新父节点
			if (root->_right)
				root->_right->_parent = root;
		}
	}
private:
	BinaryTreeNode_P<T>* _root;
};

// 测试二叉树
void TestBinaryTree_P()
{
	int array[20] = {1, 2, 3, '#', '#', 4, '#', '#', 5, 6};
	BinaryTree_P<int> tree(array, 10);
}