/******************************************************************************************
Copyright (c) Bit Software, Inc.(2013), All rights reserved.

Purpose: 二叉树的中序线索化

Author: xjh

Reviser: yyy

Created Time: 2015-8-6
******************************************************************************************/

#pragma once

enum PointerTag {THREAD, LINK};

template<class T>
struct BinaryTreeNode_Thd
{
	T _data;						// 数据
	BinaryTreeNode_Thd<T>* _left;	// 左孩子
	BinaryTreeNode_Thd<T>* _right;	// 右孩子
	PointerTag	_leftTag;			// 左孩子线索标志
	PointerTag	_rightTag;			// 右孩子线索标志

	BinaryTreeNode_Thd(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
		,_leftTag(LINK)
		,_rightTag(LINK)
	{}
};

template<class T>
class BinaryTree_Thd
{
public:
	BinaryTree_Thd()
		:_root(NULL)
	{}

	// 1.创建二叉树
	void CreateTree(T array[], size_t size)
	{
		int index = 0;
		_CreateTree(_root, array, size, index);
	}

	void InOrder()
	{
		cout<<"InOrder:";
		_InOrder(_root);
		cout<<endl;
	}

	void InThreading()
	{
		BinaryTreeNode_Thd<T>* prev = NULL;
		_InThreading(_root, prev);
	}

	void InOrderThreading()
	{
		cout<<"InOrderThreading:";
		_InOrderThreading(_root);
		cout<<endl;
	}

protected:
	// 构建二叉树
	void _CreateTree(BinaryTreeNode_Thd<T>*& root, T array[], size_t size, int& index)
	{
		if (index < size && array[index] != '#')
		{
			root = new BinaryTreeNode_Thd<T>(array[index]);
			_CreateTree(root->_left, array, size, ++index);
			_CreateTree(root->_right, array, size, ++index);
		}
	}

	void _InOrder(BinaryTreeNode_Thd<T>* root)
	{
		if (root == NULL)
			return;

		_InOrder(root->_left);
		cout<<root->_data<<" ";
		_InOrder(root->_right);
	}

	void _InThreading(BinaryTreeNode_Thd<T>* cur, BinaryTreeNode_Thd<T>*& prev)
	{
		if (cur)
		{
			// 1.线索化左子树
			_InThreading(cur->_left, prev);

			// 2.线索化当前节点的前驱
			if(cur->_left == NULL)
			{
				cur->_leftTag = THREAD;
				cur->_left = prev;
			}
			
			// 3.线索化前驱节点的后继节点
			if (prev && prev->_right == NULL)
			{
				prev->_rightTag = THREAD;
				prev->_right = cur;
			}

			prev = cur;
			
			// 4.线索化右子树
			_InThreading(cur->_right, prev);
		}
	}

	void _InOrderThreading(BinaryTreeNode_Thd<T>* cur)
	{
		while(cur)
		{
			// 走左子树，找到第一个要访问的前取节点
			while (cur && cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}

			// 访问当前节点
			cout<<cur->_data<<" ";

			// 访问连接在一起的后继节点
			while (cur->_rightTag == THREAD && cur->_right)
			{
				cur = cur->_right;
				cout<<cur->_data<<" ";
			}

			cur = cur->_right;
		}
	}

private:
	BinaryTreeNode_Thd<T>* _root;
};


// 测试线索化二叉树
void TestBinaryTreeThd()
{
	int array[20] = {1, 2, 3, '#', '#', 4, '#', '#', 5, 6};
	BinaryTree_Thd<int> tree;
	tree.CreateTree(array, 10);
	tree.InOrder();

	tree.InThreading();
	tree.InOrderThreading();
}