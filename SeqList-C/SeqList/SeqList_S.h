
// ��̬˳���
#pragma once

#define MAX_SIZE 100
typedef int DataType;

typedef struct SeqList
{
	DataType array[MAX_SIZE];
	size_t size;
}SeqList;

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

//typedef struct SeqList SeqList;
void InitSeqList(SeqList* pSeq);
void PrintSeqList(SeqList* pSeq);

void PushBack(SeqList* pSeq, DataType x);
void PopBack(SeqList* pSeq);

void PushFront(SeqList* pSeq, DataType x);
void PopFront(SeqList* pSeq);

void Insert(SeqList* pSeq, size_t index, DataType x);
void Modified (SeqList* pSeq, size_t index, DataType x );
void Remove(SeqList* pSeq, size_t index);

// ����-1����ʾ����ʧ�ܡ�
// ����>=0����ʾ���ҳɹ�,����ֵ��ʾ���ҵ����ݵ��±ꡣ
FindRet Find(SeqList* pSeq, DataType x, size_t index);

// ����-1����ʾɾ��ʧ�ܡ�
// ����0����ʾɾ���ɹ���
//int Erase(SeqList* pSeq, DataType x);

// ����-1����ʾɾ��ʧ�ܡ�
// ����0����ʾɾ���ɹ���
// all����0��ʾɾ������x
// all����-1��ʾɾ����һ������
Tag Erase(SeqList* pSeq, DataType x, Tag all);

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

	if (pSeq->size > MAX_SIZE - 1)
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
	// i�ǵ�ǰ��Ų�������ݵ��±�
	int i = pSeq->size - 1;
	assert(pSeq);

	if (pSeq->size > MAX_SIZE -1)
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

// ���뵽indexλ��
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

void Remove (SeqList* pSeq, size_t index)
{
	assert(pSeq);
	assert(index < pSeq->size);

	for (; index < pSeq->size - 1; ++index)
	{
		pSeq->array[index] = pSeq->array[index + 1];
	}

	pSeq->size--;
}

FindRet Find(SeqList* pSeq, DataType x, size_t index)
{
	FindRet ret;
	assert(pSeq);

	for (; index < pSeq->size; ++index)
	{
		if (x == pSeq->array[index])
		{
			ret.isFind = TRUE;
			ret.index = index;
			return ret;
		}
	}

	ret.isFind = FALSE;
	return ret;
}

//// ����-1����ʾɾ��ʧ�ܡ�
//// ����0����ʾɾ���ɹ���
//int Erase(SeqList* pSeq, DataType x)
//{
//	int i = 0;
//	assert(pSeq);
//	
//	while (i < pSeq->size)
//	{
//		if (pSeq->array[i] == x)
//		{
//			/*for (; i < pSeq->size - 1; ++i)
//			{
//				pSeq->array[i] = pSeq->array[i + 1];
//			}
//			pSeq->size--;*/
//			Remove(pSeq, i);
//			return 0;
//		}
//
//		++i;
//	}
//
//	if (i == pSeq->size)
//	{
//		return -1;
//	}
//
//	return 0;
//}

// ����-1����ʾɾ��ʧ�ܡ�
// ����0����ʾɾ���ɹ���
//int Erase(SeqList* pSeq, DataType x)
//{
//	int ret = 0;
//	assert(pSeq);
//	
//	ret = Find(pSeq, x);
//	if (ret != -1)
//	{
//		Remove(pSeq, ret);
//		return 0;
//	}
//	else
//	{
//		return -1;
//	}
//}

Tag Erase(SeqList* pSeq, DataType x, Tag all)
{
	Tag success = FALSE;
	FindRet ret;
	assert(pSeq);

	ret = Find(pSeq, x, 0);
	while(ret.isFind == TRUE)
	{
		success = TRUE;
		Remove(pSeq, ret.index);

		if (all == FALSE)
		{
			break;
		}

		ret = Find(pSeq, x, ret.index);
	}

	return success;
}
