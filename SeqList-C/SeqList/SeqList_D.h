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

//typedef struct SeqList SeqList;

typedef enum Tag
{
	TRUE,	// ��
	FALSE,	// ��
}Tag;

typedef struct FindRet
{
	Tag isFind;		// �Ƿ��ҵ��ı�ʾ
	size_t index;	// �ҵ����ݵ��±�
}FindRet;

// ��ʼ��/����/��ӡ/�������
void InitSeqList(SeqList* pSeq);
void DestorySeqList(SeqList* pSeq);
void PrintSeqList(SeqList* pSeq);
void CheckExpandCapicity(SeqList* pSeq);

// ͷ��/ͷɾ/β��/βɾ
void PushBack(SeqList* pSeq, DataType x);
void PopBack(SeqList* pSeq);
void PushFront(SeqList* pSeq, DataType x);
void PopFront(SeqList* pSeq);

// ����/�޸�/ɾ��/����(ps:�߼����뾲̬˳��������ͬ������δʵ��)
void Insert(SeqList* pSeq, size_t index, DataType x);
void Modified (SeqList* pSeq, size_t index, DataType x);
void Erase(SeqList* pSeq, size_t index);
FindRet Find(SeqList* pSeq, DataType x, size_t index);
Tag Remove(SeqList* pSeq, DataType x, Tag all);

// ð������/ѡ������/���ֲ���
void Swap(DataType* left, DataType* right);
void BubbleSort(SeqList* pSeq);
void SelectSort(SeqList* pSeq);
//FindRet BinarySearch(DataType* array, size_t begin, size_t end, DataType x);
FindRet BinarySearch(SeqList* pSep, DataType x);

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

void CheckExpandCapicity(SeqList* pSeq)
{
	if (pSeq->size == pSeq->capicity)
	{
		DataType* tmp = (DataType*)malloc(pSeq->capicity * 2 *sizeof(DataType));
		memcpy(tmp, pSeq->array, sizeof(DataType) * pSeq->size);

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
	CheckExpandCapicity(pSeq);

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
	CheckExpandCapicity(pSeq);

	for (; i > 0; --i)
	{
		pSeq->array[i] = pSeq->array[i - 1];
	}

	pSeq->array[0] = x;
	pSeq->size++;
}

void Modified (SeqList* pSeq, size_t index, DataType x )
{
	assert(pSeq);
	assert(index < pSeq->size);

	pSeq->array[index] = x;
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

// ѡ������
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

FindRet BinarySearch(SeqList* pSep, DataType x)
{
	size_t left, right, mid;
	FindRet ret;
	ret.isFind = FALSE;

	assert(pSep);

	left = 0;
	right = pSep->size - 1;

	// ע������ʹ��<=, ������ܴ�����ѭ������
	while(left <= right)
	{
		// ע��Խ������
		//mid = (left + right) / 2;
		mid = left + (right- left) / 2;
		if (pSep->array[mid] == x)
		{
			ret.isFind = TRUE;
			ret.index = mid;
			return ret;
		}
		else if (pSep->array[mid] > x)
		{
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}

	return ret;
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
	PushFront(&s, 0);

	PrintSeqList(&s);

	DestorySeqList(&s);
}

void Test2()
{
	SeqList s;
	InitSeqList(&s);

	PushBack(&s, 6);
	PushBack(&s, 3);
	PushBack(&s, 5);
	PushBack(&s, 8);
	PushBack(&s, 4);
	PushBack(&s, 2);
	PushBack(&s, 1);
	PrintSeqList(&s);

	BubbleSort(&s);
	PrintSeqList(&s);

	BubbleSort(&s);
	PrintSeqList(&s);

	Swap(s.array + (s.size - 1), s.array);
	PrintSeqList(&s);
	BubbleSort(&s);
	PrintSeqList(&s);

	DestorySeqList(&s);
}

void Test3()
{
	DataType x;
	FindRet ret;
	SeqList s;
	InitSeqList(&s);

	PushBack(&s, 6);
	PushBack(&s, 3);
	PushBack(&s, 5);
	PushBack(&s, 8);
	PushBack(&s, 4);
	PushBack(&s, 2);
	PushBack(&s, 1);
	PrintSeqList(&s);

	SelectSort(&s);
	PrintSeqList(&s);

	x = 1;
	ret = BinarySearch(&s, x);
	if (ret.isFind == TRUE)
	{
		printf("Binary Search %d Success: %d\n", x, ret.index);
	}

	x = 8;
	ret = BinarySearch(&s, x);
	if (ret.isFind == TRUE)
	{
		printf("Binary Search %d Success: %d\n", x, ret.index);
	}

	x = 5;
	ret = BinarySearch(&s, x);
	if (ret.isFind == TRUE)
	{
		printf("Binary Search %d Success: %d\n", x, ret.index);
	}

	x = 20;
	ret = BinarySearch(&s, x);
	if (ret.isFind == FALSE)
	{
		printf("Binary Search %d Failed\n", x);
	}

	DestorySeqList(&s);
}