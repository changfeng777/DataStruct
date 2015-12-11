#pragma once
#include <iostream>
#include <stack>
#include <assert.h>
using namespace std;

void PrintArray (const int* array, int size)
{
	for (int i = 0; i < size; ++i)
	{
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
		int end = index - 1;
		int tmp = array[index];
		while (end >= 0 && tmp < array[end])
		{
			array[end + 1] = array[end];
			--end;
		}

		// ע�������λ��
		array[end + 1] = tmp;
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
		for (int cur = gap; cur < size; ++cur)
		{
			int end = cur - gap;
			int tmp = array[cur];
			while (end >= 0 && tmp < array[end])
			{
				array[end + gap] = array[end];
				end -= gap;
			}

			array[end + gap] = tmp; 
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

//
// �Ż�ѡ���������·��������⣬������������ͷ����λ����ʱ���ͻ������⣩
// �磺6,3,2,4,5,0,1����һ������minΪ0��maxΪ6��һ�����Ժ󣬱����1,3,2,4,5,6,0
//
//void SelectSort_OP(int* array, int size)
//{
//	assert(array);
//
//	int end = size - 1;
//	for (int begin = 0; begin < end; ++begin)
//	{
//		// һ��ѡ��������ݼ���С����
//		int minIndex = begin;
//		int maxIndex = begin;
//		for (int index = begin + 1; index <= end; ++index)
//		{
//			if (array[minIndex] > array[index])
//			{
//				minIndex = index;
//			}
//
//			if (array[maxIndex] < array[index])
//			{
//				maxIndex = index;
//			}
//		}
//
//		if (minIndex != begin)
//		{
//			swap(array[minIndex], array[begin]);
//		}
//
//		if (maxIndex != end)
//		{
//			swap(array[maxIndex], array[end]);
//		}
//
//		--end;
//	}
//}

// ʹ�ñȽ�֮������н���У��
void SelectSort_OP(int* array, int size)
{
	assert(array);

	int begin = 0, end = size - 1;
	while (begin < end)
	{
		int cur = begin;
		while (cur < end)
		{
			if (array[begin] > array[cur])
				swap(array[begin], array[cur]);
			if (array[end] < array[cur])
				swap(array[end], array[cur]);

			++cur;
		}

		++begin;
		--end;
	}
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
	for (int i = size/2 - 1; i >= 0; --i)
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

	int index, end;
	for (end = size - 1; end > 0; --end)
	{
		// ���ý�����־
		int exchange = 0;

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

		if (gap < 13)
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

// �鲢��������ϲ�������Ϊ[begin,mid) [mid, end)
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

	// ���ϲ������ݿ�����src������
	memcpy(src+begin, dst+begin, sizeof(int)*(end - begin));
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
				mid = size;

			if (end > size)
				end = size;

			_Merge(src, dst, begin, mid, end);
		}

		gap = 2*gap;
	}

	delete [] dst;
}

void _MergeSort_R(int* src, int* dst, int left, int right)
{
	// [left, right)
	if (left+1 >= right)
		return;

	int mid = left + (right - left)/2;
	_MergeSort_R(src, dst, left, mid);
	_MergeSort_R(src, dst, mid, right);
	_Merge(src, dst, left, mid, right);
}

void _MergeSort_R_OP(int* src, int* dst, int left, int right)
{
	// [left, right)
	if (left+1 >= right)
		return;

	// ������Ƚ�Сʱ��ʹ�ò���������ٵݹ����ЧһЩ
	//if (right - left < 13)
	if (right - left < 5)
	{
		InsertSort(src+left, right - left);
		return;
	}

	int mid = left + (right - left)/2;
	_MergeSort_R_OP(src, dst, left, mid);
	_MergeSort_R_OP(src, dst, mid, right);
	_Merge(src, dst, left, mid, right);
}

void MergeSort_R(int* array, int size)
{
	int* tmp = new int[size];
	//_MergeSort_R(array, tmp, 0, size);
	_MergeSort_R_OP(array, tmp, 0, size);
	delete[] tmp;
}

/////////////////////////////////////////////////////////////////////
// �ǱȽ�����->��������&��������

// ��������--�Ա���ǰ��ıȽ�����
void CountSort(int* array, int size)
{
	assert(array);

	// �ҳ�������С��ֵ
	int max = array[0];
	int min = array[0];
	for (int i = 1; i < size; ++i)
	{
		if (array[i] > max)
		{
			max = array[i];
		}
		if (array[i] < min)
		{
			min = array[i];
		}
	}

	// ͳ��min-max��Χ�����ݵĳ��ָ���
	int range = max - min + 1;
	int* count = new int[range];
	memset(count, 0, range*sizeof(int));
	for (int i = 0; i < size; ++i)
	{
		count[array[i] - min]++;
	}

	// ����ͳ�����ݵĸ�����������
	int index = 0;
	for (int i = 0; i < range; ++i)
	{
		while(count[i]--)
		{
			array[index++] = i+min;
		}
	}

	delete[] count;
}

int getDigit(int x, int d)
{
	int a[] = { 1, 1, 10, 100 }; // ��ʵ���е�������ǰ�λ��������ֻҪ��100�Ϳ�����
	return ((x / a[d]) % 10);
}

int _GetMaxBit(int* array, int size)
{
	int bit = 1;
	int max = 10;
	for (int i = 0; i < size; ++i)
	{
		while(array[i] >= max)
		{
			max *= 10;
			bit++;
		}
	}
	return bit;
}

// ��������--Ͱ����
void RadixSort_LSD(int* array, int size)
{
	int maxBit = _GetMaxBit(array, size);
	int* bucket = new int[size];
	int* count = new int[10];
	memset(bucket, 0, sizeof(int)*size);

	int radix = 1;
	for (int bit = 1; bit <= maxBit; ++bit)
	{
		memset(count, 0, sizeof(int)*10);
		
		// ȷ����ӦλͰ���ݵĸ�������ȷ����Ͱ�е�λ��
		for (int i = 0; i < size; ++i)
		{
			int k = (array[i]/radix)%10;
			count[k]++;
		}
		for (int i = 1; i < 10; ++i)
		{
			count[i] = count[i] + count[i-1];
		}

		// �����ݷŵ���Ӧ��Ͱ��
		for (int i = size - 1; i >= 0; --i)
		{
			int k = (array[i]/radix) % 10;
			bucket[count[k] - 1] = array[i];
			count[k]--;
		}

		// ��Ͱ���ź����ݿ�����ԭ����
		memcpy(array, bucket, sizeof(int)*size);

		radix *= 10;
	}

	delete [] count;
	delete [] bucket;
}

#include <math.h>

// ��������--Ͱ����MSD
// [left, right)
void _RadixSort_MSD(int* array, int left, int right, int bit, int* bucket, int* count)
{
	if (left >= right-1 || bit < 1)
		return;

	assert(array);
	assert(bucket);
	assert(count);

	// ������С��һ����ֵʱ��ֱ��ʹ�ò���������������Ч
	if (right - left < 5)
	{
		InsertSort(array+left, right-left);
		return;
	}

	int radix = pow(10.0, bit-1);
	memset(count, 0, sizeof(int)*10);

	for (int i = left; i < right; ++i)
	{
		int k = (array[i]/radix)%10;
		count[k]++;
	}
	for (int i = 1; i < 10; ++i)
	{
		count[i] = count[i] + count[i-1];
	}
	
	// �����ݷŵ���Ӧ��Ͱ��
	for (int i = right-1; i >= left; --i)
	{
		int k = (array[i]/radix) % 10;
		bucket[count[k] - 1] = array[i];
		count[k]--;
	}

	// ��Ͱ���ź����ݿ�����ԭ����
	memcpy(array, bucket, sizeof(int)*(right-left));

	// ��������еݹ�����
	for (int i = 0; i < 10; ++i)
	{
		int interval1 = left + count[i];
		int interval2 = left + count[i+1];

		_RadixSort_MSD(array, interval1, interval2, bit-1, bucket, count);
	}
}

void RadixSort_MSD(int* array, int size)
{
	int maxBit = _GetMaxBit(array, size);
	int* bucket = new int[size];                                                          int* count = new int[10];

	_RadixSort_MSD(array, 0, size, maxBit, bucket, count);

	delete[] count;
	delete[] bucket;
}


/////////////////////////////////////////////////////
// ���Դ���

#define SIZE 10

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

	//int array[SIZE] = {2, 5, 4, 9, 3, 6, 8, 7, 1, 0};
	int array[SIZE] = {6,3,2,4,5,0,1};
	PrintArray(array, SIZE);

	//SelectSort(array, SIZE);
	SelectSort_OP(array, 7);
	PrintArray(array, 7);
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

	//MergeSort(array, SIZE);
	MergeSort_R(array, SIZE);

	PrintArray(array, SIZE);
}

void Test8()
{
	cout<<"CountSort:"<<endl;

	int array[SIZE] = {2, 5, 4, 9, 3, 6, 8, 7, 1, 10};
	PrintArray(array, SIZE);

	CountSort(array, SIZE);

	PrintArray(array, SIZE);
}

void Test9()
{
	cout<<"RadixSort:"<<endl;

	int array[SIZE] = {21, 51, 22, 26, 300, 6, 240, 7, 10, 10};
	PrintArray(array, SIZE);

	//RadixSort_LSD(array, SIZE);
	RadixSort_MSD(array, SIZE);

	PrintArray(array, SIZE);
}