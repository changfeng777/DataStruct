#include<stdio.h>
#include <iostream>
using namespace std;

#include "Slist.h"

// 测试PushBack
void Test1()
{
	PLinkList pList;
	printf("Test PushBack begin\n");

	InitSList(&pList);

	PushBack(&pList, 1);
	PushBack(&pList, 2);
	PushBack(&pList, 3);
	PushBack(&pList, 4);

	PrintSList(pList);

	DestorySList(&pList);

	printf("Test PushBack end\n\n");
}

// 测试PopBack
void Test2()
{
	PLinkList pList;
	printf("Test PopBack begin\n");

	InitSList(&pList);

	PushBack(&pList, 1);
	PushBack(&pList, 2);
	PushBack(&pList, 3);
	PushBack(&pList, 4);

	PrintSList(pList);

	PopBack(&pList);
	PopBack(&pList);
	PopBack(&pList);
	PopBack(&pList);

	PrintSList(pList);

	DestorySList(&pList);

	printf("Test PopBack end\n\n");
}

// PushFront
void Test3()
{
	PLinkList pList;
	printf("Test PushFront begin\n");

	InitSList(&pList);

	PushFront(&pList, 1);
	PushFront(&pList, 2);
	PushFront(&pList, 3);
	PushFront(&pList, 4);

	PrintSList(pList);

	DestorySList(&pList);

	printf("Test PushFront end\n\n");
}

// PopFront
void Test4()
{
	PLinkList pList;
	printf("Test PopFront begin\n");

	InitSList(&pList);

	PushFront(&pList, 1);
	PushFront(&pList, 2);
	PushFront(&pList, 3);
	PushFront(&pList, 4);
	PrintSList(pList);

	PopFront(&pList);
	PopFront(&pList);
	PopFront(&pList);
	PopFront(&pList);
	PrintSList(pList);

	DestorySList(&pList);

	printf("Test PopFront end\n\n");
}

// Find
void Test5()
{
	PLinkList pList;
	printf("Test Find begin\n");

	InitSList(&pList);

	PushFront(&pList, 1);
	PushFront(&pList, 2);
	PushFront(&pList, 3);
	PushFront(&pList, 4);
	PrintSList(pList);

	if(Find(pList, 4))
	{
		printf("Find 4 Success\n");
	}

	if(Find(pList, 5) == 0)
	{
		printf("Not Find 5\n");
	}

	DestorySList(&pList);

	printf("Test Find end\n\n");
}

// Remove
void Test6()
{
	PLinkList pList;
	printf("Test Remove begin\n");

	InitSList(&pList);

	PushFront(&pList, 1);
	PushFront(&pList, 2);
	PushFront(&pList, 3);
	PushFront(&pList, 4);
	PrintSList(pList);

	Remove(&pList, 1);
	Remove(&pList, 2);
	Remove(&pList, 3);
	Remove(&pList, 4);

	PrintSList(pList);

	DestorySList(&pList);

	printf("Test Remove end\n\n");
}

// Insert
void Test7()
{
	PLinkList pList;
	printf("Test Insert begin\n");

	InitSList(&pList);

	Insert(&pList, pList, 1);
	Insert(&pList, pList, 2);
	Insert(&pList, pList, 3);
	PrintSList(pList);

	DestorySList(&pList);
	printf("Test Insert end\n\n");
}

// Erase
void Test8()
{
	Node* del = 0;
	PLinkList pList;
	printf("Test Erase begin\n");

	InitSList(&pList);

	PushFront(&pList, 1);
	PushFront(&pList, 2);
	PrintSList(pList);

	del = Find(pList, 1);
	Erase(&pList, del);

	del = Find(pList, 2);
	Erase(&pList, del);
	PrintSList(pList);

	DestorySList(&pList);
	printf("Test Erase end\n\n");
}

/////////////////////////////////////////////////////////////////////////////////
// 面试题测试

// Reverse
void Test9()
{
	Node* del = 0;
	PLinkList pList;
	printf("Test Reverse begin\n");

	InitSList(&pList);

	PushFront(&pList, 1);
	PushFront(&pList, 2);
	PushFront(&pList, 3);
	PushFront(&pList, 4);
	PrintSList(pList);

	Reverse(&pList);
	PrintSList(pList);

	DestorySList(&pList);
	printf("Test Reverse end\n\n");
}

