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

// 插入排序
void InsertSort(int* array, int size)
{
	assert(array);

	for (int index = 1; index < size; ++index)
	{
		// 将当前数据往前插入
		int end = index - 1;
		int tmp = array[index];
		while (end >= 0 && tmp < array[end])
		{
			array[end + 1] = array[end];
			--end;
		}

		// 注意这里的位置
		array[end + 1] = tmp;
	}
}

// 对于插入排序，如果待排序数据越接近有序，则数据移动次数越少，
// 所以使用希尔排序进行了优化。时间复杂度（N^1.25--1.6*N^1.25）
void ShellSort(int* array, int size)
{
	int gap = size;

	while (gap > 1)
	{
		// Knuth提出的增量效果更好
		gap = gap/3 + 1;

		// 单次以gap为增量进行插入排序
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

// 选择排序
void SelectSort(int* array, int size)
{
	int statistics = 0;
	assert(array);

	for (int begin = 0; begin < size - 1; ++begin)
	{
		// 获取最小数据的下标
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
// 优化选择排序（以下方法有问题，当最大的数就在头部的位置上时，就会有问题）
// 如：6,3,2,4,5,0,1，第一趟排序，min为0，max为6，一交换以后，变成了1,3,2,4,5,6,0
//
//void SelectSort_OP(int* array, int size)
//{
//	assert(array);
//
//	int end = size - 1;
//	for (int begin = 0; begin < end; ++begin)
//	{
//		// 一次选出最大数据及最小数据
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

// 使用比较之后则进行交换校正
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

// 堆排序
void HeapAdjust(int* array, int root, int size)
{
	assert(array);

	// child为左孩子的下标
	int child = root*2 + 1;
	while (child < size)
	{
		// 比较左孩子和右孩子，child指向大的孩子。
		if (child + 1 < size && array[child+1] > array[child])
		{
			child++;
		}

		// 1.若大的孩子节点大于根节点，则不再需要调整，跳出循环
		// 2.否则，交换孩子节点和根节点，将根节点继续往下调整。
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

	// 创建堆
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

// 冒泡排序
void BubbleSort(int* array, int size)
{
	assert(array);

	int index, end;
	for (end = size - 1; end > 0; --end)
	{
		// 重置交换标志
		int exchange = 0;

		// 单次冒泡
		for (index = 0; index < end; ++index)
		{
			if (array[index] > array[index + 1])
			{
				swap(array[index], array[index + 1]);
				exchange = 1;
			}
		}

		// 若一次交换都没有，则这段数据已经有序，不再需要排序
		if (exchange == 0)
		{
			break;
		}
	}
}

// 快速排序
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

// 快速排序（前后指针版本）
int Partion1(int* array, int left, int right)
{
	//
	// prev指向比key大的前一个位置
	// cur向前寻找比key小的数据。
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
		// 找到比key的小的数据则与前面的数据进行交换
		if(array[cur] < key && ++prev != cur)
		{
			swap(array[cur], array[prev]);
		}

		++cur;
	}

	swap(array[++prev], array[right]);

	return prev;
}

// 快速排序（Hoare版本）
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
		// 从左往右找到比key大的数据时停下
		while (array[begin] <= key && begin < end)
		{
			++begin;
		}

		// 从右往左找到比key小的数据时停下
		while (array[end] >= key && begin < end)
		{
			--end;
		}

		// 若位置还没有交错，则交换着两个数据。
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

// 快速排序（挖坑法）
int Partion3(int* array, int left, int right)
{
	// 三数取中
	int keyIndex = GetMidIndex(array, left, right);
	if (keyIndex != right)
	{
		swap(array[keyIndex], array[right]);
	}

	// key取最后一个数据
	int key = array[right];
	int begin = left;
	int end = right; // end作为第一个坑

	while (begin < end)
	{
		// 从左往右找到比key大的数据时停下
		while (array[begin] <= key && begin < end)
		{
			++begin;
		}

		// 找到一个比key大的数填到end，形成一个新的坑begin
		if (begin < end)
		{
			array[end--] = array[begin];
		}

		// 从右往左找到比key小的数据时停下
		while (array[end] >= key && begin < end)
		{
			--end;
		}

		// 找到一个比key小的数填到begin，形成一个新的坑end
		if (begin < end)
		{
			array[begin++] = array[end];
		}
	}

	// 将key填到最后留下的坑
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

// 非递归实现
void QuickSort_NonRecursive(int* array, int left, int right)
{
	stack<int> s;

	// 注意先入栈右边界，再入栈边界
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

// 区段数据比较小时使用插入排序优化
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

// 归并排序，这里合并的区间为[begin,mid) [mid, end)
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

	// 将合并的数据拷贝回src数组中
	memcpy(src+begin, dst+begin, sizeof(int)*(end - begin));
}

void MergeSort(int* array, int size)
{
	int* src = array;
	int* dst = new int[size];

	// gap两两归并的差距值
	int gap = 1;
	int begin, end, mid;
	while (gap < size)
	{
		for (int div = 0; div < size; div += 2*gap)
		{
			begin = div;
			mid = div+gap;
			end = div+2*gap;

			// 检查修正mid和size的值不能大于size
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

	// 当区间比较小时，使用插入排序减少递归更高效一些
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
// 非比较排序->计数排序&基数排序

// 计数排序--对比与前面的比较排序
void CountSort(int* array, int size)
{
	assert(array);

	// 找出最大和最小的值
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

	// 统计min-max范围内数据的出现个数
	int range = max - min + 1;
	int* count = new int[range];
	memset(count, 0, range*sizeof(int));
	for (int i = 0; i < size; ++i)
	{
		count[array[i] - min]++;
	}

	// 根据统计数据的个数进行排序
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
	int a[] = { 1, 1, 10, 100 }; // 本实例中的最大数是百位数，所以只要到100就可以了
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

// 基数排序--桶排序
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
		
		// 确定对应位桶数据的个数，及确定在桶中的位置
		for (int i = 0; i < size; ++i)
		{
			int k = (array[i]/radix)%10;
			count[k]++;
		}
		for (int i = 1; i < 10; ++i)
		{
			count[i] = count[i] + count[i-1];
		}

		// 将数据放到对应的桶中
		for (int i = size - 1; i >= 0; --i)
		{
			int k = (array[i]/radix) % 10;
			bucket[count[k] - 1] = array[i];
			count[k]--;
		}

		// 将桶中排后数据拷贝回原数组
		memcpy(array, bucket, sizeof(int)*size);

		radix *= 10;
	}

	delete [] count;
	delete [] bucket;
}

#include <math.h>

// 基数排序--桶排序MSD
// [left, right)
void _RadixSort_MSD(int* array, int left, int right, int bit, int* bucket, int* count)
{
	if (left >= right-1 || bit < 1)
		return;

	assert(array);
	assert(bucket);
	assert(count);

	// 当区间小于一定数值时，直接使用插入排序，这样更高效
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
	
	// 将数据放到对应的桶中
	for (int i = right-1; i >= left; --i)
	{
		int k = (array[i]/radix) % 10;
		bucket[count[k] - 1] = array[i];
		count[k]--;
	}

	// 将桶中排后数据拷贝回原数组
	memcpy(array, bucket, sizeof(int)*(right-left));

	// 对区间进行递归排序
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
// 测试代码

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