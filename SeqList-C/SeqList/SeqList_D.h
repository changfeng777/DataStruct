/***********************************************************************************
xxx.h:
    Copyright (c) Bit Software, Inc.(2013), All rights reserved.

Purpose: C����ʵ�ֶ�̬˳���
ps:���ֽӿ�δʵ�֣���Ϊ����̬˳���һ�£��ص��ע��������ʱ�����ݾͿ�����

Author: xxx

Reviser: yyy

Created Time: 2015-4-26
************************************************************************************/

// ��̬˳���
#pragma once
#define __SEQ_LIST__
#ifdef __SEQ_LIST__

typedef int DataType;

#define DEFAULT_CAPICITY 3

typedef struct SeqList
{
	DataType* array;  // ���ݿ�ָ��
	size_t size;	  // ��ǰ����Ч���ݸ��� 
	size_t capicity;  // ����
}SeqList;

// ��ʼ��/����/��ӡ/�������
void InitSeqList(SeqList* pSeq);
void DestorySeqList(SeqList* pSeq);
void PrintSeqList(SeqList* pSeq);
void CheckCapicity(SeqList* pSeq);

// ͷ��/ͷɾ/β��/βɾ (��Ҫ���ֲ������ݵ�ʱ������Զ����ݴ���)
void PushBack(SeqList* pSeq, DataType x);
void PopBack(SeqList* pSeq);
void PushFront(SeqList* pSeq, DataType x);
void PopFront(SeqList* pSeq);

// ����/�޸�/ɾ��/����(ps:�߼����뾲̬˳��������ͬ������δʵ��)
void Insert(SeqList* pSeq, size_t index, DataType x);
void Modified (SeqList* pSeq, size_t index, DataType x);
void Erase(SeqList* pSeq, size_t index);
int Find(SeqList* pSeq, DataType x, size_t index);
bool Remove(SeqList* pSeq, DataType x);
void RemoveAll(SeqList* pSeq, DataType x);
//...

//////////////////////////////////////////////////////////////////////////////
// ʵ��

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
		// ps:��������reallocҲ����,�Ҹ����

		// �����¿ռ䣬��������
		DataType* tmp = (DataType*)malloc(pSeq->capicity * 2 *sizeof(DataType));
		memcpy(tmp, pSeq->array, sizeof(DataType) * pSeq->size);

		// �ͷ�ԭ�ռ䣬����ָ��
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