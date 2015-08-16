#include <iostream>
using namespace std;

#include "BinaryTree.hpp"
#include "BinaryTreeTopic.hpp"
#include "BinaryTreeThreading.hpp"
#include "Heap.hpp"
#include "RedPacket.hpp"

// ���Զ�����
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

// ���Զ����
void TestHeap()
{
	Heap<int, greater<int>> heap;
	heap.Insert(3);
	heap.Insert(5);
	heap.Insert(1);
	heap.Insert(4);
	heap.Insert(5);
	heap.Insert(1);
	heap.Insert(8);

	while (!heap.Empty())
	{
		cout<<heap.GetHeapTop()<<" ";
		heap.Remove();
	}
	cout<<endl;

	//int array[10] = {9,1,3,5,6,7,8,0,2,4};
	int array[10] = {10,16,18,12,11,13,15,17,14,19};
	Heap<int> heap1(array, 10);

	while (!heap1.Empty())
	{
		cout<<heap1.GetHeapTop()<<" ";
		heap1.Remove();
	}
	cout<<endl;
}

int main()
{
	//TestBinaryTree();
	//TestBinaryTreeTopic();
	//TestBinaryTreeThd();
	//TestHeap();
	TestRedPacket();

	return 0;
}


