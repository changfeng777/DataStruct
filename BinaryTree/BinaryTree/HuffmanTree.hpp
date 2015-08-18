#pragma once

#include "Heap.hpp"

///////////////////////////////////////////////////////////////////////
// 动态结构

template<class T>
struct HuffmanNode_P
{
	T _weight;				// 权重				
	HuffmanNode_P* _parent;	// 父节点
	HuffmanNode_P* _left;	// 左孩子节点
	HuffmanNode_P* _right;	// 右孩子节点

	HuffmanNode_P(const T& weight)
		:_parent(NULL)
		,_left(NULL)
		,_right(NULL)
		,_weight(weight)
	{}
};

template<class T>
class HuffmanTree_P
{
public:
	HuffmanTree_P()
		:_root(NULL)
	{}
	
	~HuffmanTree_P()
	{}

public:
	void CreateHuffmanTree(const T* array, size_t size)
	{	
		struct Compare 
		{
			bool operator()(HuffmanNode_P<T>*& lhs, HuffmanNode_P<T>*& rhs)
			{
				return lhs->_weight < rhs->_weight;
			}
		};

		// 1.将所有值构建为节点放入到一个最小堆中，Compare仿函数做比较器
		Heap<HuffmanNode_P<T>*, Compare> minHeap;
		for (int i = 0; i < size; ++i)
		{
			HuffmanNode_P<T>* node = new HuffmanNode_P<T>(array[i]);
			minHeap.Insert(node);
		}

		// 2.获取出最小和次小的节点做孩子节点，并构建这两个孩子节点的父节点进行链接。
		HuffmanNode_P<T>* parent = minHeap.GetHeapTop();
		while (minHeap.Size() > 1)
		{
			HuffmanNode_P<T>* first = minHeap.GetHeapTop();
			minHeap.Remove();
			HuffmanNode_P<T>* second = minHeap.GetHeapTop();
			minHeap.Remove();

			parent = new HuffmanNode_P<T>(first->_weight + second->_weight);
			parent->_left = first;
			parent->_right = second;
			first->_parent = parent;
			second->_parent = parent;

			minHeap.Insert(parent);
		}

		_root = parent;
	}

	// 层次遍历打印二叉树
	void LevelOrder()
	{
		queue<HuffmanNode_P<T>* > q;
		if (_root)
		{
			q.push(_root);
		}

		while (!q.empty())
		{
			HuffmanNode_P<T>* node = q.front();
			cout<<node->_weight<<" ";

			if (node->_left)
			{
				q.push(node->_left);
			}

			if (node->_right)
			{
				q.push(node->_right);
			}
			q.pop();
		}
	}

private:
	HuffmanNode_P<T>* _root;
};

void TestHuffmanTree_P()
{
	int ar[10] = {2, 3, 6, 0 ,4, 5, 1, 9, 7, 8};
	HuffmanTree_P<int> tree;
	tree.CreateHuffmanTree(ar, 10);
	tree.LevelOrder();
}


//////////////////////////////////////////////////////////////////
// 静态存储结构

typedef unsigned int IndexType;

template<class T>
struct HuffmanNode_A
{
	T _weight;			// 权值
	IndexType _parent;	// 父节点
	IndexType _left;	// 左孩子
	IndexType _right;	// 右孩子
	IndexType _index;	// 下标

	HuffmanNode_A(const T& weight)
		:_weight(weight)
		,_left(0)
		,_right(0)
		,_parent(0)
	{}
};

template<class T> 
class HuffmanTree_A
{
public:
	void CreateHuffmanTree(const T* array, size_t size)
	{
		struct Compare 
		{
			bool operator()(const HuffmanNode_A<T>* lhs, const HuffmanNode_A<T>* rhs)
			{
				return lhs->_weight < rhs->_weight;
			}
		};

		_vNodes.reserve(size*2 - 1);
		Heap<HuffmanNode_A<T>*, Compare> minHeap;
		size_t index = 0;
		for (; index < size; ++index)
		{
			_vNodes.push_back(HuffmanNode_A<T>(array[index]));
			HuffmanNode_A<T>& node = _vNodes.back();
			node._index = index;
			minHeap.Insert(&node);
		}

		while (minHeap.Size() > 1)
		{
			HuffmanNode_A<T>* first = minHeap.GetHeapTop();
			minHeap.Remove();
			HuffmanNode_A<T>* second = minHeap.GetHeapTop();
			minHeap.Remove();

			_vNodes.push_back(HuffmanNode_A<T>(first->_weight + second->_weight));
			HuffmanNode_A<T>& parent = _vNodes.back();
			parent._index = index++;
			minHeap.Insert(&parent);

			first->_parent = parent._index;
			second->_parent = parent._index;
			parent._left = first->_index;
			parent._right = second->_index;
		}

		_rootIndex = minHeap.GetHeapTop()->_index;
	}

private:
	vector<HuffmanNode_A<T> > _vNodes;	// 静态存储结构
	IndexType _rootIndex;				// 根节点的下标
};

void TestHuffmanTree_A()
{
	int ar[10] = {2, 3, 6, 0 ,4, 5, 1, 9, 7, 8};
	HuffmanTree_A<int> tree;
	tree.CreateHuffmanTree(ar, 10);
}