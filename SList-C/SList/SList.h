/***********************************************************************************
xxx.h:
    Copyright (c) Bit Software, Inc.(2013), All rights reserved.

Purpose: C语言实现单链表--不带头结点实现

Author: xxx

Reviser: yyy

Created Time: 2015-4-26
************************************************************************************/

#pragma once

#include<stdio.h>
#include<assert.h>
#include<malloc.h>
#include<stdlib.h>

typedef int DataType;

typedef struct ListNode
{
	DataType	 _data;			// 数据
	struct ListNode* _next;		// 指向下一个节点的指针
}ListNode, *PListNode;

//
// ps:PushBack/PopBack等接口的参数使用PListNode*的二级指针做参数，
// 可以先讲解修改链表数据时为什么要用二级指针，后续简单介绍一下引用，为了方便可以改用引用替代
// 如：void PushBack (PListNode& ppList, DataType x);
//

/////////////////////////////////////////////////////////////////////////////////
// 单链表的基本操作

// 初始化/销毁/打印单链表
void InitSList(PListNode* ppList);
void DestorySList(PListNode* ppList);
void PrintSList(PListNode pList);
int GetLength(PListNode pList);

// 尾插/尾删/头插/头删
void PushBack (PListNode* ppList, DataType x);
void PopBack (PListNode* ppList);
void PushFront (PListNode* ppList, DataType x);
void PopFront (PListNode* ppList);

// 查找/删除/插入
ListNode* Find (PListNode pList, DataType x);
int Remove (PListNode* ppList, DataType x);
void Erase (PListNode* ppList, ListNode* n);
void Insert (PListNode* ppList, ListNode* n, DataType x);

void InitSList(PListNode* ppList)
{
	assert(ppList);

	*ppList = 0;
}

void DestorySList(PListNode* ppList)
{
	ListNode* begin = *ppList;
	assert(ppList);

	while (begin)
	{
		ListNode* tmp = begin;
		begin = begin->_next;

		free (tmp);
	}

	*ppList = 0;
}

void PrintSList(PListNode pList)
{
	ListNode* begin = pList;

	printf("PListNode:");
	while (begin)
	{
		printf("->%d", begin->_data);
		begin = begin->_next;
	}
	printf("->NULL\n");
}

int GetLength(PListNode ppList)
{
	int length = 0;
	ListNode* begin = ppList;
	while (begin)
	{
		length++;
		begin = begin->_next;
	}

	return length;
}

ListNode* CreateNode (DataType x)
{
	ListNode* n = (ListNode*)malloc (sizeof(ListNode));
	n->_data = x;
	n->_next = 0;

	return n;
}

void PushBack (PListNode* ppList, DataType x)
{
	ListNode* n = 0;
	assert(ppList);

	n = CreateNode (x);

	// 没有节点/一个以上
	if (*ppList == NULL)
	{
		*ppList = n;
	}
	else
	{
		ListNode* begin = *ppList; 
		while (begin->_next)
		{
			begin = begin->_next;
		}

		begin->_next = n;
	}
}

void PopBack (PListNode* ppList)
{
	ListNode* begin = 0;
	assert(ppList);

	// 1.没有节点
	if (*ppList == 0)
	{
		return;
	}

	// 2.一个节点
	if ((*ppList)->_next == 0)
	{
		free(*ppList);
		*ppList = 0;
		return;
	}

	// 3.有两个以上的节点
	begin = *ppList;
	while(begin->_next->_next != NULL)
	{
		begin = begin->_next;
	}

	free(begin->_next);
	begin->_next = 0;
}

void PushFront (PListNode* ppList, DataType x)
{
	ListNode* n = 0;
	assert(ppList);

	n = CreateNode(x);

	//
	// 1：没有节点
	// 2：一个或以上节点
	// 
	if (*ppList == NULL)
	{
		*ppList = n;
	}
	else
	{
		n->_next = *ppList;
		*ppList = n;
	}
}

void PopFront (PListNode* ppList)
{
	ListNode* n = 0;
	assert(ppList);

	// 1.没有节点
	if (*ppList == NULL)
	{
		return;
	}

	// 2.一个节点
	if((*ppList)->_next == NULL)
	{
		free(*ppList);
		*ppList = NULL;
		return;
	}

	// 3.两个节点以上
	n = *ppList;
	*ppList = n->_next;
	free(n);
}

