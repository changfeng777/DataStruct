#pragma once

#include<stdio.h>
#include<assert.h>
#include<malloc.h>
#include<stdlib.h>

typedef int DataType;

typedef struct ListNode
{
	DataType	 _data;			// ����
	struct ListNode* _next;		// ָ����һ���ڵ��ָ��
}ListNode, *PListNode;

//typedef struct ListNode  ListNode;
//typedef struct ListNode* PListNode;

//
// ps:PushBack/PopBack�ȽӿڵĲ���ʹ��PListNode*�Ķ���ָ����������
// �����Ƚ����޸�����ʱΪʲôҪ�ö���ָ�룬����Ϊ�˷�����Ը������������
// �磺void PushBack (PListNode& ppList, DataType x);
//

/////////////////////////////////////////////////////////////////////////////////
// ������Ļ�������

// ��ʼ��/����/��ӡ������
void InitSList(PListNode* ppList);
void DestorySList(PListNode* ppList);
void PrintSList(PListNode pList);
int GetLength(PListNode pList);

// β��/βɾ/ͷ��/ͷɾ
void PushBack (PListNode* ppList, DataType x);
void PopBack (PListNode* ppList);
void PushFront (PListNode* ppList, DataType x);
void PopFront (PListNode* ppList);

// ����/ɾ��/����
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

	// û�нڵ�/һ������
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

	// 1.û�нڵ�
	if (*ppList == 0)
	{
		return;
	}

	// 2.һ���ڵ�
	if ((*ppList)->_next == 0)
	{
		free(*ppList);
		*ppList = 0;
		return;
	}

	// 3.���������ϵĽڵ�
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

	// 1��û�нڵ� or һ������
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

	// û�нڵ�
	if (*ppList == NULL)
	{
		return;
	}

	// һ���ڵ�
	if((*ppList)->_next == NULL)
	{
		free(*ppList);
		*ppList = NULL;
		return;
	}

	// �����ڵ�����
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

			// ͷ�ڵ� or �м�ڵ�
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

	// û�нڵ� / һ�����Ͻڵ�
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

void Erase (PListNode* ppList, ListNode* n)
{
	ListNode* del = 0;
	assert(ppList);
	assert(n);

	// ����β�ڵ�����
	if(n->_next == 0)
	{
		PopBack(ppList);
		return;
	}

	// ��n����һ��next�ڵ��ֵ��ֵ��n�� ɾ��n��next�ڵ㡣
	n->_data = n->_next->_data;
	del = n->_next;
	n->_next = n->_next->_next;
	free(del);
}


//////////////////////////////////////////////////////////////////////////////////////
// �������������
//
//1. �Ƚ�˳�����������ȱ�㣬˵˵���Ƿֱ���ʲô������ʹ�ã�
//2. ��β��ͷ��ӡ������
//3. ɾ��һ����ͷ������ķ�β�ڵ�
//4. ����ͷ�������һ����ͷ�ڵ�ǰ����һ���ڵ�
//5. ������ʵ��Լɪ��
//6. ����/��ת������
//7. ����������ð������&��������
//8. �ϲ�������������,�ϲ�����Ȼ����
//9. ���ҵ�������м�ڵ㣬Ҫ��ֻ�ܱ���һ������
//10. ���ҵ�����ĵ�����k���ڵ㣬Ҫ��ֻ�ܱ���һ������
//11. �жϵ������Ƿ���������������󻷵ĳ��ȣ��󻷵���ڵ㣿������ÿ���㷨��ʱ�临�Ӷ�&�ռ临�Ӷȡ�
//12. �ж����������Ƿ��ཻ�����ཻ���󽻵㡣����������������
//13. �ж����������Ƿ��ཻ�����ཻ���󽻵㡣������������ܴ������������桿
//14. ��������ĸ��ơ�һ�������ÿ���ڵ㣬��һ��ָ��nextָ��ָ����һ���ڵ㣬����һ��randomָ��ָ����������е�һ������ڵ����NULL������Ҫ��ʵ�ָ�������������ظ��ƺ��������
//15.��������������������ͬ�����ݡ�void UnionSet(ListNode* l1, ListNode* l2);
//


// ɾ���������һ����β�ڵ�
void DelNonTailNode (ListNode* n)
{
	ListNode* del = 0;

	// �����Ƿ���β�ڵ�
	assert(n->_next);

	// ��n����һ��next�ڵ��ֵ��ֵ��n�� ɾ��n��next�ڵ㡣
	n->_data = n->_next->_data;
	del = n->_next;
	n->_next = n->_next->_next;
	free(del);
}

// �ڵ�ǰ�ڵ�ǰ����һ������x
void InsertFrontNode (ListNode* n, DataType x)
{
	DataType tmpData;
	ListNode* tmpNode = CreateNode(x);
	assert(n);

	// ���ݲ嵽��ǰ�ڵ��
	tmpNode->_next = n->_next;
	n->_next = tmpNode;

	// ��������
	tmpData = n->_data;
	n->_data = tmpNode->_data;
	tmpNode->_data = tmpData;
}