// Sort & SortOP
void Test10()
{
	Node* del = 0;
	PLinkList pList;
	printf("Test Sort begin\n");

	InitSList(&pList);

	//PushFront(&pList, 6);
	//PushFront(&pList, 4);
	//PushFront(&pList, 1);
	//PushFront(&pList, 5);
	//PushFront(&pList, 3);
	//PushFront(&pList, 2);
	//PushFront(&pList, 7);
	//PushFront(&pList, 8);
	//PushFront(&pList, 8);
	//PushFront(&pList, 9);
	//PushFront(&pList, 0);
	PushBack(&pList, 2);
	PushBack(&pList, 2);
	PushBack(&pList, 2);
	PushBack(&pList, 3);
	PushBack(&pList, 3);
	PushBack(&pList, 2);
	PushBack(&pList, 2);
	PushBack(&pList, 2);
	PushBack(&pList, 2);
	PushBack(&pList, 2);
	PushBack(&pList, 2);
	PushBack(&pList, 2);
	PushBack(&pList, 2);
	PushBack(&pList, 2);
	PushBack(&pList, 4);
	PushBack(&pList, 3);
	PushBack(&pList, 3);
	PushBack(&pList, 4);
	PushBack(&pList, 4);
	PushBack(&pList, 4);
	PushBack(&pList, 4);
	PushBack(&pList, 3);
	PushBack(&pList, 3);
	PushBack(&pList, 3);
	PushBack(&pList, 3);
	PushBack(&pList, 3);
	PushBack(&pList, 3);
	PushBack(&pList, 3);
	PushBack(&pList, 3);
	PushBack(&pList, 3);
	PushBack(&pList, 3);
	PushBack(&pList, 3);
	PushBack(&pList, 3);
	PushBack(&pList, 3);
	PushBack(&pList, 3);
	PushBack(&pList, 3);
	PushBack(&pList, 3);
	PushBack(&pList, 3);
	PushBack(&pList, 2);
	PushBack(&pList, 2);
	PushBack(&pList, 2);
	PushBack(&pList, 2);
	PushBack(&pList, 2);
	PushBack(&pList, 2);
	PushBack(&pList, 2);
	PushBack(&pList, 2);
	PushBack(&pList, 2);
	PushBack(&pList, 2);
	PushBack(&pList, 3);
	PushBack(&pList, 3);
	PushBack(&pList, 3);
	PushBack(&pList, 3);
	PushBack(&pList, 3);
	PushBack(&pList, 3);
	PushBack(&pList, 4);
	PushBack(&pList, 4);
	PushBack(&pList, 4);
	PushBack(&pList, 3);
	PushBack(&pList, 3);
	PushBack(&pList, 3);
	PushBack(&pList, 4);


	PrintSList(pList);

	//BubbleSort(pList);
	QucikSort_OP(pList, NULL);
	PrintSList(pList);

	DestorySList(&pList);
	printf("Test Sort end\n\n");
}

// Merge
void Test11()
{
	Node* del = 0;
	PLinkList pList1;
	PLinkList pList2;
	PLinkList mergePList;
	printf("Test Merge begin\n");

	InitSList(&pList1);
	InitSList(&pList2);
	InitSList(&mergePList);

	PushFront(&pList1, 1);
	PushFront(&pList1, 2);
	PushFront(&pList1, 3);
	PushFront(&pList1, 4);
	PushFront(&pList2, 10);
	PrintSList(pList1);

	PushFront(&pList2, 0);
	PushFront(&pList2, 1);
	PushFront(&pList2, 5);
	PushFront(&pList2, 8);
	PushFront(&pList2, 9);

	PrintSList(pList2);

	BubbleSort(pList1, NULL);
	BubbleSort(pList2, NULL);
	mergePList = Merge(pList1, pList2);
	PrintSList(mergePList);

	DestorySList(&mergePList);
	printf("Test Merge end\n\n");
}

// MergeRecursive
void Test12()
{
	Node* del = 0;
	PLinkList pList1;
	PLinkList pList2;
	PLinkList mergePList;
	printf("Test MergeRecursive begin\n");

	InitSList(&pList1);
	InitSList(&pList2);
	InitSList(&mergePList);

	PushFront(&pList1, 1);
	PushFront(&pList1, 2);
	PushFront(&pList1, 3);
	PushFront(&pList1, 4);
	PushFront(&pList2, 10);
	PrintSList(pList1);

	PushFront(&pList2, 0);
	PushFront(&pList2, 1);
	PushFront(&pList2, 5);
	PushFront(&pList2, 8);
	PushFront(&pList2, 9);

	PrintSList(pList2);

	BubbleSort(pList1, NULL);
	BubbleSort(pList2, NULL);
	mergePList = MergeRecursive(pList1, pList2);
	PrintSList(mergePList);

	DestorySList(&mergePList);
	printf("Test MergeRecursive end\n\n");
}

// DelNonTailNode
void Test13()
{
	Node* del = 0;
	PLinkList pList;
	printf("Test DelMidNode begin\n");

	InitSList(&pList);

	PushFront(&pList, 1);
	PushFront(&pList, 2);
	PushFront(&pList, 3);
	PushFront(&pList, 4);
	PrintSList(pList);

	del =Find(pList, 3);
	DelNonTailNode(del);
	PrintSList(pList);

	DestorySList(&pList);
	printf("Test DelMidNode end\n\n");
}

