#include <iostream>
using namespace std;

#include"BinaryTree.hpp"

void Test()
{
	int array[20] = {1, 2, 3, '#', '#', 4, '#', '#', 5, 6};
	BinaryTree<int> tree;
	tree.CreateTree(array, 10);

	tree.PrevOrder();
	tree.PrevOrder_NonR();

	tree.InOrder();

	tree.PostOrder();

	tree.LevelOrder();

	BinaryTreeNode<int>* ret = tree.Find(3);
	cout<<"Find 3?: "<<ret->_data<<endl;

	ret = tree.Find(10);
	cout<<"Find 10?: "<<ret<<endl;

	cout<<"Height:"<<tree.Height()<<endl;
}

int main()
{
	Test();
	return 0;
}