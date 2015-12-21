/***********************************************************************************
xxx.h:
    Copyright (c) Bit Software, Inc.(2013), All rights reserved.

Purpose: C����ʵ�־�̬˳���

Author: xxx

Reviser: yyy

Created Time: 2015-4-26
************************************************************************************/

// ��̬˳���
#pragma once

#define MAX_SIZE 100
typedef int DataType;

typedef struct SeqList
{
	DataType array[MAX_SIZE];
	size_t size;
}SeqList;

void InitSeqList(SeqList* pSeq);
void PrintSeqList(SeqList* pSeq);
void PushBack(SeqList* pSeq, DataType x);
void PopBack(SeqList* pSeq);
void PushFront(SeqList* pSeq, DataType x);
void PopFront(SeqList* pSeq);
int Find(SeqList* pSeq, DataType x);
void Insert(SeqList* pSeq, size_t index, DataType x);
void Modified (SeqList* pSeq, size_t index, DataType x );
void Erase(SeqList* pSeq, size_t index);
bool Remove(SeqList* pSeq, DataType x);
void RemoveAll(SeqList* pSeq, DataType x);

/////////////////////////////////////////////////////////////
// ʵ��

void InitSeqList(SeqList* pSeq)
{
	assert(pSeq);
	memset(pSeq->array, 0, MAX_SIZE*sizeof(DataType));
	pSeq->size = 0;
}

void PrintSeqList(SeqList* pSeq)
{
	size_t i = 0;
	assert(pSeq);

	for (; i < pSeq->size; ++i)
	{
		printf("%d ", pSeq->array[i]);
	}
	printf("\n");
}

void PushBack(SeqList* pSeq, DataType x)
{
	assert(pSeq != NULL);

	if (pSeq->size >= MAX_SIZE)
	{
		printf("SeqList Is Full\n");
		return;
	}

	pSeq->array[(pSeq->size)++] = x;
}

void PopBack(SeqList* pSeq)
{
	assert(pSeq);

	if (pSeq->size < 1)
	{
		printf("SeqList Is Empty\n");
		return;
	}

	//pSeq->array[--(pSeq->size)] = 0;
	--pSeq->size;
}

void PushFront(SeqList* pSeq, DataType x)
{
	// i�ǵ�ǰ��Ų����������ʼ�±�
	int i = pSeq->size - 1;
	assert(pSeq);

	if (pSeq->size >= MAX_SIZE)
	{
		printf("SeqList is Full\n");
		return;
	}

	for (; i >= 0; --i)
	{
		pSeq->array[i + 1] = pSeq->array[i];
	}

	pSeq->array[0] = x;
	++pSeq->size;
}

void PopFront(SeqList* pSeq)
{
	int i = 1;
	assert(pSeq);

	if (pSeq->size == 0)
	{
		printf("SeqList is Empty\n");
		return;
	}
	
	for (; i < pSeq->size; ++i)
	{
		pSeq->array[i - 1] = pSeq->array[i];
	}

	pSeq->size--;
}

// ��index��λ���ϲ���һ������
void Insert(SeqList* pSeq, size_t index, DataType x)
{
	size_t end = pSeq->size;
	assert(pSeq);
	assert(index <= pSeq->size);

	if (pSeq->size > MAX_SIZE - 1)
	{
		printf("SeqList is Full\n");
		return;
	}

	for(; end > index; --end)
	{
		pSeq->array[end] = pSeq->array[end - 1];
	}

	pSeq->array[index] = x;
	pSeq->size++;
}

void Modified (SeqList* pSeq, size_t index, DataType x )
{
	assert(pSeq);
	assert(index < pSeq->size);

	pSeq->array[index] = x;
}

void Erase (SeqList* pSeq, size_t index)
{
	assert(pSeq);
	assert(index < pSeq->size);

	for (; index < pSeq->size - 1; ++index)
	{
		pSeq->array[index] = pSeq->array[index + 1];
	}

	pSeq->size--;
}

