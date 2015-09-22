#pragma once
#include <iostream>
#include <stack>
#include <assert.h>
using namespace std;

void PrintArray (const int* array, int size)
{
	for (int i = 0; i < size; ++i) {
		printf ("%d ", array[i]);
	}

	printf ("\n");
}

// ��������
void InsertSort(int* array, int size)
{
	assert(array);

	for (int index = 1; index < size; ++index)
	{
		// ����ǰ������ǰ����
		int insertIndex = index - 1;
		int tmp = array[index];
		while (insertIndex >= 0 && tmp < array[insertIndex])
		{
			array[insertIndex + 1] = array[insertIndex];
			--insertIndex;
		}

		// ע�������λ��
		array[insertIndex + 1] = tmp;
	}
}

// ���ڲ��������������������Խ�ӽ������������ƶ�����Խ�٣�
// ����ʹ��ϣ������������Ż���ʱ�临�Ӷȣ�N^1.25--1.6*N^1.25��
void ShellSort(int* array, int size)
{
	int gap = size;

	while (gap > 1)
	{
		// Knuth���������Ч������
		gap = gap/3 + 1;

		// ������gapΪ�������в�������
		for (int curIndex = gap; curIndex < size; ++curIndex)
		{
			int insertIndex = curIndex - gap;
			int tmp = array[curIndex];
			while (insertIndex >= 0 && tmp < array[insertIndex])
			{
				array[insertIndex + gap] = array[insertIndex];
				insertIndex -= gap;
			}

			array[insertIndex + gap] = tmp; 
		}
	}
}

// ѡ������
void SelectSort(int* array, int size)
{
	int statistics = 0;
	assert(array);

	for (int begin = 0; begin < size - 1; ++begin)
	{
		// ��ȡ��С���ݵ��±�
		int minIndex = begin;
		for (int index = begin + 1; index < size; ++index)
		{
			if (array[minIndex] > array[index])
			{
				minIndex = index;
			}

			++statistics;
		}

		if (minIndex != begin)
		{
			swap(array[minIndex], array[begin]);
		}
	}

	cout<<"statistics:"<<statistics<<endl;
}

// �Ż�ѡ������
void SelectSort_OP(int* array, int size)
{
	assert(array);

	int statistics = 0;

	int end = size - 1;
	for (int begin = 0; begin < end; ++begin)
	{
		// һ��ѡ��������ݼ���С����
		int minIndex = begin;
		int maxIndex = begin;
		for (int index = begin + 1; index <= end; ++index)
		{
			statistics++;

			if (array[minIndex] > array[index])
			{
				minIndex = index;
			}

			if (array[maxIndex] < array[index])
			{
				maxIndex = index;
			}
		}

		if (minIndex != begin)
		{
			swap(array[minIndex], array[begin]);
		}

		if (maxIndex != end)
		{
			swap(array[maxIndex], array[end]);
		}

		--end;
	}

	cout<<"statistics:"<<statistics<<endl;
}

// ������
void HeapAdjust(int* array, int root, int size)
{
	assert(array);

	// childΪ���ӵ��±�
	int child = root*2 + 1;
	while (child < size)
	{
		// �Ƚ����Ӻ��Һ��ӣ�childָ���ĺ��ӡ�
		if (child + 1 < size && array[child+1] > array[child])
		{
			child++;
		}

		// 1.����ĺ��ӽڵ���ڸ��ڵ㣬������Ҫ����������ѭ��
		// 2.���򣬽������ӽڵ�͸��ڵ㣬�����ڵ�������µ�����
		if(array[child] > array[root])
		{
			swap(array[child], array[root]);
			root = child;
			child = root*2 + 1;
		}
		else
		{
			break;
		}
	}
}

void HeapSort(int* array, int size)
{
	assert(array);

	// ������
	for (int i = (size - 1) / 2; i >= 0; --i)
	{
		HeapAdjust(array, i, size);
	}

	for (int i = size - 1; i > 0; --i)
	{
		swap(array[0], array[i]);
		HeapAdjust(array, 0, i);
	}
}

