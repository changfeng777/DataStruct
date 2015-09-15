#pragma once
#include <vector>
#include <assert.h>
using namespace std;

template<class T, class Compare = less<T> >
class Heap
{
public:
	Heap()
	{}

	Heap(const T* array, size_t size)
	{
		assert(array);

		for (int i = 0; i< size; ++i)
		{
			_vec.push_back(array[i]);
		}

		for (int i = _vec.size()/2 - 1; i >=0; --i)
		{
			_AdjustDown(_vec, i, _vec.size());
		}
	}

	Heap(const vector<T>& vec)
	{
		_vec.swap(vec);

		for (int i = _vec.size()/2 - 1; i >=0; --i)
		{
			_AdjustDown(_vec, i, _vec.size());
		}
	}

	// 插入一个数据x到最小堆中
	void Insert(const T& x)
	{
		_vec.push_back(x);

		if (_vec.size() > 1)
		{
			_AdjustUp(_vec, _vec.size() - 1);
		}
	}

	// 删除堆顶元素
	void Remove()
	{
		int size = _vec.size();
		assert(size > 0);

		swap(_vec[0], _vec[size - 1]);
		_vec.pop_back();

		if (_vec.size() > 1)
		{
			_AdjustDown(_vec, 0, _vec.size());
		}
	}

	const T& GetHeapTop()
	{
		return _vec[0];
	}

	// 将根节点向下调整（小堆举例）
	void _AdjustDown(vector<T>& vec, int root, int size)
	{
		// 1.child指向左孩子节点
		int child = root * 2 + 1;
		while (child < size)
		{
			// 2.child指向左右孩子中小的节点
			if (child + 1 < size && Compare()(vec[child + 1], vec[child]))
			{
				++child;
			}

			// 3.若child小于跟节点，则交换child和root节点，并继续向下调整
			if (Compare()(vec[child], vec[root]))
			{
				swap(vec[child], vec[root]);
				root = child;
				child = root*2 + 1;
			}
			else
			{
				break;
			}
		}
	}

	// 一个节点向上调整（小堆举例说明）
	void _AdjustUp(vector<T>& vec, int pos)
	{
		// 1.parent指向父节点
		int child = pos;
		int parent = (child - 1) / 2;
		while(parent >= 0)
		{
			// 2.若child小于父节点，则交换父子节点，并继续向上调整，直到根节点
			if (Compare()(vec[child], vec[parent]))
			//if (vec[child] < vec[parent])
			{
				swap(vec[child], vec[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}

	// 判断是否为空
	bool Empty()
	{
		return _vec.empty();
	}

	size_t Size()
	{
		return _vec.size();
	}

private:
	vector<T> _vec;
};

// 测试堆
//void TestHeap()
//{
//	Heap<int, greater<int>> heap;
//	heap.Insert(3);
//	heap.Insert(5);
//	heap.Insert(1);
//	heap.Insert(4);
//	heap.Insert(5);
//	heap.Insert(1);
//	heap.Insert(8);
//
//	while (!heap.Empty())
//	{
//		cout<<heap.GetHeapTop()<<" ";
//		heap.Remove();
//	}
//	cout<<endl;
//
//	//int array[10] = {9,1,3,5,6,7,8,0,2,4};
//	int array[10] = {10,16,18,12,11,13,15,17,14,19};
//	Heap<int> heap1(array, 10);
//
//	while (!heap1.Empty())
//	{
//		cout<<heap1.GetHeapTop()<<" ";
//		heap1.Remove();
//	}
//	cout<<endl;
//}