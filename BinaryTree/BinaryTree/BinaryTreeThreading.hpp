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
	BinaryTreeNode_Thd<T>* _parent;	// ���ڵ㣨Ϊ���������������������
	PointerTag	_leftTag;			// ����������־
	PointerTag	_rightTag;			// �Һ���������־

	BinaryTreeNode_Thd(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
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

	BinaryTree_Thd(const char* array)
	{
		_CreateTree(_root, array);
	}

	// 1.����������
	/*void CreateTree(T array[], size_t size)
	{
		int index = 0;
		_CreateTree(_root, array, size, index);
	}*/

	void InThreading()
	{
		BinaryTreeNode_Thd<T>* prev = NULL;
		_InThreading(_root, prev);
	}

	void PrevThreading()
	{
		BinaryTreeNode_Thd<T>* prev = NULL;
		_PrevThreading(_root, prev);
	}

	void PostThreading()
	{
		BinaryTreeNode_Thd<T>* prev = NULL;
		_PostThreading(_root, prev);
	}

	void InOrder()
	{
		cout<<"InOrder:";
		_InOrder(_root);
		cout<<endl;
	}

	void PrevOrder()
	{
		cout<<"PrevOrder:";
		_PrevOrder(_root);
		cout<<endl;
	}

	void PostOrder()
	{
		cout<<"PostOrder:";
		_PostOrder(_root);
		cout<<endl;
	}

protected:
	//// ����������
	//void _CreateTree(BinaryTreeNode_Thd<T>*& root, T array[], size_t size, int& index)
	//{
	//	if (index < size && array[index] != '#')
	//	{
	//		root = new BinaryTreeNode_Thd<T>(array[index]);
	//		_CreateTree(root->_left, array, size, ++index);
	//		_CreateTree(root->_right, array, size, ++index);

	//		if (root->_left)
	//		{
	//			root->_left->_parent = root;
	//		}

	//		if (root->_right)
	//		{
	//			root->_right->_parent = root;
	//		}
	//	}
	//}

	// ����������
	void _CreateTree(BinaryTreeNode_Thd<T>*& root, const char*& str)
	{
		//
		// ps:�����char* str�����������Ϊ�˷�����ԡ�
		// ʵ�ʶ��Ը�char*������������T�����͡�^^
		//
		if (*str != '\0' && *str != '#')
		{
			root = new BinaryTreeNode_Thd<T>(*str);
			_CreateTree(root->_left, ++str);
			if (root->_left)
			{
				root->_left->_parent = root;
			}

			if (*str == '\0')
				return;

			_CreateTree(root->_right, ++str);
			if (root->_right)
			{
				root->_right->_parent = root;
			}
		}
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

	void _PrevThreading(BinaryTreeNode_Thd<T>* cur, BinaryTreeNode_Thd<T>*& prev)
	{
		if(cur)
		{
			// 1.��������ǰ�ڵ��ǰ��
			if (cur->_left == NULL)
			{
				cur->_leftTag = THREAD;
				cur->_left = prev;
			}

			// 2.������ǰһ���ڵ�ĺ��Ϊ��ǰ�ڵ�
			if (prev && prev->_right == NULL)
			{
				prev->_rightTag = THREAD;
				prev->_right = cur;
			}

			prev = cur;

			// ֻ��LINK�Ľڵ����Ҫ�ݹ飬����ǰ������Ľڵ�����������
			if (cur->_leftTag == LINK)
				_PrevThreading(cur->_left, prev);

			if (cur->_rightTag == LINK)
				_PrevThreading(cur->_right, prev);
		}
	}

	void _PostThreading(BinaryTreeNode_Thd<T>* cur, BinaryTreeNode_Thd<T>*& prev)
	{
		if(cur)
		{
			// ֻ��LINK�Ľڵ����Ҫ�ݹ飬����ǰ������Ľڵ�����������
			if (cur->_leftTag == LINK)
				_PostThreading(cur->_left, prev);

			if (cur->_rightTag == LINK)
				_PostThreading(cur->_right, prev);

			// 1.��������ǰ�ڵ��ǰ��
			if (cur->_left == NULL)
			{
				cur->_leftTag = THREAD;
				cur->_left = prev;
			}

			// 2.������ǰһ���ڵ�ĺ��Ϊ��ǰ�ڵ�
			if (prev && prev->_right == NULL)
			{
				prev->_rightTag = THREAD;
				prev->_right = cur;
			}

			prev = cur;
		}
	}

	void _InOrder(BinaryTreeNode_Thd<T>* cur)
	{
		while(cur)
		{
			// �����������ҵ���һ��Ҫ���ʵ�ǰ���ڵ�
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

	void _PrevOrder(BinaryTreeNode_Thd<T>* cur)
	{
		while(cur)
		{
			// ǰ�����·���ϵ������ڵ�
			while (cur)
			{
				// ���ʵ�ǰ�ڵ�
				cout<<cur->_data<<" ";
				if (cur->_leftTag == THREAD)
					break;

				cur = cur->_left;
			}

			// ����������һ��ĺ�̽ڵ�
			while (cur->_rightTag == THREAD && cur->_right)
			{
				cur = cur->_right;
				cout<<cur->_data<<" ";
			}

			cur = cur->_right;
		}
	}

	void _PostOrder(BinaryTreeNode_Thd<T>* root)
	{
		BinaryTreeNode_Thd<T>* cur = NULL;
		BinaryTreeNode_Thd<T>* visited = NULL;

		if (root)
			cur = root->_left;

		while (cur != root)
		{
			// ��������
			while (cur && cur->_leftTag == LINK && cur->_left != visited)
			{
				cur = cur->_left;
			}

			// ���ʺ�̽ڵ�
			while(cur && cur->_rightTag == THREAD)
			{
				cout<<cur->_data<<" ";
				visited = cur;

				cur = cur->_right;
			}

			if (cur == root)
			{
				cout<<cur->_data<<" ";
				return;
			}

			// �����ǰ�ڵ���ҽڵ��ѷ��ʣ����������ڵ�
			while(cur && cur->_right == visited)
			{
				cout<<cur->_data<<" ";
				visited = cur;

				cur = cur->_parent;			
			}
			
			// �ߵ�ǰ�ڵ������
			if (cur && cur->_rightTag == LINK)
				cur = cur->_right;
		}
	}

private:
	BinaryTreeNode_Thd<T>* _root;
};


// ����������������
void TestBinaryTreeThd()
{
	/*int array[20] = {1, 2, 3, '#', '#', 4, '#', '#', 5, 6};
	BinaryTree_Thd<int> tree;
	tree.CreateTree(array, 10);*/

	// HDA##C#B##GF#E

	//char* str = "HDA##C#B##GF#E";
	char* str = "123##4##56";
	BinaryTree_Thd<char> tree(str);

	
	//tree.InOrder();

	//tree.InThreading();
	//tree.InOrder();

	//tree.PrevThreading();
	//tree.PrevOrder();

	tree.PostThreading();
	tree.PostOrder();
}