ListNode* Find (PListNode ppList, DataType x)
{
	ListNode* begin = 0;
	assert(ppList);

	begin = ppList;
	while (begin)
	{
		if (begin->_data == x)
		{
			return begin;
		}

		begin = begin->_next;
	}

	return 0;
}

void Erase (PListNode* ppList, ListNode* n)
{
	ListNode* del = 0;
	assert(ppList);
	assert(n);

	// 处理尾节点的情况
	if(n->_next == 0)
	{
		PopBack(ppList);
		return;
	}

	// 将n的下一个next节点的值赋值给n， 删除n的next节点。
	n->_data = n->_next->_data;
	del = n->_next;
	n->_next = n->_next->_next;
	free(del);
}

int Remove (PListNode* ppList, DataType x)
{
	ListNode* prev = 0;
	ListNode* begin = 0;
	ListNode* del = 0;
	assert(ppList);

	begin = *ppList;
	while (begin)
	{
		if (begin->_data == x)
		{
			ListNode* del = begin;

			// 头节点 or 中间节点
			if (*ppList == begin)
			{
				*ppList =  (*ppList)->_next;
			}
			else
			{				
				prev->_next = begin->_next;
			}

			free(del);

			return 0;
		}

		prev = begin;
		begin = begin->_next;
	}

	return -1;
}

void Insert (PListNode* ppList, ListNode* n, DataType x)
{
	ListNode* tmp = 0;
	assert(ppList);

	tmp = CreateNode(x);

	// 没有节点 / 一个以上节点
	if(*ppList == NULL)
	{
		*ppList = tmp;
	}
	else
	{
		assert(n);
		tmp->_next = n->_next;
		n->_next = tmp;
	}
}

//////////////////////////////////////////////////////////////////////////////////////
// 链表相关面试题
//
//1. 比较顺序表和链表的优缺点，说说它们分别在什么场景下使用？
//2. 从尾到头打印单链表
//3. 删除一个无头单链表的非尾节点
//4. 在无头单链表的一个非头节点前插入一个节点
//5. 单链表实现约瑟夫环
//6. 逆置/反转单链表
//7. 单链表排序（冒泡排序&快速排序）
//8. 合并两个有序链表,合并后依然有序
//9. 查找单链表的中间节点，要求只能遍历一次链表
//10. 查找单链表的倒数第k个节点，要求只能遍历一次链表
//11. 判断单链表是否带环？若带环，求环的长度？求环的入口点？并计算每个算法的时间复杂度&空间复杂度。
//12. 判断两个链表是否相交，若相交，求交点。（假设链表不带环）
//13. 判断两个链表是否相交，若相交，求交点。（假设链表可能带环）【升级版】
//14. 复杂链表的复制。一个链表的每个节点，有一个指向next指针指向下一个节点，还有一个random指针指向这个链表中的一个随机节点或者NULL，现在要求实现复制这个链表，返回复制后的新链表。
//15.求两个已排序链表中相同的数据。void UnionSet(ListNode* l1, ListNode* l2);
//


// 删除单链表的一个非尾节点
void DelNonTailNode (ListNode* n)
{
	ListNode* del = 0;

	// 断言是否是尾节点
	assert(n->_next);

	// 将n的下一个next节点的值赋值给n， 删除n的next节点。
	n->_data = n->_next->_data;
	del = n->_next;
	n->_next = n->_next->_next;
	free(del);
}

// 在当前节点前插入一个数据x
void InsertFrontNode (ListNode* n, DataType x)
{
	DataType tmpData;
	ListNode* tmpNode = CreateNode(x);
	assert(n);

	// 数据插到当前节点后
	tmpNode->_next = n->_next;
	n->_next = tmpNode;

	// 交换数据
	tmpData = n->_data;
	n->_data = tmpNode->_data;
	tmpNode->_data = tmpData;
}

//
//约瑟夫环（约瑟夫问题）是一个数学的应用问题：已知n个人（以编号1，2，3...n分别表示）围坐在一张//圆桌周围。从编号为k的人开始报数，数到m的那个人出列；他的下一个人又从1开始报数，数到m的那个人//又出列；依此规律重复下去，直到圆桌周围的人全部出列。
//

ListNode* JosephCycle(PListNode pList, int m)
{
	ListNode* begin = pList;
	assert(pList);

	while (1)
	{
		ListNode* del = 0;
		int i = 0;

		// 判断只有一个节点时退出
		if (begin->_next == begin)
		{
			break;
		}

		// 跳m-1步
		for (; i < m-1 ; ++i)
		{
			begin = begin->_next;
		}

		printf("%d ", begin->_data);

		// 替换删除法进行删除
		del = begin->_next;
		begin->_data = begin->_next->_data;
		begin->_next = begin->_next->_next;
		free(del);
	}

	return begin;
}