// ð������
void BubbleSort(int* array, int size)
{
	assert(array);

	int exchange = 0;
	int index, end;
	for (end = size - 1; end > 0; --end)
	{
		// ���ý�����־
		exchange = 0;

		// ����ð��
		for (index = 0; index < end; ++index)
		{
			if (array[index] > array[index + 1])
			{
				swap(array[index], array[index + 1]);
				exchange = 1;
			}
		}

		// ��һ�ν�����û�У�����������Ѿ����򣬲�����Ҫ����
		if (exchange == 0)
		{
			break;
		}
	}
}

// ��������
int GetMidIndex(int* array, int left, int right)
{
	int mid = left + ((right-left)>>1);

	if (array[left] < array[right])
	{
		if (array[right] < array[mid])
		{
			return right;
		}
		else if (array[left] > array[mid])
		{
			return left;
		}
		else
		{
			return mid;
		}
	}
	else
	{
		if (array[right] > array[mid])
		{
			return right;
		}
		else if (array[left] < array[mid])
		{
			return left;
		}
		else
		{
			return mid;
		}
	}
}

// ��������ǰ��ָ��汾��
int Partion1(int* array, int left, int right)
{
	//
	// prevָ���key���ǰһ��λ��
	// cur��ǰѰ�ұ�keyС�����ݡ�
	//
	int keyIndex = GetMidIndex(array, left, right);
	if (keyIndex != right)
	{
		swap(array[keyIndex], array[right]);
	}

	int key = array[right];
	int prev = left - 1;
	int cur = left;

	while (cur < right)
	{
		// �ҵ���key��С����������ǰ������ݽ��н���
		if(array[cur] < key && ++prev != cur)
		{
			swap(array[cur], array[prev]);
		}

		++cur;
	}

	swap(array[++prev], array[right]);

	return prev;
}

// ��������Hoare�汾��
int Partion2(int* array, int left, int right)
{
	int keyIndex = GetMidIndex(array, left, right);
	if (keyIndex != right)
	{
		swap(array[keyIndex], array[right]);
	}

	int key = array[right];
	int begin = left;
	int end = right;

	while (begin < end)
	{
		// ���������ҵ���key�������ʱͣ��
		while (array[begin] <= key && begin < end)
		{
			++begin;
		}

		// ���������ҵ���keyС������ʱͣ��
		while (array[end] >= key && begin < end)
		{
			--end;
		}

		// ��λ�û�û�н����򽻻����������ݡ�
		if (begin < end)
		{
			swap(array[begin], array[end]);
		}
	}

	if (begin != right)
	{
		swap(array[begin], array[right]);
	}

	return begin;
}

// ���������ڿӷ���
int Partion3(int* array, int left, int right)
{
	// ����ȡ��
	int keyIndex = GetMidIndex(array, left, right);
	if (keyIndex != right)
	{
		swap(array[keyIndex], array[right]);
	}

	// keyȡ���һ������
	int key = array[right];
	int begin = left;
	int end = right; // end��Ϊ��һ����

	while (begin < end)
	{
		// ���������ҵ���key�������ʱͣ��
		while (array[begin] <= key && begin < end)
		{
			++begin;
		}

		// �ҵ�һ����key������end���γ�һ���µĿ�begin
		if (begin < end)
		{
			array[end--] = array[begin];
		}

		// ���������ҵ���keyС������ʱͣ��
		while (array[end] >= key && begin < end)
		{
			--end;
		}

		// �ҵ�һ����keyС�����begin���γ�һ���µĿ�end
		if (begin < end)
		{
			array[begin++] = array[end];
		}
	}

	// ��key�������µĿ�
	array[end] = key;

	return begin;
}

void QuickSort(int* array, int left, int right)
{
	if (left < right)
	{
		int boundary = Partion3(array, left, right);

		QuickSort(array, left, boundary - 1);
		QuickSort(array, boundary + 1, right);
	}
}

// �ǵݹ�ʵ��
void QuickSort_NonRecursive(int* array, int left, int right)
{
	stack<int> s;

	// ע������ջ�ұ߽磬����ջ�߽�
	s.push(right);
	s.push(left);

	while(!s.empty())
	{
		left = s.top();
		s.pop();
		right = s.top();
		s.pop();

		if (left < right)
		{
			int boundary = Partion3(array, left, right);
			s.push(boundary - 1);
			s.push(left);
			s.push(right);
			s.push(boundary + 1);
		}
	}
}

