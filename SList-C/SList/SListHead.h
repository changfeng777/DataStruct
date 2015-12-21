/***********************************************************************************
xxx.h:
    Copyright (c) Bit Software, Inc.(2013), All rights reserved.

Purpose: C语言实现单链表--带头结点实现

Author: xxx

Reviser: yyy

Created Time: 2015-4-26
************************************************************************************/

////////////////////////////////////////
// 定义带头结点的结构+用于对比不带头结点的结构

#pragma once
#include <stdio.h>
#include <assert.h>
#include <malloc.h>

typedef int DataType;

typedef struct ListNode
{
	DataType _data;
	struct ListNode* _next;
}ListNode;

//
// ps：注意这里切忌使用头结点的_data域存储链表节点个数，
// 只实现了部分接口，带头结点的大部分实现都差不多，可布置成作业完成
// 否则当DataType是char/double等类型类型时会存在设计缺陷和bug
//

ListNode* _BuyNode(DataType x)
{
	ListNode* tmp = (ListNode*)malloc(sizeof(ListNode));
	tmp->_data = x;
	tmp->_next = NULL;

	return tmp;
}

void PushBack(ListNode* pHead, DataType x)
{
	assert(pHead);

	ListNode* tail = pHead;
	while (tail->_next)
	{
		tail = tail->_next;
	}

	tail->_next = _BuyNode(x);
}

void PopBack(ListNode* pHead)
{
	assert(pHead);

	// 1.没有节点
	if(pHead->_next == NULL)
		return;

	// 2.一个及以上节点
	ListNode* tail = pHead;
	while (tail->_next->_next)
	{
		tail = tail->_next;
	}

	free(tail->_next);
	tail->_next = NULL;
}

void PushFront(ListNode* pHead, DataType x)
{
	assert(pHead);

	ListNode* tmp = _BuyNode(x);
	tmp->_next = pHead->_next;
	pHead->_next = tmp;
}


void PopFront(ListNode* pHead)
{
	assert(pHead);

	if (pHead->_next == NULL)
		return;

	ListNode* del = pHead->_next;
	pHead->_next = pHead->_next->_next;
	free(del);
}

void PrintList(ListNode* pHead)
{
	ListNode* begin = pHead->_next;
	assert(pHead);

	while (begin)
	{
		printf("%d->", begin->_data);
		begin = begin->_next;
	}

	printf("NULL\n");
}

void TestSListHead1()
{
	ListNode list;
	list._next = NULL;
	PushBack(&list, 1);
	PushBack(&list, 2);
	PushBack(&list, 3);
	PushBack(&list, 4);

	PrintList(&list);

	PopBack(&list);
	PopBack(&list);
	PopBack(&list);
	PopBack(&list);
	PopBack(&list);

	PrintList(&list);
}

void TestSListHead2()
{
	ListNode list;
	list._next = NULL;
	PushFront(&list, 1);
	PushFront(&list, 2);
	PushFront(&list, 3);
	PushFront(&list, 4);

	PrintList(&list);

	PopFront(&list);
	PopFront(&list);
	PopFront(&list);
	PopFront(&list);
	PopFront(&list);

	PrintList(&list);
}