// 逆置
void Reverse (PListNode& pList)
{
	ListNode* newHead = NULL;
	ListNode* cur = pList;

	// 从第二个节点开始进行头插。
	while (cur)
	{
		// 摘节点
		ListNode* tmp = cur;
		cur = cur->_next;

		// 头插
		tmp->_next = newHead;
		newHead = tmp;
	}

	// 更新头结点指针
	pList = newHead;
}

// 排序-（冒泡升序排序）
void BubbleSort(PListNode pList)
{
	ListNode* prev = NULL;
	ListNode* next = NULL;
	ListNode* tail = NULL;

	// tail做冒泡排序的尾标记
	while (tail != pList)
	{
		// 优化标记
		int exchange = 0;

		// 将数据向后冒
		prev = pList;
		next = pList->_next;
		while(next != tail)
		{
			if (prev->_data > next->_data)
			{
				DataType tmp = prev->_data;
				prev->_data = next->_data;
				next->_data = tmp;

				exchange = 1;
			}

			prev = next;
			next = next->_next;
		}

		if (exchange == 0)
			return;

		// 更新尾标记
		tail = prev;
	}
}

//
// 使用前后指针版的快速排序
//
void PartionSort(ListNode* left, ListNode* right)
{
	if (left == right || left->_next == right)
		return;

	// left和right是[)的区间
	ListNode* key = left;

	// 一前一后指针在调整序列
	ListNode* prev = left, *next = left->_next;
	while (next != right)
	{
		// 如果找到比key小的值则进行交换
		if (next->_data <= key->_data)
		{
			prev = prev->_next;
			if (prev != next)
			{
				swap(prev->_data, next->_data);
			}
		}

		next = next->_next;
	}

	if (prev != key)
	{
		swap(prev->_data, key->_data);
	}

	PartionSort(left, prev);
	PartionSort(prev->_next, right);
}

// 排序优化->快速排序 left和right是[)的区间
void QucikSort(PListNode pList)
{
	PartionSort(pList, NULL);
}

// 合并两个有序链表，合并后的链表依然有序
PListNode Merge(PListNode pList1, PListNode pList2)
{
	// 若其中一个链表为空，则返回另一个链表
	if (pList1 == NULL)
	{
		return pList2;
	}
	if (pList2 == NULL)
	{
		return pList2;
	}

	PListNode newList, tail;
	// 取出数据小的节点为新链表的头结点。
	if (pList1->_data < pList2->_data)
	{
		newList = pList1;
		pList1 = pList1->_next;
	}
	else
	{
		newList = pList2;
		pList2 = pList2->_next;
	}

	// 标记尾节点，方便归并的数据尾插。
	tail = newList;

	while (pList1 && pList2)
	{
		if (pList1->_data < pList2->_data)
		{
			tail->_next = pList1;
			pList1 = pList1->_next;

			tail = tail->_next;
		}
		else
		{
			tail->_next = pList2;
			pList2 = pList2->_next;

			tail = tail->_next;
		}
	}

	// 链接剩余尾链表
	if (pList1)
	{
		tail->_next = pList1;
	}

	if (pList2)
	{
		tail->_next = pList2;
	}

	return newList;
}

// 递归实现链表合并
PListNode MergeRecursive(PListNode pList1, PListNode pList2)
{
	PListNode mergePList;

	// 若两个链表相同，则直接返回
	if (pList1 == pList2)
	{
		return pList1;
	}

	// 若其中一个链表为空，则返回另一个链表
	if (pList1 == NULL)
	{
		return pList2;
	}
	if (pList2 == NULL)
	{
		return pList2;
	}

	if (pList1->_data < pList2->_data)
	{
		mergePList = pList1;
		mergePList->_next = MergeRecursive(pList1->_next, pList2);
	}
	else
	{
		mergePList = pList2;
		mergePList->_next = MergeRecursive(pList1, pList2->_next);
	}

	return mergePList;
}

// 【快慢指针问题】

// 查找单链表的中间节点
PListNode FindMidNode(PListNode pList)
{
	// 快慢指针，快指针一次走两步，慢指针一次走一步。
	PListNode slow, fast;
	slow = pList;
	fast = pList;

	while (fast && fast->_next)
	{
		slow = slow->_next;
		fast = fast->_next->_next;
	}

	//
	// fast 为空则链表长度为偶数，slow为中间节点。
	// fast->next为空则链表长度为奇数，slow为中间节点。
	//

	return slow;
}

