/******************************************************************************************
Copyright (c) Bit Software, Inc.(2013), All rights reserved.

Purpose: 实现二叉树的基本面试题    

Author: xjh

Reviser: yyy

Created Time: 2015-8-6
******************************************************************************************/


// ps:1-6题在在二叉树基础部分已经实现，下面是从第7题开始
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

struct BinaryTreeTopic
{
	struct BinaryTreeNode
	{
		DataType _data;				// 结点数据
		BinaryTreeNode* _left;		// 左子树
		BinaryTreeNode* _right;		// 右子树

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
			return NULL;

		if (root->_data == x)
			return root;

		if (ret = Find(root->_left, x))
			return ret;

		if (ret = Find(root->_right, x))
			return ret;

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

	// 判断一个节点是否在一棵树中
	bool IsInTree(BinaryTreeNode* root, BinaryTreeNode* node)
	{
		if (root == NULL)
			return false;

		if(node == root)
			return true;

		if (IsInTree(root->_left, node) || IsInTree(root->_right, node))
			return true;

		return false;
	}

	// 求两个节点的最近公共祖先 -- O(N^2)
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
					 vector<BinaryTreeNode*>& s,
					 BinaryTreeNode* x)
	{
		if (root)
		{
			// 节点入数据
			s.push_back(root);

			// 找到节点则返回true
			if (root == x)
				return true;

			// 分别查找左右子树
			if(GetNodePath(root->_left, s, x))
				return true;

			if (GetNodePath(root->_right, s, x))
				return true;

			// 左右子树均没有找到，则出数据。
			s.pop_back();
		}

		return false;
	}

	// 优化 -- 时间复杂度O(N)
	BinaryTreeNode* GetCommontAncestor_OP(BinaryTreeNode* root,
										  BinaryTreeNode* x1, BinaryTreeNode* x2)
	{
		// 获取两个节点的查找路径
		vector<BinaryTreeNode*> s1;
		vector<BinaryTreeNode*> s2;
		GetNodePath(root, s1, x1);
		GetNodePath(root, s2, x2);

		// stack这里不能遍历，所以使用list/vector.
		// 找顺序表中从开始最后一个相同的数据则是最近公共祖先
		size_t i = 0;
		while (i < s1.size() && i < s2.size())
		{
			if (s1[i] == s2[i])
				++i;
			else
				break;
		}

		--i;

		if (i != 0)
			return s1[i];
		else
			return NULL;
	}

	int GetHeight(BinaryTreeNode* root)
	{
		if (root == NULL)
			return 0;
		
		int left = GetHeight(root->_left);
		int right = GetHeight(root->_right);

		return left > right ? left+1 : right+1;
	}

	// O(N^2)
	// 判断一棵二叉树是否是平衡树（AVL树的规则）
	bool IsBalance(BinaryTreeNode* root)
	{
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

	// 优化 -- O(N)
	bool IsBalance_OP(BinaryTreeNode* root, int& height)
	{
		// 1.判断当前树是否是平衡树
		if (root == NULL)
		{
			height = 0;
			return true;
		}

		if (root->_left == NULL && root->_right == NULL)
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


	// 9.求一棵二叉树中最远节点的距离 O(N^2)
	void FindMaxLen(BinaryTreeNode* root, int& maxLen)
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

		FindMaxLen_OP(root->_left, maxLen);
		FindMaxLen_OP(root->_right, maxLen);
	}

	// 优化O(N)
	int FindMaxLen_OP(BinaryTreeNode* root, int& maxLen)
	{
		if (root == NULL)
		{
			maxLen = 0;
			return -1;
		}

		int l = FindMaxLen_OP(root->_left, maxLen) + 1; 
		int r = FindMaxLen_OP(root->_right, maxLen) + 1;

		if (maxLen < l + r)
		{
			maxLen = l + r;
		}

		return l > r ? l : r;
	}

	//10. 由前序遍历和中序遍历重建二叉树（前序序列：1 2 3 4 5 6 - 中序序列:3 2 4 1 6 5)
	BinaryTreeNode* _RebulidTree(int prevOrder[], int& index, int prevSize,
								 int inOrder[], int po1, int po2)
	{
		BinaryTreeNode* root = NULL;
		if (index < prevSize && po1 <= po2)
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
				root->_left = _RebulidTree(prevOrder, ++index, prevSize, inOrder, po1, div-1);
				root->_right = _RebulidTree(prevOrder, ++index, prevSize, inOrder,div+1, po2);
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
		return _RebulidTree(prevOrder, index, prevSize, inOrder, 0, prevSize-1);
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


		// 求两个节点的最近公共祖先
		BinaryTreeNode* x1 = Find(root, 4);
		BinaryTreeNode* x2 = Find(root, 5);
		BinaryTreeNode* ret = GetCommontAncestor_OP(root, x1, x2);
		if (ret)
			cout<<"3 & 6 Commont Ancestor Is:"<<ret->_data<<endl;
		else
			cout<<"Not Find Commont Ancestor"<<endl;

		int height = 0;
		cout<<"Tree Is Balance Tree ? : "<<IsBalance(root)<<endl;

		cout<<"OP Tree Is Balance Tree ? : "<<IsBalance_OP(root, height)<<endl;

		// 测试一棵树中的最远距离
		int maxLen = 0;
		FindMaxLen(root, maxLen);
		cout<<"Max Len:"<<maxLen<<endl;

		maxLen = 0;
		FindMaxLen_OP(root, maxLen);
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
};