int Find(SeqList* pSeq, DataType x)
{
	size_t index = 0;
	assert(pSeq);

	for (; index < pSeq->size; ++index)
	{
		if (x == pSeq->array[index])
		{
			return index;
		}
	}

	return -1;
}

bool Remove(SeqList* pSeq, DataType x)
{
	size_t ret = Find(pSeq, x);
	if (ret != -1)
	{
		Erase(pSeq, x);
	}

	return ret != -1;
}

void RemoveAll(SeqList* pSeq, DataType x)
{
	// ����˼·��Find��ѯEraseɾ����ֱ��û�в��ҵ�x
	size_t count = 0;
	size_t index = 0, begin = 0;
	assert(pSeq);

	for (; index < pSeq->size; ++index)
	{
		if (pSeq->array[index] == x)
		{
			++count;
		}
		else
		{
			pSeq->array[begin++] = pSeq->array[index];
		}
	}

	pSeq->size -= count;
}

void Swap(DataType* left, DataType* right)
{
	DataType tmp = *left;
	*left = *right;
	*right = tmp;
}

void BubbleSort(SeqList* pSeq)
{
	int count = 0;
	int exchange = 0;
	size_t index, end;
	assert(pSeq);
	for (end = pSeq->size -1; end > 0; --end)
	{
		//������־�����Ż�
		exchange = 0;
		for (index = 0; index < end; ++index)
		{
			count++;
			if (pSeq->array[index] > pSeq->array[index + 1])
			{
				Swap(pSeq->array + index, pSeq->array + index + 1);
				exchange = 1;
			}
		}

		if (exchange == 0)
		{
			break;
		}
	}

	printf("count:%d\n", count);
}

//
// ѡ������
// �Ż�˼·--һ��ѡ��������С�����ݷ�����ͷ
//
void SelectSort(SeqList* pSeq)
{
	size_t minIndex, index, begin;
	assert(pSeq);

	for (begin = 0; begin < pSeq->size - 1; ++begin)
	{
		minIndex = begin;
		for (index = begin + 1; index < pSeq->size; ++index)
		{
			if (pSeq->array[minIndex] > pSeq->array[index])
			{
				minIndex = index;
			}
		}

		if (minIndex != begin)
		{
			Swap(pSeq->array + minIndex, pSeq->array + begin);
		}
	}
}

// ע�����ұ߽����[]��[)�Ŀ���

//// []
//int BinarySearch(SeqList* pSep, DataType x)
//{
//	assert(pSep);
//	size_t left = 0;
//	size_t right = pSep->size - 1;
//
//	while(left <= right)
//	{
//		// ע��Խ������
//		//mid = (left + right) / 2;
//		size_t mid = left + (right- left) / 2;
//		if (pSep->array[mid] == x)
//		{
//			return mid;
//		}
//		else if (pSep->array[mid] > x)
//		{
//			right = mid - 1;
//		}
//		else
//		{
//			left = mid + 1;
//		}
//	}
//
//	return -1;
//}

// [)
int BinarySearch(SeqList* pSep, DataType x)
{
	assert(pSep);
	size_t left = 0;
	size_t right = pSep->size;

	while(left < right)
	{
		// ע��Խ������
		size_t mid = left + (right- left) / 2;
		if (pSep->array[mid] == x)
		{
			return mid;
		}
		else if (pSep->array[mid] > x)
		{
			right = mid;
		}
		else
		{
			left = mid + 1;
		}
	}

	return -1;
}

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
}

void Test2()
{
	SeqList s;
	InitSeqList(&s);

	PushBack(&s, 1);
	PushBack(&s, 2);
	PushBack(&s, 3);
	PushBack(&s, 4);

	PrintSeqList(&s);

	SelectSort(&s);
	PrintSeqList(&s);
}

//
// δд�����Ĳ����������벹�䣬�����ص㽲�⸲�ǽ�ȫ������������Ҫ��
// ��:PushBack 5�����ݣ�PopBackʱӦ��ɾ5�����ϲ��ǽ�ȫ�ĸ��ǲ���
//