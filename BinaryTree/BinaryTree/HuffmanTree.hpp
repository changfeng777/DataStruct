#pragma once

#include "Heap.hpp"

///////////////////////////////////////////////////////////////////////
// ��̬�ṹ

template<class T>
struct HuffmanNode
{
	T _weight;				// Ȩ��				
	HuffmanNode* _parent;	// ���ڵ�
	HuffmanNode* _left;	// ���ӽڵ�
	HuffmanNode* _right;	// �Һ��ӽڵ�

	HuffmanNode(const T& weight)
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
	{
		Destory(_root);
	}

	void Destory(HuffmanNode<T>*& root)
	{
		if (root)
		{
			Destory(root->_left);
			Destory(root->_right);
			
			delete root;
			root = NULL;
		}
	}

	HuffmanNode<T>* GetRootNode()
	{
		return _root;
	}

public:
	void CreateHuffmanTree(const T* array, size_t size, const T& invalid)
	{	
		struct Compare 
		{
			bool operator()(HuffmanNode<T>*& lhs, HuffmanNode<T>*& rhs)
			{
				return lhs->_weight < rhs->_weight;
			}
		};

		// 1.������ֵ����Ϊ�ڵ���뵽һ����С���У�Compare�º������Ƚ���
		Heap<HuffmanNode<T>*, Compare> minHeap;
		for (int i = 0; i < size; ++i)
		{
			if (array[i] != invalid)
			{
				HuffmanNode<T>* node = new HuffmanNode<T>(array[i]);
				minHeap.Push(node);
			}
		}

		if (minHeap.Empty())
			return;

		// 2.��ȡ����С�ʹ�С�Ľڵ������ӽڵ㣬���������������ӽڵ�ĸ��ڵ�������ӡ�
		HuffmanNode<T>* parent = minHeap.Top();
		while (minHeap.Size() > 1)
		{
			HuffmanNode<T>* first = minHeap.Top();
			minHeap.Pop();
			HuffmanNode<T>* second = minHeap.Top();
			minHeap.Pop();

			parent = new HuffmanNode<T>(first->_weight + second->_weight);
			parent->_left = first;
			parent->_right = second;
			first->_parent = parent;
			second->_parent = parent;

			minHeap.Push(parent);
		}

		_root = parent;
	}

	// ��α�����ӡ������
	void LevelOrder()
	{
		queue<HuffmanNode<T>* > q;
		if (_root)
		{
			q.push(_root);
		}

		while (!q.empty())
		{
			HuffmanNode<T>* node = q.front();
			cout<<node->_weight<<"	";

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

		cout<<endl<<endl;
	}

private:
	HuffmanNode<T>* _root;
};

void TestHuffmanTree_P()
{
	int ar[10] = {2, 3, 6, 0 ,4, 5, 1, 9, 7, 8};
	HuffmanTree_P<int> tree;
	tree.CreateHuffmanTree(ar, 10, -1);
	tree.LevelOrder();
}


//////////////////////////////////////////////////////////////////
// ��̬�洢�ṹ
	
typedef int IndexType;

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
		,_left(-1)
		,_right(-1)
		,_parent(-1)
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

		// ���ڵ��ָ�������С���У���д�Ƚ���
		_vNodes.reserve(size*2 - 1);
		Heap<HuffmanNode_A<T>*, Compare> minHeap;
		size_t index = 0;
		for (; index < size; ++index)
		{
			_vNodes.push_back(HuffmanNode_A<T>(array[index]));
			HuffmanNode_A<T>& node = _vNodes.back();
			node._index = index;
			minHeap.Push(&node);
		}

		while (minHeap.Size() > 1)
		{
			HuffmanNode_A<T>* first = minHeap.Top();
			minHeap.Pop();
			HuffmanNode_A<T>* second = minHeap.Top();
			minHeap.Pop();

			_vNodes.push_back(HuffmanNode_A<T>(first->_weight + second->_weight));
			HuffmanNode_A<T>& parent = _vNodes.back();
			parent._index = index++;
			minHeap.Push(&parent);

			first->_parent = parent._index;
			second->_parent = parent._index;
			parent._left = first->_index;
			parent._right = second->_index;
		}

		_rootIndex = minHeap.Top()->_index;
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