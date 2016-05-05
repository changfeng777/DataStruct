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
//10. ��ǰ���������������ؽ���������ǰ�����У�1 2 3 4 5 6 - ��������:3 2 4 1 5 6��
//11. �ж�һ�����Ƿ�����ȫ������
//12. ��������ľ���y��
//13. ������������ת��Ϊ˫������


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

namespace Topic
{

struct BinaryTreeNode
{
	DataType _data;				// �������
	BinaryTreeNode* _left;	// ������
	BinaryTreeNode* _right;	// ������

	// �ڲ�����Զ����ʹ��(����ʽ���)
	int _maxLeftLen;
	int _maxRightLen;

	BinaryTreeNode(int data)
		:_data(data)
		,_left(0)
		,_right(0)
	{}
};

void CreateBinaryTree(BinaryTreeNode*& root, const vector<DataType>& vDatas, int& i)
{
	// ǰ���������������
	if(i < vDatas.size() && vDatas[i] !=  '#')
	{
		root = new BinaryTreeNode(vDatas[i]);
		CreateBinaryTree(root->_left, vDatas, ++i);
		CreateBinaryTree(root->_right, vDatas, ++i);
	}
}

BinaryTreeNode* Find(BinaryTreeNode* root, DataType x)
{
	BinaryTreeNode* ret;
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
void PrevOrder(BinaryTreeNode* root)
{
	if (root)
	{
		cout<<root->_data<<" ";
		PrevOrder(root->_left);
		PrevOrder(root->_right);
	}
}

void InOrder(BinaryTreeNode* root)
{
	if (root)
	{
		InOrder(root->_left);
		cout<<root->_data<<" ";
		InOrder(root->_right);
	}
}

void PostOrder(BinaryTreeNode* root)
{
	if (root)
	{
		PostOrder(root->_left);
		PostOrder(root->_right);

		cout<<root->_data<<" ";
	}
}

// ��α�����ӡ������
void LevelOrder(BinaryTreeNode* root)
{
	queue<BinaryTreeNode*> q;
	if (root)
	{
		q.push(root);
	}

	while (!q.empty())
	{
		BinaryTreeNode* node = q.front();
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
int GetHeight(BinaryTreeNode* root)
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
int GetLeafNum(BinaryTreeNode* root)
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
int GetKLevelNum (BinaryTreeNode* root, int k)
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
bool IsInTree(BinaryTreeNode* root, BinaryTreeNode* node)
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
BinaryTreeNode* GetCommontAncestor(BinaryTreeNode* root,
								   BinaryTreeNode* x1, BinaryTreeNode* x2)
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
bool GetNodePath(BinaryTreeNode* root, 
				 stack<BinaryTreeNode*>& s,
				 BinaryTreeNode* x)
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
BinaryTreeNode* GetCommontAncestor_OP(BinaryTreeNode* root,
									  BinaryTreeNode* x1, BinaryTreeNode* x2)
{
	// ��ȡ�����ڵ�Ĳ���·��
	stack<BinaryTreeNode*> s1;
	stack<BinaryTreeNode*> s2;
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
bool IsBalance(BinaryTreeNode* root)
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
bool IsBalance_OP(BinaryTreeNode* root, int& height)
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
void FindMaxLen(BinaryTreeNode* root)
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
void FindMaxLen_OP1(BinaryTreeNode* root, int& maxLen)
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
int FindMaxLen_OP2(BinaryTreeNode* root, int& maxLen)
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

//10. ��ǰ���������������ؽ���������ǰ�����У�1 2 3 4 5 6 - ��������:3 2 4 1 6 5)
BinaryTreeNode* _RebulidTree(int prevOrder[], int& index, int inSize,
							 int inOrder[], int po1, int po2)
{
	BinaryTreeNode* root = NULL;
	if (index < inSize && po1 <= po2)
	{
		// ǰ��ȷ����
		root = new BinaryTreeNode(prevOrder[index]);

		// ȷ����������������
		if (po1 < po2)
		{
			int div = po1;
			while (inOrder[div] != prevOrder[index])
			{
				++div;
			}
			root->_left = _RebulidTree(prevOrder, ++index, inSize, inOrder, po1, div-1);
			root->_right = _RebulidTree(prevOrder, ++index, inSize, inOrder,div+1, po2);
		}
	}

	return root;
}

// ��ǰ���������������ؽ���������ǰ�����У�1 2 3 4 5 6 - ��������:3 2 4 1 6 5��
BinaryTreeNode* RebulidTree(int inOrder[], int inSize,
							 int prevOrder[], int prevSize)
{
	assert(inOrder);
	assert(prevOrder);
	assert(inSize == prevSize);

	int index = 0;
	return _RebulidTree(prevOrder, index, inSize, inOrder, 0, prevSize-1);
}

void TestRebulidTree()
{
	int prevOrder[] = {1,2,3,4,5,6};
	int inOrder[] = {3,2,4,1,6,5};

	BinaryTreeNode* root = RebulidTree(inOrder, sizeof(inOrder)/sizeof(int),
		prevOrder, sizeof(prevOrder)/sizeof(int));

	PrevOrder(root);
	InOrder(root);
}

//11. �ж�һ�����Ƿ�����ȫ������
bool IsCompleteTree(BinaryTreeNode* root)
{
	queue<BinaryTreeNode*> q;
	if (root)
		q.push(root);

	bool isLast = false;

	while (!q.empty())
	{
		BinaryTreeNode* front = q.front();
		q.pop();
		if (front->_left)
		{
			if (isLast)
				return false;

			q.push(front->_left);
		}
		else
		{
			isLast = true;
		}

		if (front->_right)
		{
			if (isLast)
				return false;

			q.push(front->_right);
		}
		else
		{
			isLast = true;
		}
	}

	return true;
}

void TestIsCompleteTree()
{
	BinaryTreeNode* root = 0;

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

	int index = 0;
	CreateBinaryTree(root, t, index);

	cout<<"IsCompleteTree?"<<IsCompleteTree(root)<<endl;

}

//12. ��������ľ���y��
void ToTreeMirror(BinaryTreeNode* root)
{
	if (root == NULL)
	{
		return;
	}

	swap(root->_left, root->_right);
	ToTreeMirror(root->_left);
	ToTreeMirror(root->_right);
}

void TestToTreeMirror()
{
	BinaryTreeNode* root = 0;

	//	    1
	//    /   \
	//	 2	   5	
	//  / \	  /	\
	// 3   4  6  7
	//

	// 123##4##56##7
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
	t.push_back('#');
	t.push_back('#');
	t.push_back(7);

	int index = 0;
	CreateBinaryTree(root, t, index);
	ToTreeMirror(root);

	PrevOrder(root);
	cout<<endl;
}

//13.������������ת����һ�������˫������Ҫ���ܴ����κ��µĽ�㣬ֻ�ܵ������н��ָ���ָ��
// left��ʾ˫�������ǰ��ָ�룬right����˫������ĺ��ָ��
void _ToList(BinaryTreeNode* cur, BinaryTreeNode*& prev)
{
	if (cur == NULL)
		return;
	
	_ToList(cur->_left, prev);

	cur->_left = prev;
	if (prev)
		prev->_right = cur;

	prev = cur;

	_ToList(cur->_right, prev);
}

BinaryTreeNode* ToList(BinaryTreeNode* root)
{
	// ���ҵ�����ڵ���Ϊ�����ͷ
	BinaryTreeNode* head = root;
	while (head && head->_left)
	{
		head = head->_left;
	}

	BinaryTreeNode* prev = NULL;
	_ToList(root, prev);

	return head;
}

void TestToList()
{
	// 531##4##76
	vector<DataType> t;
	t.push_back(5);
	t.push_back(3);
	t.push_back(1);
	t.push_back('#');
	t.push_back('#');
	t.push_back(4);
	t.push_back('#');
	t.push_back('#');
	t.push_back(7);
	t.push_back(6);

	int index = 0;
	BinaryTreeNode* root = 0;
	CreateBinaryTree(root, t, index);

	BinaryTreeNode* head = ToList(root);


	BinaryTreeNode* tail = NULL;
	while (head)
	{
		cout<<head->_data<<" ";
		tail = head;
		head = head->_right;
	}
	cout<<endl;

	while (tail)
	{
		cout<<tail->_data<<" ";
		tail = tail->_left;
	}
	cout<<endl;
}

// ���Զ����������
void TestBinaryTreeTopic()
{
	cout<<endl;
	cout<<"TestBinaryTreeTopic:"<<endl;
	BinaryTreeNode* root = 0;

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

	BinaryTreeNode* ret = Find(root, 3);
	cout<<"Is 3 In The Tree:"<<IsInTree(root, ret)<<endl;

	BinaryTreeNode* x1 = Find(root, 4);
	BinaryTreeNode* x2 = Find(root, 5);
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

	// ���Զ������ؽ�
	cout<<"TestRebulidTree:";
	TestRebulidTree();
	cout<<endl;

	// ��������������ת����˫������
	cout<<"TestToList:";
	TestToList();

	// ������������ľ���
	cout<<"TestToTreeMirror:";
	TestToTreeMirror();

	// �����ж��Ƿ�����ȫ������
	cout<<"TestIsCompleteTree:";
	TestIsCompleteTree();
};

}