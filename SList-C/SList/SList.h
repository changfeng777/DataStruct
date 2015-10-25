#pragma once

#include<stdio.h>
#include<assert.h>
#include<malloc.h>
#include<stdlib.h>

typedef int DataType;

typedef struct Node
{
	DataType	 _data;		// ����
	struct Node* _next;		// ָ����һ���ڵ��ָ��
}Node, *PLinkList;

//typedef struct Node  Node;
//typedef struct Node* PLinkList;

//
// ps:PushBack/PopBack�ȽӿڵĲ���ʹ��PLinkList*�Ķ���ָ����������
// �����Ƚ����޸�����ʱΪʲôҪ�ö���ָ�룬����Ϊ�˷�����Ը������á�
//

/////////////////////////////////////////////////////////////////////////////////
// ������Ļ�������

// ��ʼ��/����/��ӡ������
void InitSList(PLinkList* ppList);
void DestorySList(PLinkList* ppList);
void PrintSList(PLinkList pList);
int GetListLength(PLinkList pList);

// β��/βɾ/ͷ��/ͷɾ
void PushBack (PLinkList* ppList, DataType x);
void PopBack (PLinkList* ppList);
void PushFront (PLinkList* ppList, DataType x);
void PopFront (PLinkList* ppList);

// ����/ɾ��/����
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

	// û�нڵ�/һ������
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

void PushFront (PLinkList* ppList, DataType x)
{
	Node* n = 0;
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

void PopFront (PLinkList* ppList)
{
	Node* n = 0;
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

void Insert (PLinkList* ppList, Node* n, DataType x)
{
	Node* tmp = 0;
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

void Erase (PLinkList* ppList, Node* n)
{
	Node* del = 0;
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

// ����/����(ð��)/�ϲ�
void DelNonTailNode (Node* n);
void InsertFrontNode (Node* n, DataType x);
void Reverse (PLinkList* ppList);
void Sort(PLinkList pList);
PLinkList Merge(PLinkList l1, PLinkList l2);
PLinkList MergeRecursive(PLinkList l1, PLinkList l2);

// ɾ���������һ����β�ڵ�
void DelNonTailNode (Node* n)
{
	Node* del = 0;

	// �����Ƿ���β�ڵ�
	assert(n->_next);

	// ��n����һ��next�ڵ��ֵ��ֵ��n�� ɾ��n��next�ڵ㡣
	n->_data = n->_next->_data;
	del = n->_next;
	n->_next = n->_next->_next;
	free(del);
}

// �ڵ�ǰ�ڵ�ǰ����һ������x
void InsertFrontNode (Node* n, DataType x)
{
	DataType tmpData;
	Node* tmpNode = CreateNode(x);
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

Node* JosephCycle(PLinkList pList, int m)
{
	Node* begin = pList;
	assert(pList);

	while (1)
	{
		Node* del = 0;
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
void Reverse (PLinkList& pList)
{
	Node* newHead = NULL;
	Node* cur = pList;

	// �޽ڵ��ֻ��һ���ڵ���ֱ�ӷ���
	if (pList == NULL || pList->_next == NULL)
		return;

	// �ӵڶ����ڵ㿪ʼ����ͷ�塣
	while (cur)
	{
		// ժ�ڵ�
		Node* tmp = cur;
		cur = cur->_next;

		// ͷ��
		tmp->_next = newHead;
		newHead = tmp;
	}

	// ����ͷ���ָ��
	pList = newHead;
}

// ����-��ð����������
void BubbleSort(PLinkList pList, Node* end)
{
	// �Ż����
	int exchange = 0;

	Node* prev = 0;
	Node* next = 0;
	Node* tail = 0;

	// û�нڵ� or һ���ڵ���ֱ�ӷ���
	if (pList == end || pList->_next == end)
	{
		return;
	}

	// tail��β���
	tail = end;
	while (tail != pList)
	{
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
		{
			return;
		}

		// ����β���
		tail = prev;
	}
}

//
// ʹ��ǰ��ָ���Ŀ�������
//
Node* Partion(Node* left, Node* right, int& leftCnt, int& rightCnt)
{
	// left��right��[)������
	Node* key = left;

	leftCnt = 0, rightCnt = 0;
	int totalCnt = 0;

	// һǰһ��ָ���ڵ�������
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

// �����Ż�->�������� left��right��[)������
void QucikSort_OP(PLinkList left, PLinkList right)
{
	int leftCnt,rightCnt;
	// һ���ڵ����һ��
	if ((left != right) 
		&& (left && left->_next != right))
	{
		// ʹ�õ�����С��13ʱ��ʹ��ð����������Ż�
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

// �ϲ��������������ϲ����������Ȼ����
PLinkList Merge(PLinkList pList1, PLinkList pList2)
{
	PLinkList mergePList;
	Node* tail = 0;

	Node* begin1 = 0;
	Node* begin2 = 0;

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

	// ȡ������С�Ľڵ�Ϊ�������ͷ��㡣
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

	// ���β�ڵ㣬����鲢������β�塣
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

	// ����ʣ��β����
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

// �ݹ�ʵ������ϲ�
PLinkList MergeRecursive(PLinkList pList1, PLinkList pList2)
{
	PLinkList mergePList;

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
PLinkList FindMidNode(PLinkList pList)
{
	// ����ָ�룬��ָ��һ������������ָ��һ����һ����
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
	// fast Ϊ����������Ϊż����slowΪ�м�ڵ㡣
	// fast->nextΪ����������Ϊ������slowΪ�м�ڵ㡣
	//

	return slow;
}

// ɾ��������ĵ�����k���ڵ�(k > 1 && k < ������ܳ���);
// ʱ�临�Ӷ�O(N)
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
		Node* del = slow->_next;
		slow->_data = slow->_next->_data;
		slow->_next = slow->_next->_next;
		free(del);
	}
}

// ������������⡿

// �ж������Ƿ����, ������������󻷵ĳ��Ⱥ������ڵ㣬����������-1
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
Node* GetCycleEntryNode(PLinkList pList, PLinkList meetNode)
{
	int length1 = 0, length2 = 0, interval = 0;
	Node* begin1 = pList, *begin2 = meetNode->_next;

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