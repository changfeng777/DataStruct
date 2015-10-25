#pragma once

#include<stdio.h>
#include<assert.h>
#include<malloc.h>
#include<stdlib.h>

typedef int DataType;

typedef struct Node
{
	DataType	 _data;		// 数据
	struct Node* _next;		// 指向下一个节点的指针
}Node, *PLinkList;

//typedef struct Node  Node;
//typedef struct Node* PLinkList;

//
// ps:PushBack/PopBack等接口的参数使用PLinkList*的二级指针做参数，
// 可以先讲解修改链表时为什么要用二级指针，后续为了方便可以改用引用。
//

/////////////////////////////////////////////////////////////////////////////////
// 单链表的基本操作

// 初始化/销毁/打印单链表
void InitSList(PLinkList* ppList);
void DestorySList(PLinkList* ppList);
void PrintSList(PLinkList pList);
int GetListLength(PLinkList pList);

// 尾插/尾删/头插/头删
void PushBack (PLinkList* ppList, DataType x);
void PopBack (PLinkList* ppList);
void PushFront (PLinkList* ppList, DataType x);
void PopFront (PLinkList* ppList);

// 查找/删除/插入
Node* Find (PLinkList pList, DataType x);
int Remove (PLinkList* ppList, DataType x);
void Erase (PLinkList* ppList, Node* n);
void Insert (PLinkList* ppList, Node* n, DataType x);

void InitSList(PLinkList* ppList)
{
	assert(ppList);

	*ppList = 0;
}

void DestorySList(PLinkList* ppList)
{
	Node* begin = *ppList;
	assert(ppList);

	while (begin)
	{
		Node* tmp = begin;
		begin = begin->_next;

		free (tmp);
	}

	*ppList = 0;
}

void PrintSList(PLinkList pList)
{
	Node* begin = pList;

	printf("PLinkList:");
	while (begin)
	{
		printf("->%d", begin->_data);
		begin = begin->_next;
	}
	printf("->NULL\n");
}

int GetListLength(PLinkList ppList)
{
	int length = 0;
	Node* begin = ppList;
	while (begin)
	{
		length++;
		begin = begin->_next;
	}

	return length;
}

Node* CreateNode (DataType x)
{
	Node* n = (Node*)malloc (sizeof(Node));
	n->_data = x;
	n->_next = 0;

	return n;
}

void PushBack (PLinkList* ppList, DataType x)
{
	Node* n = 0;
	assert(ppList);

	n = CreateNode (x);

	// 没有节点/一个以上
	if (*ppList == NULL)
	{
		*ppList = n;
	}
	else
	{
		Node* begin = *ppList; 
		while (begin->_next)
		{
			begin = begin->_next;
		}

		begin->_next = n;
	}
}

