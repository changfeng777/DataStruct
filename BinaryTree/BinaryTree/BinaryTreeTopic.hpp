/******************************************************************************************
Copyright (c) Bit Software, Inc.(2013), All rights reserved.

Purpose: ʵ�ֶ������Ļ���������    

Author: xjh

Reviser: yyy

Created Time: 2015-8-6
******************************************************************************************/


//1. ǰ��/����/�������
//2. �������
//3. ��������ĸ߶�
//4. ��Ҷ�ӽڵ�ĸ���
//5. ���������k��Ľڵ����
//6. �ж�һ���ڵ��Ƿ���һ�ö�������
//7. �������ڵ�������������
//8. �ж�һ�ö������Ƿ���ƽ�������
//9. �����������Զ�������ڵ�ľ���


#pragma once

#pragma once
#include<iostream>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

//
// �������½ṹ�����ڶ�����������������в��ԡ�
//
typedef int DataType;

int statistics = 0;

struct BinaryTreeNode_C
{
	DataType _data;			// �������
	BinaryTreeNode_C* _left;	// ������
	BinaryTreeNode_C* _right;	// ������

	// �ڲ�����Զ����ʹ��(����ʽ���)
	int _maxLeftLen;
	int _maxRightLen;

	BinaryTreeNode_C(int data)
		:_data(data)
		,_left(0)
		,_right(0)
	{}
};

void CreateBinaryTree(BinaryTreeNode_C*& root, const vector<DataType>& vDatas, int& i)
{
	// ǰ���������������
	if(i < vDatas.size() && vDatas[i] !=  '#')
	{
		root = new BinaryTreeNode_C(vDatas[i]);
		CreateBinaryTree(root->_left, vDatas, ++i);
		CreateBinaryTree(root->_right, vDatas, ++i);
	}
}

BinaryTreeNode_C* Find(BinaryTreeNode_C* root, DataType x)
{
	BinaryTreeNode_C* ret;
	if (root == NULL)
	{
		return NULL;
	}

	if (root->_data == x)
	{
		return root;
	}

	if (ret = Find(root->_left, x))
	{
		return ret;
	}

	if (ret = Find(root->_right, x))
	{
		return ret;
	}

	return NULL;
}

// ǰ��/����/�������
void PrevOrder(BinaryTreeNode_C* root)
{
	if (root)
	{
		cout<<root->_data<<" ";
		PrevOrder(root->_left);
		PrevOrder(root->_right);
	}
}

void InOrder(BinaryTreeNode_C* root)
{
	if (root)
	{
		InOrder(root->_left);
		cout<<root->_data<<" ";
		InOrder(root->_right);
	}
}

void PostOrder(BinaryTreeNode_C* root)
{
	if (root)
	{
		PostOrder(root->_left);
		PostOrder(root->_right);

		cout<<root->_data<<" ";
	}
}

// ��α�����ӡ������
void LevelOrder(BinaryTreeNode_C* root)
{
	queue<BinaryTreeNode_C*> q;
	if (root)
	{
		q.push(root);
	}

	while (!q.empty())
	{
		BinaryTreeNode_C* node = q.front();
		cout<<node->_data<<" ";

		if (node->_left)
		{
			q.push(node->_left);
		}

		if (node->_right)
		{
			q.push(node->_right);
		}
		q.pop();
	}
}

// ��߶�
int GetHeight(BinaryTreeNode_C* root)
{
	statistics++;

	if (root)
	{
		int leftHeight, rightHight;

		leftHeight = GetHeight(root->_left) + 1;
		rightHight = GetHeight(root->_right);

		return leftHeight > rightHight ? leftHeight : rightHight;
	}

	return 0;
}

// Ҷ�ӽڵ����
int GetLeafNum(BinaryTreeNode_C* root)
{
	if(root == NULL)
		return 0;

	// �����Ҷ�ӽڵ��򷵻�1
	if (root->_left == NULL && root->_right == NULL)
	{
		return 1;
	}

	return GetLeafNum(root->_left) + GetLeafNum(root->_right);
}

// ���K��Ľڵ����
int GetKLevelNum (BinaryTreeNode_C* root, int k)
{
	if (root == NULL || k < 1)
	{
		return 0;
	}

	if (k == 1)
	{
		return 1;
	}

	return GetKLevelNum(root->_left, k-1) + GetKLevelNum(root->_right, k-1);
}

// �ж�һ���ڵ��Ƿ���һ������
bool IsInTree(BinaryTreeNode_C* root, BinaryTreeNode_C* node)
{
	if (root == NULL)
	{
		return false;
	}

	if(node == root)
	{
		return true;
	}

	if (IsInTree(root->_left, node) || IsInTree(root->_right, node))
	{
		return true;
	}

	return false;
}

