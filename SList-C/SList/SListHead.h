////////////////////////////////////////
// 带头结点结构定义+部分实现

#pragma once
#include <stdio.h>
#include <assert.h>
#include <malloc.h>

typedef int DataType;

typedef struct Node
{
	DataType data;
	struct Node* next;
}Node;

typedef struct List
{
	Node* head;  // 指向单链表的头
	size_t size;
}List;

Node* _CreateNode(DataType x)
{
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->data = x;
	tmp->next = NULL;

	return tmp;
}

void InitList(List* pList)
{
	assert(pList);
	pList->head = NULL;
	pList->size = 0;
}

void PushBack(List* pList, DataType x)
{
	assert(pList);

	if (pList->head == NULL)
	{
		pList->head = _CreateNode(x);
	}
	else
	{
		Node* end = pList->head;
		while(end->next != NULL)
		{
			end = end->next;
		}

		end->next = _CreateNode(x);
	}

	++pList->size;
}

void PrintList(List* pList)
{
	Node* begin = pList->head;
	assert(pList);

	while (begin)
	{
		printf("%d->", begin->data);
		begin = begin->next;
	}

	printf("NULL\n");
}