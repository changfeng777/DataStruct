#include <iostream>
using namespace std;

#include"BinaryTree.hpp"
#include"BinaryTreeTopic.hpp"
#include "BinaryTreeThreading.hpp"

void TestBinaryTree()
{
	cout<<"TestBinaryTree:"<<endl;

	int array[20] = {1, 2, 3, '#', '#', 4, '#', '#', 5, 6};
	BinaryTree<int> tree;
	tree.CreateTree(array, 10);

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

void TestBinaryTreeThd()
{
	int array[20] = {1, 2, 3, '#', '#', 4, '#', '#', 5, 6};
	BinaryTree_Thd<int> tree;
	tree.CreateTree(array, 10);
	tree.InOrder();

	tree.InThreading();
	tree.InOrderThreading();
}

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

int main()
{
	//TestBinaryTree();
	//TestBinaryTreeTopic();
	TestBinaryTreeThd();
	return 0;
}