// InsertFrontNode
void Test14()
{
	Node* n = 0;
	PLinkList pList;
	printf("Test InsertFrontNode begin\n");

	InitSList(&pList);

	PushFront(&pList, 1);
	PushFront(&pList, 2);
	PushFront(&pList, 3);
	PushFront(&pList, 4);
	PrintSList(pList);

	n =Find(pList, 3);
	InsertFrontNode(n, 0);
	PrintSList(pList);

	DestorySList(&pList);
	printf("Test InsertFrontNode end\n\n");
}

// FindMidNode
void Test15()
{
	Node* n = 0;
	PLinkList pList;
	printf("Test FindMidNode begin\n");

	InitSList(&pList);

	PushBack(&pList, 1);
	PushBack(&pList, 2);
	PushBack(&pList, 3);
	PushBack(&pList, 4);
	PrintSList(pList);

	n =FindMidNode(pList);
	printf("Mid: %d\n", n->_data);

	PushBack(&pList, 5);
	PrintSList(pList);

	n =FindMidNode(pList);
	printf("Mid: %d\n", n->_data);

	DestorySList(&pList);
	printf("Test FindMidNode end\n\n");
}

// DelKNode
void Test16()
{
	Node* n = 0;
	PLinkList pList;
	printf("Test DelKNode begin\n");

	InitSList(&pList);

	PushBack(&pList, 1);
	PushBack(&pList, 2);
	PushBack(&pList, 3);
	PushBack(&pList, 4);
	PrintSList(pList);

	DelKNode(pList, 3);
	PrintSList(pList);

	DestorySList(&pList);
	printf("Test DelKNode end\n\n");
}

// CheckCycle
void Test17()
{
	int length = 0;
	Node* realEntry = 0, *getEntry = 0;
	Node* end = 0;
	PLinkList pList;
	PLinkList meetNode = 0;
	printf("Test CheckCycle begin\n");

	InitSList(&pList);

	PushBack(&pList, 1);
	PushBack(&pList, 2);
	PushBack(&pList, 3);
	PushBack(&pList, 4);
	PushBack(&pList, 5);
	PushBack(&pList, 6);
	PushBack(&pList, 7);
	PrintSList(pList);

	length = CheckCycle(pList, &meetNode);
	printf("Plist Length:%d\n", length);

	// 创建带环链表
	end = Find(pList, 7);
	realEntry = Find(pList, 4);
	end->_next = realEntry;
	printf("realEntry:%d\n", realEntry->_data);

	length = CheckCycle(pList, &meetNode);
	printf("Plist Length:%d, meetNode: %d\n", length, meetNode->_data);

	getEntry = GetCycleEntryNode(pList, meetNode);
	printf("realEntry:%d, getEntry: %d\n", realEntry->_data, getEntry->_data);

	// 解环
	end->_next = 0;
	DestorySList(&pList);
	printf("Test CheckCycLeLength end\n\n");
}

// CheckCross
void Test18()
{
	PLinkList pList1, pList2;
	Node* realCrossNode, *end;
	printf("Test CheckCross begin\n");

	InitSList(&pList1);
	InitSList(&pList2);

	PushBack(&pList1, 1);
	PushBack(&pList1, 2);
	PushBack(&pList1, 3);
	PushBack(&pList1, 4);
	PushBack(&pList1, 5);
	PushBack(&pList1, 6);
	PushBack(&pList1, 7);
	PrintSList(pList1);

	PushBack(&pList2, 10);
	PushBack(&pList2, 11);
	PushBack(&pList2, 12);
	PrintSList(pList2);

	printf("Cross: %d\n", CheckCross(pList1, pList2));


	// 创建相交链表
	realCrossNode = Find(pList1, 4);
	end = Find(pList2, 12);
	end->_next = realCrossNode;

	printf("Cross: %d\n", CheckCross(pList1, pList2));

	// 解开
	end->_next = NULL;
	DestorySList(&pList1);
	DestorySList(&pList2);
	printf("Test CheckCycLeLength end\n\n");
}

// JosephCycle
void Test19()
{
	Node* end;
	PLinkList pList;
	printf("Test JosephCycle begin\n");

	InitSList(&pList);

	PushBack(&pList, 1);
	PushBack(&pList, 2);
	PushBack(&pList, 3);
	PushBack(&pList, 4);
	PushBack(&pList, 5);
	PushBack(&pList, 6);
	PushBack(&pList, 7);
	PrintSList(pList);

	// 创建带环链表
	end = Find(pList, 7);
	end->_next = pList;

	printf("JosephCycle:%d\n", JosephCycle(pList, 3)->_data);

	printf("Test JosephCycle end\n\n");
}

// 复杂链表的复制
void Test20()
{
	ComplexNode* cpList;
	CreateComplexNode(cpList);
	PrintComplexList(cpList);

	ComplexNode* copyList = CopyComplexList(cpList);
	PrintComplexList(copyList);
}

int main()
{
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	//Test6();
	//Test7();
	//Test8();
	//Test9();
	//Test10();
	//Test11();
	//Test12();
	//Test13();
	//Test14();
	//Test15();
	//Test16();
	//Test17();
	//Test18();
	//Test19();
	//Test20();

	return 0;
}