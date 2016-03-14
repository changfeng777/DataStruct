/******************************************************************************************
Copyright (c) Bit Software, Inc.(2013), All rights reserved.

Purpose: ��������ǰ/��/����������

Author: xjh

Reviser: yyy

Created Time: 2015-8-6
******************************************************************************************/

#pragma once

enum PointerTag {THREAD, LINK};

template<class T>
struct BinaryTreeNodeThd
{
	T _data;						// ����
	BinaryTreeNodeThd<T>* _left;	// ����
	BinaryTreeNodeThd<T>* _right;	// �Һ���
	BinaryTreeNodeThd<T>* _parent;	// ���ڵ㣨Ϊ���������������������
	PointerTag	_leftTag;			// ����������־
	PointerTag	_rightTag;			// �Һ���������־

	BinaryTreeNodeThd(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_leftTag(LINK)
		,_rightTag(LINK)
	{}
};

template<class T>
class BinaryTreeThd
{
public:
	BinaryTreeThd()
		:_root(NULL)
	{}

	/*BinaryTreeThd(const char* array1)
	{
		_CreateTree(_root, array1);
	}*/

	BinaryTreeThd(T array[], size_t size)
	{
		int index = 0;
		_CreateTree(_root, array, size, index);
	}

	void InThreading()
	{
		BinaryTreeNodeThd<T>* prev = NULL;
		_InThreading(_root, prev);
	}

	void PrevThreading()
	{
		BinaryTreeNodeThd<T>* prev = NULL;
		_PrevThreading(_root, prev);
	}

	void PostThreading()
	{
		BinaryTreeNodeThd<T>* prev = NULL;
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
	// ����������
	void _CreateTree(BinaryTreeNodeThd<T>*& root, T array1[], size_t size, int& index)
	{
		if (index < size && array1[index] != '#')
		{
			root = new BinaryTreeNodeThd<T>(array1[index]);
			_CreateTree(root->_left, array1, size, ++index);
			_CreateTree(root->_right, array1, size, ++index);

			if (root->_left)
			{
				root->_left->_parent = root;
			}

			if (root->_right)
			{
				root->_right->_parent = root;
			}
		}
	//}

	// ����������
	//void _CreateTree(BinaryTreeNodeThd<T>*& root, const char*& str)
	//{
	//	//
	//	// ps:�����char* str�����������Ϊ�˷�����ԡ�
	//	// ʵ�ʶ��Ը�char*������������T�����͡�^^
	//	//
	//	if (*str != '\0' && *str != '#')
	//	{
	//		root = new BinaryTreeNodeThd<T>(*str);
	//		_CreateTree(root->_left, ++str);
	//		if (root->_left)
	//		{
	//			root->_left->_parent = root;
	//		}

	//		if (*str == '\0')
	//			return;

	//		_CreateTree(root->_right, ++str);
	//		if (root->_right)
	//		{
	//			root->_right->_parent = root;
	//		}
	//	}
	}

	void _InThreading(BinaryTreeNodeThd<T>* cur, BinaryTreeNodeThd<T>*& prev)
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

	void _PrevThreading(BinaryTreeNodeThd<T>* cur, BinaryTreeNodeThd<T>*& prev)
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

	void _PostThreading(BinaryTreeNodeThd<T>* cur, BinaryTreeNodeThd<T>*& prev)
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

	void _InOrder(BinaryTreeNodeThd<T>* cur)
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

	void _PrevOrder(BinaryTreeNodeThd<T>* cur)
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
			/*while (cur->_rightTag == THREAD && cur->_right)
			{
				cur = cur->_right;
				cout<<cur->_data<<" ";
			}
			cur = cur->_right;*/

			//
			// ������Thread��̽ڵ㣬������������ֱ����ת��ȥ����
			// ���нڵ㶼���ɶ���������·�ڵ�������
			//
			cur = cur->_right;
		}
	}

	void _PostOrder(BinaryTreeNodeThd<T>* root)
	{
		BinaryTreeNodeThd<T>* cur = NULL;
		BinaryTreeNodeThd<T>* prev = NULL;

		if (root)
			cur = root->_left;

		while (cur)
		{
			// �������������ҵ�����ڵ�
			while (cur && cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}

			// ���ʺ�̽ڵ�
			while(cur && cur->_rightTag == THREAD)
			{
				cout<<cur->_data<<" ";
				prev = cur;

				cur = cur->_right;
			}

			if (cur == root)
			{
				cout<<cur->_data<<" ";
				break;
			}

			// �����ǰ�ڵ���ҽڵ��ѷ��ʣ����������ڵ�
			while(cur && cur->_right == prev)
			{
				cout<<cur->_data<<" ";
				prev = cur;

				cur = cur->_parent;			
			}
			
			// �ߵ�ǰ�ڵ������
			if (cur && cur->_rightTag == LINK)
				cur = cur->_right;
		}
	}

private:
	BinaryTreeNodeThd<T>* _root;
};


// ����������������
void TestBinaryTreeThd()
{
	int array1[20] = {1, 2, 3, '#', '#', 4, '#', '#', 5, 6};
	BinaryTreeThd<int> t1(array1, 10);
	t1.InThreading();
	t1.InOrder();

	BinaryTreeThd<int> t2(array1, 10);
	t2.PrevThreading();
	t2.PrevOrder();

	BinaryTreeThd<int> t3(array1, 10);
	t3.PostThreading();
	t3.PostOrder();

	cout<<"==================================="<<endl;

	int array2[15] = {1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8};
	BinaryTreeThd<int> t4(array2, 15);
	t4.InThreading();
	t4.InOrder();

	BinaryTreeThd<int> t5(array2, 15);
	t5.PostThreading();
	t5.PostOrder();

	BinaryTreeThd<int> t6(array2, 15);
	t6.PrevThreading();
	t6.PrevOrder();
}