//
//Լɪ�򻷣�Լɪ�����⣩��һ����ѧ��Ӧ�����⣺��֪n���ˣ��Ա��1��2��3...n�ֱ��ʾ��Χ����һ��//Բ����Χ���ӱ��Ϊk���˿�ʼ����������m���Ǹ��˳��У�������һ�����ִ�1��ʼ����������m���Ǹ���//�ֳ��У����˹����ظ���ȥ��ֱ��Բ����Χ����ȫ�����С�
//

ListNode* JosephCycle(PListNode pList, int m)
{
	ListNode* begin = pList;
	assert(pList);

	while (1)
	{
		ListNode* del = 0;
		int i = 0;

		// �ж�ֻ��һ���ڵ�ʱ�˳�
		if (begin->_next == begin)
		{
			break;
		}

		// ��m-1��
		for (; i < m-1 ; ++i)
		{
			begin = begin->_next;
		}

		printf("%d ", begin->_data);

		// �滻ɾ��������ɾ��
		del = begin->_next;
		begin->_data = begin->_next->_data;
		begin->_next = begin->_next->_next;
		free(del);
	}

	return begin;
}

// ����
void Reverse (PListNode& pList)
{
	ListNode* newHead = NULL;
	ListNode* cur = pList;

	// �ӵڶ����ڵ㿪ʼ����ͷ�塣
	while (cur)
	{
		// ժ�ڵ�
		ListNode* tmp = cur;
		cur = cur->_next;

		// ͷ��
		tmp->_next = newHead;
		newHead = tmp;
	}

	// ����ͷ���ָ��
	pList = newHead;
}

// ����-��ð����������
void BubbleSort(PListNode pList)
{
	ListNode* prev = NULL;
	ListNode* next = NULL;
	ListNode* tail = NULL;

	// tail��ð�������β���
	while (tail != pList)
	{
		// �Ż����
		int exchange = 0;

		// ���������ð
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

		// ����β���
		tail = prev;
	}
}

