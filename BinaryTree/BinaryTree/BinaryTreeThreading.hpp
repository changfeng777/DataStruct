/******************************************************************************************
Copyright (c) Bit Software, Inc.(2013), All rights reserved.

Purpose: ������������������

Author: xjh

Reviser: yyy

Created Time: 2015-8-6
******************************************************************************************/

#pragma once

enum PointerTag {THREAD, LINK};

template<class T>
struct BinaryTreeNode_Thd
{
	T _data;						// ����
	BinaryTreeNode_Thd<T>* _left;	// ����
	BinaryTreeNode_Thd<T>* _right;	// �Һ���
	PointerTag	_leftTag;			// ����������־
	PointerTag	_rightTag;			// �Һ���������־

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

	// 1.����������
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
	// ����������
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
			// 1.������������
			_InThreading(cur->_left, prev);

			// 2.��������ǰ�ڵ��ǰ��
			if(cur->_left == NULL)
			{
				cur->_leftTag = THREAD;
				cur->_left = prev;
			}
			
			// 3.������ǰ���ڵ�ĺ�̽ڵ�
			if (prev && prev->_right == NULL)
			{
				prev->_rightTag = THREAD;
				prev->_right = cur;
			}

			prev = cur;
			
			// 4.������������
			_InThreading(cur->_right, prev);
		}
	}

	void _InOrderThreading(BinaryTreeNode_Thd<T>* cur)
	{
		while(cur)
		{
			// �����������ҵ���һ��Ҫ���ʵ�ǰȡ�ڵ�
			while (cur && cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}

			// ���ʵ�ǰ�ڵ�
			cout<<cur->_data<<" ";

			// ����������һ��ĺ�̽ڵ�
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


// ����������������
void TestBinaryTreeThd()
{
	int array[20] = {1, 2, 3, '#', '#', 4, '#', '#', 5, 6};
	BinaryTree_Thd<int> tree;
	tree.CreateTree(array, 10);
	tree.InOrder();

	tree.InThreading();
	tree.InOrderThreading();
}