// 删除单链表的倒数第k个节点(k > 1 && k < 链表的总长度);
// 时间复杂度O(N)
void DelKNode(PListNode pList, int k)
{
	PListNode slow, fast;
	slow = pList;
	fast = pList;

	assert(k > 1);

	// 快指针走k步以后，慢指针才开始移动
	while (fast)
	{
		if (--k < 0)
		{
			slow = slow->_next;
		}

		fast = fast->_next;
	}

	if (k < 0)
	{
		ListNode* del = slow->_next;
		slow->_data = slow->_next->_data;
		slow->_next = slow->_next->_next;
		free(del);
	}
}

// 【链表带环问题】

// 判断链表是否带环, 若链表带环则求环的长度和相遇节点，不带环返回-1
int CheckCycle(PListNode pList, PListNode* meetNode)
{
	PListNode slow, fast;

	if (pList == NULL)
	{
		return -1;
	}

	slow = pList;
	fast = pList;

	//
	// 使用快慢指针，当快指针追上慢指针，则表示有环，否则表示无环。
	//
	while (fast && fast->_next)
	{
		slow = slow->_next;
		fast = fast->_next->_next;

		if (slow == fast)
		{
			// 慢指针再跑一圈，计算环的长度。
			int cycleLength = 0;
			*meetNode = fast;
			do{
				slow = slow->_next;
				++cycleLength;
			}while (slow != fast);

			return cycleLength;
		}
	}

	// 链表不带环则返回-1
	return -1;
}

//
// 获取环入口点
// 获取环的入口点还有另外一种简单的方法--一个指针从相遇点开始走
// 另外一个指针从头开始走，两个指针相遇时，则是入口点,请进行证明！^^
//
ListNode* GetCycleEntryNode(PListNode pList, PListNode meetNode)
{
	int length1 = 0, length2 = 0, interval = 0;
	ListNode* begin1 = pList, *begin2 = meetNode->_next;

	assert(pList);
	assert(meetNode);

	//
	// 1：模拟从相遇节点断开环，则转换为两单链表相交，求交点的问题。
	//
	while (begin1 != meetNode)
	{
		begin1 = begin1->_next;
		++length1;
	}
	while (begin2 != meetNode)
	{
		begin2 = begin2->_next;
		++length2;
	}

	// 2：先计算两个链表的长度，长的链表先走interval（两链表长度的差值）步。
	begin1 = pList, begin2 = meetNode->_next;  // 重置链表起点
	if (length1 > length2)
	{
		interval = length1 - length2;
		while (interval--)
		{
			begin1 = begin1->_next;
		}
	}
	else if(length1 < length2)
	{
		interval = length2 - length1;
		while (interval--)
		{
			begin2 = begin2->_next;
		}
	}

	// 3：则第一次相遇的节点为环的入口点。
	while (begin1 != begin2)
	{
		begin1 = begin1->_next;
		begin2 = begin2->_next;
	}

	return begin1;
}

// 【链表相交问题】

//
// 判断两个链表是否相交，假设两个链表都不带环。
// 求环的交点，长链表先走n步（n为两链表的长度差），然后再一起走，第一个相遇点则为交点。(未实现)
// 这里还需要考虑链表带环时，链表的相交问题。
//
int CheckCross(PListNode pList1, PListNode pList2)
{
	ListNode* end1 = 0, *end2 = 0;
	assert(pList1 && pList2);

	while (pList1)
	{
		end1 = pList1;
		pList1 = pList1->_next;
	}

	while (pList2)
	{
		end2 = pList2;
		pList2 = pList2->_next;
	}

	if (end1 == end2)
	{
		return 1;
	}

	return 0;
}

//
// 复杂链表的复制。
// 一个链表的每个节点，有一个指向next指针指向下一个节点，还有一个random指针指向这
// 个链表中的一个随机节点或者NULL，现在要求实现复制这个链表，返回复制后的新链表。
//

typedef struct ComplexNode
{
	DataType	 _data;				// 数据
	struct ComplexNode* _next;		// 指向下一个节点的指针
	struct ComplexNode* _random;	// 指向随机节点
}ComplexNode;

ComplexNode* CreateComplexNode(DataType x)
{
	ComplexNode* tmp = new ComplexNode;
	tmp->_data = x;
	tmp->_next = NULL;
	tmp->_random = NULL;

	return tmp;
}

