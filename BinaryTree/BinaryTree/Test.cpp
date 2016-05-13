#include <iostream>
using namespace std;
#include <assert.h>

#pragma warning (disable:4996)
#pragma warning (disable:4018)

#include "BinaryTree.hpp"
#include "BinaryTreeTopic.hpp"
#include "BinaryTreeThreading.hpp"
#include "Heap.hpp"
#include "RedPacket.hpp"
#include "HuffmanTree.hpp"
#include "FileCompress.hpp"
#include "BinarySearchTree.hpp"
#include "AVLTree.hpp"
#include "RBTree.hpp"
#include "BTree.h"

int main()
{
	//TestBinaryTree();
	//TestBinaryTree_P();
	//Topic::TestBinaryTreeTopic();
	//TestBinaryTreeThd();
	//TestHeap();
	//TestRedPacket();

	//TestHuffmanTree_A();
	TestCompress();
	//TestBSTree();

	//NonRecursion::TestAVLTree();
	//Recursion::TestAVLTree();
	//TestRBTree();

	//TestBTree();

	return 0;
}