/******************************************************************************************
Copyright (c) Bit Software, Inc.(2013), All rights reserved.

Purpose: 实现二叉树的基本面试题    

Author: xjh

Reviser: yyy

Created Time: 2015-8-6
******************************************************************************************/


//1. 前序/中序/后序遍历
//2. 层序遍历
//3. 求二叉树的高度
//4. 求叶子节点的个数
//5. 求二叉树第k层的节点个数
//6. 判断一个节点是否在一棵二叉树中
//7. 求两个节点的最近公共祖先
//8. 判断一棵二叉树是否是平衡二叉树
//9. 求二叉树中最远的两个节点的距离
//10. 由前序遍历和中序遍历重建二叉树（前序序列：1 2 3 4 5 6 - 中序序列:3 2 4 1 5 6）
//11. 判断一棵树是否是完全二叉树
//12. 求二叉树的镜像【y】
//13. 将二叉搜索树转换为双向链表


#pragma once

#include<iostream>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

//
// 定义以下结构仅用于二叉树笔试面试题进行测试。
//
typedef int DataType;

int statistics = 0;

namespace Topic
{

struct BinaryTreeNode
{
	DataType _data;				// 结点数据
	BinaryTreeNode* _left;	// 左子树
	BinaryTreeNode* _right;	// 右子树

	// 在查找最远距离使用(侵入式编程)
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
	// 前序遍历创建二叉树
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

// 前序/中序/后序遍历
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

// 层次遍历打印二叉树
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

// 求高度
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

// 叶子节点个数
int GetLeafNum(BinaryTreeNode* root)
{
	if(root == NULL)
		return 0;

	// 如果是叶子节点则返回1
	if (root->_left == NULL && root->_right == NULL)
	{
		return 1;
	}

	return GetLeafNum(root->_left) + GetLeafNum(root->_right);
}

// 求第K层的节点个数
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

// 判断一个节点是否在一棵树中
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

// 求两个节点的最近公共祖先
//
// 1.如果一个节点为根结点，另一个节点在一个子树中，则根节点为祖先节点。
// 2.如果一个节点在左子树，另一个节点在右子树，则当前根节点即为祖先节点。
// 3.如果两个均在左子树或右子树，则转化为子问题，在子树使用递归求解。
//
BinaryTreeNode* GetCommontAncestor(BinaryTreeNode* root,
								   BinaryTreeNode* x1, BinaryTreeNode* x2)
{
	// 1.如果一个节点为根结点，另一个节点在一个子树中，则根节点为祖先节点。
	if(root == x1 && IsInTree(root, x2))
	{
		return root;
	}
	if (root == x2 && IsInTree(root, x1))
	{
		return root;
	}

	// 2.如果一个节点在左子树，另一个节点在右子树，则当前根节点即为祖先节点。
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

	// 3.如果两个均在左子树或右子树，则转化为子问题，在子树使用递归求解。
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

// 优化
bool GetNodePath(BinaryTreeNode* root, 
				 stack<BinaryTreeNode*>& s,
				 BinaryTreeNode* x)
{
	if (root)
	{
		// 节点入栈
		s.push(root);

		// 找到节点则返回true
		if (root == x)
		{
			return true;
		}

		// 分别查找左右子树
		if(root->_left && GetNodePath(root->_left, s, x))
		{
			return true;
		}

		if (root->_right && GetNodePath(root->_right, s, x))
		{
			return true;
		}

		// 左右子树均没有找到，则出栈栈顶节点。
		s.pop();
	}

	return false;
}

// 优化
BinaryTreeNode* GetCommontAncestor_OP(BinaryTreeNode* root,
									  BinaryTreeNode* x1, BinaryTreeNode* x2)
{
	// 获取两个节点的查找路径
	stack<BinaryTreeNode*> s1;
	stack<BinaryTreeNode*> s2;
	GetNodePath(root, s1, x1);
	GetNodePath(root, s2, x2);

	// 倒数第一个相同的节点则为祖先节点
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

// 判断一棵二叉树是否是平衡树（平衡树按AVL的标准）
bool IsBalance(BinaryTreeNode* root)
{
	statistics++;

	if (root == NULL || (root->_left == NULL && root->_right == NULL))
	{
		return true;
	}

	// 1.判断当前树是否为平衡树
	int leftH = GetHeight(root->_left);
	int rightH = GetHeight(root->_right);

	int interval = leftH - rightH;
	if (interval > 1 || interval < -1)
	{
		return false;
	}

	// 2.判断左右子树是否为平衡树
	return IsBalance(root->_left) && IsBalance(root->_right);
}

// 优化
bool IsBalance_OP(BinaryTreeNode* root, int& height)
{
	statistics++;

	// 1.判断当前树是否是平衡树
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

	// 2.判断左右子树是否是平衡树，并算出左右子树的高度，通过高度判断当前树是否是平衡树
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
// 求一棵二叉树中最远的两个节点的距离。
// http://www.cnblogs.com/miloyip/archive/2010/02/25/binary_tree_distance.html
//
int maxLen = 0;
void FindMaxLen(BinaryTreeNode* root)
{
	// 1.根节点为空则直接返回
	if(root == NULL)
	{
		return;
	}

	// 2.左右子树为空，则距离当前节点的距离为0
	if (root->_left == NULL)
	{
		root->_maxLeftLen = 0;
	}
	if (root->_right == NULL)
	{
		root->_maxRightLen = 0;
	}

	// 3.递归计算左右子树的距离根节点的距离
	if (root->_left)
	{
		FindMaxLen(root->_left);
	}

	if (root->_right)
	{
		FindMaxLen(root->_right);
	}

	// 4.计算左右子树距离根节点的最大长度
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

	// 5.更新最远距离
	if (maxLen < root->_maxLeftLen + root->_maxRightLen)
	{
		maxLen = root->_maxRightLen + root->_maxLeftLen;
	}
}

// 上面代码的问题
// 1.全局变量存在线程安全的问题
// 2.需要改变二叉树节点的结构。（也既所谓的侵入式编程）
// 3.逻辑判断复杂

// 优化
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

// 再优化
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

//10. 由前序遍历和中序遍历重建二叉树（前序序列：1 2 3 4 5 6 - 中序序列:3 2 4 1 6 5)
BinaryTreeNode* _RebulidTree(int prevOrder[], int& index, int inSize,
							 int inOrder[], int po1, int po2)
{
	BinaryTreeNode* root = NULL;
	if (index < inSize && po1 <= po2)
	{
		// 前序确定根
		root = new BinaryTreeNode(prevOrder[index]);

		// 确定左右子树的区间
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

// 由前序遍历和中序遍历重建二叉树（前序序列：1 2 3 4 5 6 - 中序序列:3 2 4 1 6 5）
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

//11. 判断一棵树是否是完全二叉树
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

//12. 求二叉树的镜像【y】
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

//13.将二叉搜索树转换成一个排序的双向链表。要求不能创建任何新的结点，只能调整树中结点指针的指向
// left表示双向链表的前驱指针，right代表双向链表的后继指针
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
	// 先找到最左节点作为链表的头
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

// 测试二叉树编程题
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

	// 测试二叉树重建
	cout<<"TestRebulidTree:";
	TestRebulidTree();
	cout<<endl;

	// 测试搜索二叉树转换成双向链表
	cout<<"TestToList:";
	TestToList();

	// 测试求二叉树的镜像
	cout<<"TestToTreeMirror:";
	TestToTreeMirror();

	// 测试判断是否是完全二叉树
	cout<<"TestIsCompleteTree:";
	TestIsCompleteTree();
};

}