// �������ڵ�������������
//
// 1.���һ���ڵ�Ϊ����㣬��һ���ڵ���һ�������У�����ڵ�Ϊ���Ƚڵ㡣
// 2.���һ���ڵ�������������һ���ڵ�������������ǰ���ڵ㼴Ϊ���Ƚڵ㡣
// 3.�����������������������������ת��Ϊ�����⣬������ʹ�õݹ���⡣
//
BinaryTreeNode_C* GetCommontAncestor(BinaryTreeNode_C* root,
								   BinaryTreeNode_C* x1, BinaryTreeNode_C* x2)
{
	// 1.���һ���ڵ�Ϊ����㣬��һ���ڵ���һ�������У�����ڵ�Ϊ���Ƚڵ㡣
	if(root == x1 && IsInTree(root, x2))
	{
		return root;
	}
	if (root == x2 && IsInTree(root, x1))
	{
		return root;
	}

	// 2.���һ���ڵ�������������һ���ڵ�������������ǰ���ڵ㼴Ϊ���Ƚڵ㡣
	bool x1InLeft = false, x2InLeft = false, x1InRight = false, x2InRight = false;
	x1InLeft = IsInTree(root->_left, x1);
	x2InRight = IsInTree(root->_right, x2);
	if (x1InLeft&&x2InRight)
	{
		return root;
	}

	x1InRight = IsInTree(root->_right, x1);
	x2InLeft = IsInTree(root->_left, x2);

	if (x1InLeft && x2InRight)
	{
		return root;
	}

	// 3.�����������������������������ת��Ϊ�����⣬������ʹ�õݹ���⡣
	if (x1InLeft && x2InLeft)
	{
		return GetCommontAncestor(root->_left, x1, x2);
	}
	if (x1InRight && x2InRight)
	{
		return GetCommontAncestor(root->_right, x1, x2);
	}

	return NULL;
}

// �Ż�
bool GetNodePath(BinaryTreeNode_C* root, 
				 stack<BinaryTreeNode_C*>& s,
				 BinaryTreeNode_C* x)
{
	if (root)
	{
		// �ڵ���ջ
		s.push(root);

		// �ҵ��ڵ��򷵻�true
		if (root == x)
		{
			return true;
		}

		// �ֱ������������
		if(root->_left && GetNodePath(root->_left, s, x))
		{
			return true;
		}

		if (root->_right && GetNodePath(root->_right, s, x))
		{
			return true;
		}

		// ����������û���ҵ������ջջ���ڵ㡣
		s.pop();
	}

	return false;
}

// �Ż�
BinaryTreeNode_C* GetCommontAncestor_OP(BinaryTreeNode_C* root,
									  BinaryTreeNode_C* x1, BinaryTreeNode_C* x2)
{
	// ��ȡ�����ڵ�Ĳ���·��
	stack<BinaryTreeNode_C*> s1;
	stack<BinaryTreeNode_C*> s2;
	GetNodePath(root, s1, x1);
	GetNodePath(root, s2, x2);

	// ������һ����ͬ�Ľڵ���Ϊ���Ƚڵ�
	while (!s1.empty() && !s2.empty())
	{
		if (s1.top() == s2.top())
		{
			return s1.top();
		}

		s1.pop();
		s2.pop();
	}

	return 0;
}

// �ж�һ�ö������Ƿ���ƽ������ƽ������AVL�ı�׼��
bool IsBalance(BinaryTreeNode_C* root)
{
	statistics++;

	if (root == NULL || (root->_left == NULL && root->_right == NULL))
	{
		return true;
	}

	// 1.�жϵ�ǰ���Ƿ�Ϊƽ����
	int leftH = GetHeight(root->_left);
	int rightH = GetHeight(root->_right);

	int interval = leftH - rightH;
	if (interval > 1 || interval < -1)
	{
		return false;
	}

	// 2.�ж����������Ƿ�Ϊƽ����
	return IsBalance(root->_left) && IsBalance(root->_right);
}