// �������ݱȽ�Сʱʹ�ò��������Ż�
void QuickSort_OP(int* array, int left, int right)
{
	if (left < right)
	{
		int gap = right - left;

		if (gap < 5)
		{
			InsertSort(array + left, gap + 1);
		}
		else
		{
			int boundary = Partion2(array, left, right);
			QuickSort_OP(array, left, boundary - 1);
			QuickSort_OP(array, boundary + 1, right);
		}
	}
}

// �鲢����
void _Merge(int* src, int* dst, int begin, int mid, int end)
{
	int index = begin;
	int begin1 = begin, end1 = mid;
	int begin2 = mid, end2 = end; 
	while (begin1 < end1 && begin2 < end2)
	{
		if (src[begin1] < src[begin2])
		{
			dst[index++] = src[begin1++];
		}
		else
		{
			dst[index++] = src[begin2++];
		}
	}

	if (begin1 < end1)
	{
		memcpy(dst + index, src+begin1, sizeof(int)*(end1-begin1));
	}
	else if (begin2 < end2)
	{
		memcpy(dst + index, src+begin2, sizeof(int)*(end2-begin2));
	}
}

void MergeSort(int* array, int size)
{
	int* src = array;
	int* dst = new int[size];

	// gap�����鲢�Ĳ��ֵ
	int gap = 1;
	int begin, end, mid;
	while (gap < size)
	{
		for (int div = 0; div < size; div += 2*gap)
		{
			begin = div;
			mid = div+gap;
			end = div+2*gap;

			// �������mid��size��ֵ���ܴ���size
			if (mid > size)
			{
				mid = size;
			}

			if (end > size)
			{
				end = size;
			}

			_Merge(src, dst, begin, mid, end);
		}

		gap = 2*gap;
		swap(src, dst);
	}

	// ����dst&srcָ��ֵ
	if (dst == array)
	{
		memcpy(array, src, sizeof(int)*size);
		swap(src, dst);
	}

	delete [] dst;
}

/////////////////////////////////////////////////////
// ���Դ���

#define SIZE 20

void Test1()
{
	cout<<"BubbleSort:"<<endl;
	int array[SIZE] = {2, 5, 4, 9, 3, 6, 8, 7, 1, 0};
	PrintArray(array, SIZE);

	BubbleSort(array, SIZE);
	PrintArray(array, SIZE);
}

void Test2()
{
	cout<<"SelectSort:"<<endl;

	int array[SIZE] = {2, 5, 4, 9, 3, 6, 8, 7, 1, 0};
	PrintArray(array, SIZE);

	SelectSort(array, SIZE);
	//SelectSort_OP(array, SIZE);
	PrintArray(array, SIZE);
}

void Test3()
{
	cout<<"InsertSort:"<<endl;

	int array[SIZE] = {2, 5, 4, 9, 3, 6, 8, 7, 1, 0};
	PrintArray(array, SIZE);

	//InsertSort(array, SIZE);
	ShellSort(array, SIZE);
	PrintArray(array, SIZE);
}

void Test4()
{
	cout<<"HeapSort:"<<endl;

	int array[SIZE] = {2, 5, 4, 9, 3, 6, 8, 7, 1, 0};
	PrintArray(array, SIZE);

	HeapSort(array, SIZE);
	PrintArray(array, SIZE);
}

void Test5()
{
	cout<<"HeapSort:"<<endl;

	int array[SIZE] = {2, 5, 4, 9, 3, 6, 8, 7, 1, 0};
	PrintArray(array, SIZE);

	HeapSort(array, SIZE);
	PrintArray(array, SIZE);
}

void Test6()
{
	cout<<"QuickSort:"<<endl;

	int array[SIZE] = {2, 5, 4, 9, 3, 6, 8, 7, 1, 0};
	PrintArray(array, SIZE);

	//	QuickSort(array, 0, SIZE - 1);
	//	QuickSort_NonRecursive(array, 0, SIZE - 1);
	QuickSort_OP(array, 0, SIZE - 1);

	PrintArray(array, SIZE);
}

void Test7()
{
	cout<<"MergeSort:"<<endl;

	int array[SIZE] = {2, 5, 4, 9, 3, 6, 8, 7, 1, 0};
	PrintArray(array, SIZE);

	MergeSort(array, SIZE);

	PrintArray(array, SIZE);
}