void CreateComplexList(ComplexNode*& head)
{
	ComplexNode* n1 = CreateComplexNode(1);
	ComplexNode* n2 = CreateComplexNode(2);
	ComplexNode* n3 = CreateComplexNode(3);
	ComplexNode* n4 = CreateComplexNode(4);

	n1->_next = n2;
	n2->_next = n3;
	n3->_next = n4;
	n4->_next = NULL;

	n1->_random = n4;
	n2->_random = n3;
	n3->_random = n2;
	n4->_random = n1;

	head = n1;
}

void PrintComplexList(ComplexNode* head)
{
	while (head)
	{
		printf("【%d】", head->_data);
		printf(":random->%d", head->_random->_data);
		printf(":next->");

		head = head->_next;
	}

	printf("NULL\n");
}

ComplexNode* CopyComplexList(ComplexNode* cpList)
{
	ComplexNode* head = cpList;

	// 1.将copy出新链表的节点插在原链表每个节点的后面
	head = cpList;
	while (head)
	{
		ComplexNode* tmp = CreateComplexNode(head->_data);
		ComplexNode* prev = head;
		head = head->_next;

		prev->_next = tmp;
		tmp->_next = head;
	}

	// 2.处理copy链表节点的random指向
	head = cpList;
	while (head)
	{
		ComplexNode* random = head->_random;
		ComplexNode* next = head->_next;
		if (random)
		{
			next->_random = random->_next;
		}

		head = head->_next->_next;
	}

	// 3.摘下copy链表节点，构建出copy链表
	head = cpList;
	ComplexNode* newHead, *newTail;
	if (head)
	{
		newHead = head->_next;
		newTail = head->_next;

		// 摘下copy节点
		head->_next = head->_next->_next;
		head = head->_next;
	}

	while (head)
	{
		newTail->_next = head->_next;
		newTail = newTail->_next;

		// 摘下copy节点
		head->_next = head->_next->_next;
		head = head->_next;
	}

	return newHead;
}


// 测试PushBack
void Test1()
{
	PListNode pList;
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
	PListNode pList;
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
	PListNode pList;
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
	PListNode pList;
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
	PListNode pList;
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
	PListNode pList;
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
	PListNode pList;
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
	ListNode* del = 0;
	PListNode pList;
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
	ListNode* del = 0;
	PListNode pList;
	printf("Test Reverse begin\n");

	InitSList(&pList);

	PushFront(&pList, 1);
	PushFront(&pList, 2);
	PushFront(&pList, 3);
	PushFront(&pList, 4);
	PrintSList(pList);

	Reverse(pList);
	PrintSList(pList);

	DestorySList(&pList);
	printf("Test Reverse end\n\n");
}

// Sort & SortOP
void Test10()
{
	ListNode* del = 0;
	PListNode pList;
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
	QucikSort(pList);
	PrintSList(pList);

	DestorySList(&pList);
	printf("Test Sort end\n\n");
}

// Merge
void Test11()
{
	ListNode* del = 0;
	PListNode pList1;
	PListNode pList2;
	PListNode mergePList;
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

	BubbleSort(pList1);
	BubbleSort(pList2);
	mergePList = Merge(pList1, pList2);
	PrintSList(mergePList);

	DestorySList(&mergePList);
	printf("Test Merge end\n\n");
}

// MergeRecursive
void Test12()
{
	ListNode* del = 0;
	PListNode pList1;
	PListNode pList2;
	PListNode mergePList;
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

	BubbleSort(pList1);
	BubbleSort(pList2);
	mergePList = MergeRecursive(pList1, pList2);
	PrintSList(mergePList);

	DestorySList(&mergePList);
	printf("Test MergeRecursive end\n\n");
}

// DelNonTailNode
void Test13()
{
	ListNode* del = 0;
	PListNode pList;
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
	ListNode* n = 0;
	PListNode pList;
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
	ListNode* n = 0;
	PListNode pList;
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
	ListNode* n = 0;
	PListNode pList;
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
	ListNode* realEntry = 0, *getEntry = 0;
	ListNode* end = 0;
	PListNode pList;
	PListNode meetNode = 0;
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
	PListNode pList1, pList2;
	ListNode* realCrossNode, *end;
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
	ListNode* end;
	PListNode pList;
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
	CreateComplexList(cpList);
	PrintComplexList(cpList);

	ComplexNode* copyList = CopyComplexList(cpList);
	PrintComplexList(copyList);
}