// �Ż�
bool IsBalance_OP(BinaryTreeNode_C* root, int& height)
{
	statistics++;

	// 1.�жϵ�ǰ���Ƿ���ƽ����
	if (root == NULL)
	{
		height = 0;
		return true;
	}

	if (root->_left == NULL && root->_right)
	{
		height = 1;
		return true;
	}

	// 2.�ж����������Ƿ���ƽ��������������������ĸ߶ȣ�ͨ���߶��жϵ�ǰ���Ƿ���ƽ����
	int leftH = 0;
	int rightH = 0;
	if(IsBalance_OP(root->_right, rightH) && IsBalance_OP(root->_left, leftH))
	{
		int interval = leftH - rightH;
		if (interval <= 1 && interval >= -1)
		{
			height = leftH > rightH ? leftH : rightH;
			height += 1;
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

//
// ��һ�ö���������Զ�������ڵ�ľ��롣
// http://www.cnblogs.com/miloyip/archive/2010/02/25/binary_tree_distance.html
//
int maxLen = 0;
void FindMaxLen(BinaryTreeNode_C* root)
{
	// 1.���ڵ�Ϊ����ֱ�ӷ���
	if(root == NULL)
	{
		return;
	}

	// 2.��������Ϊ�գ�����뵱ǰ�ڵ�ľ���Ϊ0
	if (root->_left == NULL)
	{
		root->_maxLeftLen = 0;
	}
	if (root->_right == NULL)
	{
		root->_maxRightLen = 0;
	}

	// 3.�ݹ�������������ľ�����ڵ�ľ���
	if (root->_left)
	{
		FindMaxLen(root->_left);
	}

	if (root->_right)
	{
		FindMaxLen(root->_right);
	}

	// 4.������������������ڵ����󳤶�
	if (root->_left)
	{
		int tmp = root->_left->_maxLeftLen > root->_left->_maxRightLen ? \
			root->_left->_maxLeftLen : root->_left->_maxRightLen;

		root->_maxLeftLen = tmp + 1;
	}

	if (root->_right)
	{
		int tmp = root->_right->_maxLeftLen > root->_right->_maxRightLen ? \
			root->_right->_maxLeftLen : root->_right->_maxRightLen;

		root->_maxRightLen = tmp + 1;
	}

	// 5.������Զ����
	if (maxLen < root->_maxLeftLen + root->_maxRightLen)
	{
		maxLen = root->_maxRightLen + root->_maxLeftLen;
	}
}

// ������������
// 1.ȫ�ֱ��������̰߳�ȫ������
// 2.��Ҫ�ı�������ڵ�Ľṹ����Ҳ����ν������ʽ��̣�
// 3.�߼��жϸ���

// �Ż�
void FindMaxLen_OP1(BinaryTreeNode_C* root, int& maxLen)
{
	if (root == NULL)
	{
		maxLen = 0;
		return;
	}

	int l = GetHeight(root->_left); 
	int r = GetHeight(root->_right);

	if (maxLen < l + r)
	{
		maxLen = l + r;
	}

	FindMaxLen_OP1(root->_left, maxLen);
	FindMaxLen_OP1(root->_right, maxLen);
}

// ���Ż�
int FindMaxLen_OP2(BinaryTreeNode_C* root, int& maxLen)
{
	if (root == NULL)
	{
		maxLen = 0;
		return -1;
	}

	int l = FindMaxLen_OP2(root->_left, maxLen) + 1; 
	int r = FindMaxLen_OP2(root->_right, maxLen) + 1;

	if (maxLen < l + r)
	{
		maxLen = l + r;
	}

	return l > r ? l : r;
}

// ���Զ����������
void TestBinaryTreeTopic()
{
	cout<<endl;
	cout<<"TestBinaryTreeTopic:"<<endl;
	BinaryTreeNode_C* root = 0;

	//	    1
	//    /   \
	//	 2	   5	
	//  / \	  /	
	// 3   4  6
	//

	// 123##4##56
	vector<DataType> t;
	t.push_back(1);
	t.push_back(2);
	t.push_back(3);
	t.push_back('#');
	t.push_back('#');
	t.push_back(4);
	t.push_back('#');
	t.push_back('#');
	t.push_back(5);
	t.push_back(6);

	for (size_t i = 0; i < t.size(); ++i)
	{
		cout<<t[i]<<" ";
	}
	cout<<endl;

	int index = 0;
	CreateBinaryTree(root, t, index);

	cout<<"prev:";
	PrevOrder(root);
	cout<<endl;

	cout<<"In:";
	InOrder(root);
	cout<<endl;

	cout<<"Post:";
	PostOrder(root);
	cout<<endl;

	cout<<"Level:";
	LevelOrder(root);
	cout<<endl;

	cout<<"Height:"<<GetHeight(root)<<endl;
	cout<<"Leaf Number:"<<GetLeafNum(root)<<endl;

	BinaryTreeNode_C* ret = Find(root, 3);
	cout<<"Is 3 In The Tree:"<<IsInTree(root, ret)<<endl;

	BinaryTreeNode_C* x1 = Find(root, 4);
	BinaryTreeNode_C* x2 = Find(root, 5);
	ret = GetCommontAncestor_OP(root, x1, x2);
	if (ret)
	{
		cout<<"3 & 6 Commont Ancestor Is:"<<ret->_data<<endl;
	}
	else
	{
		cout<<"Not Find Commont Ancestor"<<endl;
	}

	statistics = 0;
	int height = 0;
	cout<<"Tree Is Balance Tree ? : "<<IsBalance(root)<<endl;
	cout<<statistics<<endl;

	statistics = 0;
	cout<<"OP Tree Is Balance Tree ? : "<<IsBalance_OP(root, height)<<endl;
	cout<<statistics<<endl;

	cout<<"k Level Num:"<<GetKLevelNum(root, 3)<<endl;

	FindMaxLen(root);
	cout<<"Max Len:"<<maxLen<<endl;

	maxLen = 0;
	FindMaxLen_OP1(root, maxLen);
	cout<<"OP1 Max Len:"<<maxLen<<endl;

	maxLen = 0;
	FindMaxLen_OP2(root, maxLen);
	cout<<"OP2 Max Len:"<<maxLen<<endl;
};