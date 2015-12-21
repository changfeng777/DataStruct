/***********************************************************************************
xxx.h:
    Copyright (c) Bit Software, Inc.(2013), All rights reserved.

Purpose: C语言实现动态顺序表
ps:部分接口未实现，因为跟静态顺序表一致，重点关注插入数据时的扩容就可以了

Author: xxx

Reviser: yyy

Created Time: 2015-4-26
************************************************************************************/

// 动态顺序表
#pragma once
#define __SEQ_LIST__
#ifdef __SEQ_LIST__

typedef int DataType;

#define DEFAULT_CAPICITY 3

typedef struct SeqList
{
	DataType* array;  // 数据块指针
	size_t size;	  // 当前的有效数据个数 
	size_t capicity;  // 容量
}SeqList;

// 初始化/销毁/打印/检查扩容
void InitSeqList(SeqList* pSeq);
void DestorySeqList(SeqList* pSeq);
void PrintSeqList(SeqList* pSeq);
void CheckCapicity(SeqList* pSeq);

// 头插/头删/尾插/尾删 (主要体现插入数据的时候进行自动扩容处理)
void PushBack(SeqList* pSeq, DataType x);
void PopBack(SeqList* pSeq);
void PushFront(SeqList* pSeq, DataType x);
void PopFront(SeqList* pSeq);

// 插入/修改/删除/查找(ps:逻辑均与静态顺序表大致相同，所以未实现)
void Insert(SeqList* pSeq, size_t index, DataType x);
void Modified (SeqList* pSeq, size_t index, DataType x);
void Erase(SeqList* pSeq, size_t index);
int Find(SeqList* pSeq, DataType x, size_t index);
bool Remove(SeqList* pSeq, DataType x);
void RemoveAll(SeqList* pSeq, DataType x);
//...

//////////////////////////////////////////////////////////////////////////////
// 实现

void InitSeqList(SeqList* pSeq)
{
	assert(pSeq);
	pSeq->array = (DataType*)malloc(sizeof(DataType)*DEFAULT_CAPICITY);
	pSeq->size = 0;
	pSeq->capicity = DEFAULT_CAPICITY;
}

void PrintSeqList(SeqList* pSeq)
{
	int i = 0;
	for (; i < pSeq->size; ++i)
	{
		printf("%d ", pSeq->array[i]);
	}

	printf("\n", pSeq->array[i]);
}

void CheckCapicity(SeqList* pSeq)
{
	if (pSeq->size == pSeq->capicity)
	{
		// ps:在这里用realloc也可以,且更简洁

		// 创建新空间，拷贝数据
		DataType* tmp = (DataType*)malloc(pSeq->capicity * 2 *sizeof(DataType));
		memcpy(tmp, pSeq->array, sizeof(DataType) * pSeq->size);

		// 释放原空间，更新指针
		free(pSeq->array);
		pSeq->array = tmp;
		pSeq->capicity = pSeq->capicity * 2;
	}
}

void DestorySeqList(SeqList* pSeq)
{
	if (pSeq)
	{
		free(pSeq->array);
		pSeq->size = 0;
		pSeq->capicity = 0;
	}
}

void PushBack(SeqList* pSeq, DataType x)
{
	assert(pSeq);
	CheckCapicity(pSeq);

	pSeq->array[pSeq->size++] = x;
}

void PopBack(SeqList* pSeq)
{
	assert(pSeq);
	if (pSeq->size == 0)
	{
		printf("SeqList Is Empty\n");
	}

	--pSeq->size;
}

void PushFront(SeqList* pSeq, DataType x)
{
	int i = pSeq->size;
	assert(pSeq);
	CheckCapicity(pSeq);

	for (; i > 0; --i)
	{
		pSeq->array[i] = pSeq->array[i - 1];
	}

	pSeq->array[0] = x;
	pSeq->size++;
}

#endif // __SEQ_LIST__

void Test1()
{
	SeqList s;
	InitSeqList(&s);

	PushBack(&s, 1);
	PushBack(&s, 2);
	PushBack(&s, 3);
	PushBack(&s, 4);

	PrintSeqList(&s);

	PopBack(&s);
	PopBack(&s);
	PopBack(&s);
	PopBack(&s);
	PopBack(&s);

	DestorySeqList(&s);
}