void PopBack (PLinkList* ppList)
{
	Node* begin = 0;
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

void PushFront (PLinkList* ppList, DataType x)
{
	Node* n = 0;
	assert(ppList);

	n = CreateNode(x);

	// 1：没有节点 or 一个以上
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

void PopFront (PLinkList* ppList)
{
	Node* n = 0;
	assert(ppList);

	// 没有节点
	if (*ppList == NULL)
	{
		return;
	}

	// 一个节点
	if((*ppList)->_next == NULL)
	{
		free(*ppList);
		*ppList = NULL;
		return;
	}

	// 两个节点以上
	n = *ppList;
	*ppList = n->_next;
	free(n);
}

Node* Find (PLinkList ppList, DataType x)
{
	Node* begin = 0;
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

int Remove (PLinkList* ppList, DataType x)
{
	Node* prev = 0;
	Node* begin = 0;
	Node* del = 0;
	assert(ppList);

	begin = *ppList;
	while (begin)
	{
		if (begin->_data == x)
		{
			Node* del = begin;

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

void Insert (PLinkList* ppList, Node* n, DataType x)
{
	Node* tmp = 0;
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

void Erase (PLinkList* ppList, Node* n)
{
	Node* del = 0;
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


//////////////////////////////////////////////////////////////////////////////////////
// 链表相关面试题

// 逆置/排序(冒泡)/合并
void DelNonTailNode (Node* n);
void InsertFrontNode (Node* n, DataType x);
void Reverse (PLinkList* ppList);
void Sort(PLinkList pList);
PLinkList Merge(PLinkList l1, PLinkList l2);
PLinkList MergeRecursive(PLinkList l1, PLinkList l2);

// 删除单链表的一个非尾节点
void DelNonTailNode (Node* n)
{
	Node* del = 0;

	// 断言是否是尾节点
	assert(n->_next);

	// 将n的下一个next节点的值赋值给n， 删除n的next节点。
	n->_data = n->_next->_data;
	del = n->_next;
	n->_next = n->_next->_next;
	free(del);
}

// 在当前节点前插入一个数据x
void InsertFrontNode (Node* n, DataType x)
{
	DataType tmpData;
	Node* tmpNode = CreateNode(x);
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

Node* JosephCycle(PLinkList pList, int m)
{
	Node* begin = pList;
	assert(pList);

	while (1)
	{
		Node* del = 0;
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
void Reverse (PLinkList& pList)
{
	Node* newHead = NULL;
	Node* cur = pList;

	// 无节点或只有一个节点则直接返回
	if (pList == NULL || pList->_next == NULL)
		return;

	// 从第二个节点开始进行头插。
	while (cur)
	{
		// 摘节点
		Node* tmp = cur;
		cur = cur->_next;

		// 头插
		tmp->_next = newHead;
		newHead = tmp;
	}

	// 更新头结点指针
	pList = newHead;
}

// 排序-（冒泡升序排序）
void BubbleSort(PLinkList pList, Node* end)
{
	// 优化标记
	int exchange = 0;

	Node* prev = 0;
	Node* next = 0;
	Node* tail = 0;

	// 没有节点 or 一个节点则直接返回
	if (pList == end || pList->_next == end)
	{
		return;
	}

	// tail做尾标记
	tail = end;
	while (tail != pList)
	{
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
		{
			return;
		}

		// 更新尾标记
		tail = prev;
	}
}

//
// 使用前后指针版的快速排序
//
Node* Partion(Node* left, Node* right, int& leftCnt, int& rightCnt)
{
	// left和right是[)的区间
	Node* key = left;

	leftCnt = 0, rightCnt = 0;
	int totalCnt = 0;

	// 一前一后指针在调整序列
	Node* prev = left, *next = left->_next;
	while (next != right)
	{
		if (next->_data <= key->_data)
		{
			prev = prev->_next;
			if (prev != next)
			{
				swap(prev->_data, next->_data);
			}
			leftCnt++;
		}

		next = next->_next;
		totalCnt++;
	}

	rightCnt = totalCnt - leftCnt; 

	if (prev != key)
	{
		swap(prev->_data, key->_data);
	}

	return prev;
}

// 排序优化->快速排序 left和right是[)的区间
void QucikSort_OP(PLinkList left, PLinkList right)
{
	int leftCnt,rightCnt;
	// 一个节点或者一个
	if ((left != right) 
		&& (left && left->_next != right))
	{
		// 使用当序列小于13时，使用冒泡排序进行优化
		Node* key = Partion(left, right, leftCnt, rightCnt);
		if (leftCnt < 13)
		{
			BubbleSort(left, key);
		}
		else
		{
			QucikSort_OP(left, key);
		}
		if (rightCnt < 13)
		{
			BubbleSort(key->_next, right);
		}
		else
		{
			QucikSort_OP(key->_next, right);
		}
	}
}

// 合并两个有序链表，合并后的链表依然有序
PLinkList Merge(PLinkList pList1, PLinkList pList2)
{
	PLinkList mergePList;
	Node* tail = 0;

	Node* begin1 = 0;
	Node* begin2 = 0;

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

	// 取出数据小的节点为新链表的头结点。
	begin1 = pList1;
	begin2 = pList2;
	if(begin1->_data < begin2->_data)
	{
		mergePList = begin1;
		begin1 = begin1->_next;
	}
	else
	{
		mergePList = begin2;
		begin2 = begin2->_next;
	}

	// 标记尾节点，方便归并的数据尾插。
	tail = mergePList;

	while (begin1 && begin2)
	{
		if (begin1->_data < begin2->_data)
		{
			tail->_next = begin1;
			begin1 = begin1->_next;

			tail = tail->_next;
		}
		else
		{
			tail->_next = begin2;
			begin2 = begin2->_next;

			tail = tail->_next;
		}
	}

	// 链接剩余尾链表
	if (begin1)
	{
		tail->_next = begin1;
	}
	else if (begin2)
	{
		tail->_next = begin2;
	}

	return mergePList;
}

// 递归实现链表合并
PLinkList MergeRecursive(PLinkList pList1, PLinkList pList2)
{
	PLinkList mergePList;

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
PLinkList FindMidNode(PLinkList pList)
{
	// 快慢指针，快指针一次走两步，慢指针一次走一步。
	PLinkList slow, fast;

	if (pList == NULL)
	{
		return pList;
	}

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
void DelKNode(PLinkList pList, int k)
{
	PLinkList slow, fast;

	if (pList == NULL)
	{
		return;
	}

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
		Node* del = slow->_next;
		slow->_data = slow->_next->_data;
		slow->_next = slow->_next->_next;
		free(del);
	}
}

// 【链表带环问题】

// 判断链表是否带环, 若链表带环则求环的长度和相遇节点，不带环返回-1
int CheckCycle(PLinkList pList, PLinkList* meetNode)
{
	PLinkList slow, fast;

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
Node* GetCycleEntryNode(PLinkList pList, PLinkList meetNode)
{
	int length1 = 0, length2 = 0, interval = 0;
	Node* begin1 = pList, *begin2 = meetNode->_next;

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
int CheckCross(PLinkList pList1, PLinkList pList2)
{
	Node* end1 = 0, *end2 = 0;
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