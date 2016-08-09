/******************************************************************************************
Copyright (c) Bit Software, Inc.(2013), All rights reserved.

Purpose: ʵ�ֶ������Ļ���������    

Author: xjh

Reviser: yyy

Created Time: 2015-8-6
******************************************************************************************/


// ps:1-6�����ڶ��������������Ѿ�ʵ�֣������Ǵӵ�7�⿪ʼ
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

struct BinaryTreeTopic
{
	struct BinaryTreeNode
	{
		DataType _data;				// �������
		BinaryTreeNode* _left;		// ������
		BinaryTreeNode* _right;		// ������

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
			return NULL;

		if (root->_data == x)
			return root;

		if (ret = Find(root->_left, x))
			return ret;

		if (ret = Find(root->_right, x))
			return ret;

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

	// �ж�һ���ڵ��Ƿ���һ������
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

	// �������ڵ������������� -- O(N^2)
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
					 vector<BinaryTreeNode*>& s,
					 BinaryTreeNode* x)
	{
		if (root)
		{
			// �ڵ�������
			s.push_back(root);

			// �ҵ��ڵ��򷵻�true
			if (root == x)
				return true;

			// �ֱ������������
			if(GetNodePath(root->_left, s, x))
				return true;

			if (GetNodePath(root->_right, s, x))
				return true;

			// ����������û���ҵ���������ݡ�
			s.pop_back();
		}

		return false;
	}

	// �Ż� -- ʱ�临�Ӷ�O(N)
	BinaryTreeNode* GetCommontAncestor_OP(BinaryTreeNode* root,
										  BinaryTreeNode* x1, BinaryTreeNode* x2)
	{
		// ��ȡ�����ڵ�Ĳ���·��
		vector<BinaryTreeNode*> s1;
		vector<BinaryTreeNode*> s2;
		GetNodePath(root, s1, x1);
		GetNodePath(root, s2, x2);

		// stack���ﲻ�ܱ���������ʹ��list/vector.
		// ��˳����дӿ�ʼ���һ����ͬ���������������������
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
	// �ж�һ�ö������Ƿ���ƽ������AVL���Ĺ���
	bool IsBalance(BinaryTreeNode* root)
	{
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

	// �Ż� -- O(N)
	bool IsBalance_OP(BinaryTreeNode* root, int& height)
	{
		// 1.�жϵ�ǰ���Ƿ���ƽ����
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


	// 9.��һ�ö���������Զ�ڵ�ľ��� O(N^2)
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

	// �Ż�O(N)
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

	//10. ��ǰ���������������ؽ���������ǰ�����У�1 2 3 4 5 6 - ��������:3 2 4 1 6 5)
	BinaryTreeNode* _RebulidTree(int prevOrder[], int& index, int prevSize,
								 int inOrder[], int po1, int po2)
	{
		BinaryTreeNode* root = NULL;
		if (index < prevSize && po1 <= po2)
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
				root->_left = _RebulidTree(prevOrder, ++index, prevSize, inOrder, po1, div-1);
				root->_right = _RebulidTree(prevOrder, ++index, prevSize, inOrder,div+1, po2);
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


		// �������ڵ�������������
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

		// ����һ�����е���Զ����
		int maxLen = 0;
		FindMaxLen(root, maxLen);
		cout<<"Max Len:"<<maxLen<<endl;

		maxLen = 0;
		FindMaxLen_OP(root, maxLen);
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
};