//
// ʹ��ǰ��ָ���Ŀ�������
//
void PartionSort(ListNode* left, ListNode* right)
{
	if (left == right || left->_next == right)
		return;

	// left��right��[)������
	ListNode* key = left;

	// һǰһ��ָ���ڵ�������
	ListNode* prev = left, *next = left->_next;
	while (next != right)
	{
		// ����ҵ���keyС��ֵ����н���
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

// �����Ż�->�������� left��right��[)������
void QucikSort(PListNode pList)
{
	PartionSort(pList, NULL);
}

// �ϲ��������������ϲ����������Ȼ����
PListNode Merge(PListNode pList1, PListNode pList2)
{
	// ������һ������Ϊ�գ��򷵻���һ������
	if (pList1 == NULL)
	{
		return pList2;
	}
	if (pList2 == NULL)
	{
		return pList2;
	}

	PListNode newList, tail;
	// ȡ������С�Ľڵ�Ϊ�������ͷ��㡣
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

	// ���β�ڵ㣬����鲢������β�塣
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

	// ����ʣ��β����
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

// �ݹ�ʵ������ϲ�
PListNode MergeRecursive(PListNode pList1, PListNode pList2)
{
	PListNode mergePList;

	// ������������ͬ����ֱ�ӷ���
	if (pList1 == pList2)
	{
		return pList1;
	}

	// ������һ������Ϊ�գ��򷵻���һ������
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

// ������ָ�����⡿

// ���ҵ�������м�ڵ�
PListNode FindMidNode(PListNode pList)
{
	// ����ָ�룬��ָ��һ������������ָ��һ����һ����
	PListNode slow, fast;
	slow = pList;
	fast = pList;

	while (fast && fast->_next)
	{
		slow = slow->_next;
		fast = fast->_next->_next;
	}

	//
	// fast Ϊ����������Ϊż����slowΪ�м�ڵ㡣
	// fast->nextΪ����������Ϊ������slowΪ�м�ڵ㡣
	//

	return slow;
}

// ɾ��������ĵ�����k���ڵ�(k > 1 && k < ������ܳ���);
// ʱ�临�Ӷ�O(N)
void DelKNode(PListNode pList, int k)
{
	PListNode slow, fast;
	slow = pList;
	fast = pList;

	assert(k > 1);

	// ��ָ����k���Ժ���ָ��ſ�ʼ�ƶ�
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

// ������������⡿

// �ж������Ƿ����, ������������󻷵ĳ��Ⱥ������ڵ㣬����������-1
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
	// ʹ�ÿ���ָ�룬����ָ��׷����ָ�룬���ʾ�л��������ʾ�޻���
	//
	while (fast && fast->_next)
	{
		slow = slow->_next;
		fast = fast->_next->_next;

		if (slow == fast)
		{
			// ��ָ������һȦ�����㻷�ĳ��ȡ�
			int cycleLength = 0;
			*meetNode = fast;
			do{
				slow = slow->_next;
				++cycleLength;
			}while (slow != fast);

			return cycleLength;
		}
	}

	// ���������򷵻�-1
	return -1;
}

//
// ��ȡ����ڵ�
// ��ȡ������ڵ㻹������һ�ּ򵥵ķ���--һ��ָ��������㿪ʼ��
// ����һ��ָ���ͷ��ʼ�ߣ�����ָ������ʱ��������ڵ�,�����֤����^^
//
ListNode* GetCycleEntryNode(PListNode pList, PListNode meetNode)
{
	int length1 = 0, length2 = 0, interval = 0;
	ListNode* begin1 = pList, *begin2 = meetNode->_next;

	assert(pList);
	assert(meetNode);

	//
	// 1��ģ��������ڵ�Ͽ�������ת��Ϊ���������ཻ���󽻵�����⡣
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

	// 2���ȼ�����������ĳ��ȣ�������������interval���������ȵĲ�ֵ������
	begin1 = pList, begin2 = meetNode->_next;  // �����������
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

	// 3�����һ�������Ľڵ�Ϊ������ڵ㡣
	while (begin1 != begin2)
	{
		begin1 = begin1->_next;
		begin2 = begin2->_next;
	}

	return begin1;
}

// �������ཻ���⡿

//
// �ж����������Ƿ��ཻ����������������������
// �󻷵Ľ��㣬����������n����nΪ������ĳ��Ȳ��Ȼ����һ���ߣ���һ����������Ϊ���㡣(δʵ��)
// ���ﻹ��Ҫ�����������ʱ��������ཻ���⡣
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
// ��������ĸ��ơ�
// һ�������ÿ���ڵ㣬��һ��ָ��nextָ��ָ����һ���ڵ㣬����һ��randomָ��ָ����
// �������е�һ������ڵ����NULL������Ҫ��ʵ�ָ�������������ظ��ƺ��������
//

typedef struct ComplexNode
{
	DataType	 _data;				// ����
	struct ComplexNode* _next;		// ָ����һ���ڵ��ָ��
	struct ComplexNode* _random;	// ָ������ڵ�
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
		printf("��%d��", head->_data);
		printf(":random->%d", head->_random->_data);
		printf(":next->");

		head = head->_next;
	}

	printf("NULL\n");
}

ComplexNode* CopyComplexList(ComplexNode* cpList)
{
	ComplexNode* head = cpList;

	// 1.��copy��������Ľڵ����ԭ����ÿ���ڵ�ĺ���
	head = cpList;
	while (head)
	{
		ComplexNode* tmp = CreateComplexNode(head->_data);
		ComplexNode* prev = head;
		head = head->_next;

		prev->_next = tmp;
		tmp->_next = head;
	}

	// 2.����copy����ڵ��randomָ��
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

	// 3.ժ��copy����ڵ㣬������copy����
	head = cpList;
	ComplexNode* newHead, *newTail;
	if (head)
	{
		newHead = head->_next;
		newTail = head->_next;

		// ժ��copy�ڵ�
		head->_next = head->_next->_next;
		head = head->_next;
	}

	while (head)
	{
		newTail->_next = head->_next;
		newTail = newTail->_next;

		// ժ��copy�ڵ�
		head->_next = head->_next->_next;
		head = head->_next;
	}

	return newHead;
}


// ����PushBack
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

// ����PopBack
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
// ���������

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

	// ������������
	end = Find(pList, 7);
	realEntry = Find(pList, 4);
	end->_next = realEntry;
	printf("realEntry:%d\n", realEntry->_data);

	length = CheckCycle(pList, &meetNode);
	printf("Plist Length:%d, meetNode: %d\n", length, meetNode->_data);

	getEntry = GetCycleEntryNode(pList, meetNode);
	printf("realEntry:%d, getEntry: %d\n", realEntry->_data, getEntry->_data);

	// �⻷
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


	// �����ཻ����
	realCrossNode = Find(pList1, 4);
	end = Find(pList2, 12);
	end->_next = realCrossNode;

	printf("Cross: %d\n", CheckCross(pList1, pList2));

	// �⿪
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

	// ������������
	end = Find(pList, 7);
	end->_next = pList;

	printf("JosephCycle:%d\n", JosephCycle(pList, 3)->_data);

	printf("Test JosephCycle end\n\n");
}

// ��������ĸ���
void Test20()
{
	ComplexNode* cpList;
	CreateComplexList(cpList);
	PrintComplexList(cpList);

	ComplexNode* copyList = CopyComplexList(cpList);
	PrintComplexList(copyList);
}