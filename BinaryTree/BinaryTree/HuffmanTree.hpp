#pragma once

#include "Heap.hpp"

///////////////////////////////////////////////////////////////////////
// ��̬�ṹ

template<class T>
struct HuffmanNode_P
{
	T _weight;				// Ȩ��				
	HuffmanNode_P* _parent;	// ���ڵ�
	HuffmanNode_P* _left;	// ���ӽڵ�
	HuffmanNode_P* _right;	// �Һ��ӽڵ�

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

		// 1.������ֵ����Ϊ�ڵ���뵽һ����С���У�Compare�º������Ƚ���
		Heap<HuffmanNode_P<T>*, Compare> minHeap;
		for (int i = 0; i < size; ++i)
		{
			HuffmanNode_P<T>* node = new HuffmanNode_P<T>(array[i]);
			minHeap.Insert(node);
		}

		// 2.��ȡ����С�ʹ�С�Ľڵ������ӽڵ㣬���������������ӽڵ�ĸ��ڵ�������ӡ�
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

	// ��α�����ӡ������
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
// ��̬�洢�ṹ

typedef unsigned int IndexType;

template<class T>
struct HuffmanNode_A
{
	T _weight;			// Ȩֵ
	IndexType _parent;	// ���ڵ�
	IndexType _left;	// ����
	IndexType _right;	// �Һ���
	IndexType _index;	// �±�

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
	vector<HuffmanNode_A<T> > _vNodes;	// ��̬�洢�ṹ
	IndexType _rootIndex;				// ���ڵ���±�
};

void TestHuffmanTree_A()
{
	int ar[10] = {2, 3, 6, 0 ,4, 5, 1, 9, 7, 8};
	HuffmanTree_A<int> tree;
	tree.CreateHuffmanTree(ar, 10);
}