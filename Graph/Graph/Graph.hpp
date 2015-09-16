#pragma once

#include<assert.h>
#include <queue>
#include "Heap.hpp"
#include "UnionFindSet.hpp"

//
// �ٽӾ����ʾ����ͼ&����ͼ
//

template<class V, class W>
class GraphMatrix
{
public:
	GraphMatrix()
	{}

	GraphMatrix(const V* vertexs, int size)
		:_vertexSize(size)
	{
		// ���پ���ͱ߼�
		_matrix = new W*[_vertexSize];
		_vertexs = new V[_vertexSize];

		for (int i = 0; i < _vertexSize; ++i)
		{
			// ��ʼ������
			_matrix[i] = new W[_vertexSize];
			memset(_matrix[i], 0, sizeof(W)*_vertexSize);

			// ��ʼ���߼�
			_vertexs[i] = vertexs[i];
		}
	}

	int GetVertexIndex(const V& vtx)
	{
		for (int i = 0; i < _vertexSize; ++i)
		{
			if (_vertexs[i] == vtx)
			{
				return i;
			}
		}

		return -1;
	}

	void AddEdge(const V& src, const V& dst, const W& weight)
	{
		int srcIndex = GetVertexIndex(src); 
		int dstIndex = GetVertexIndex(dst);

		assert(srcIndex != -1);
		assert(dstIndex != -1);
		
		_matrix[srcIndex][dstIndex] = weight;
		//_matrix[dstIndex][srcIndex] = weight;
	}

	void Display()
	{
		for (int i = 0; i < _vertexSize; ++i)
		{
			cout<<_vertexs[i]<<" ";
		}
		cout<<endl<<endl; 

		for (int i = 0; i < _vertexSize; ++i)
		{
			for (int j = 0; j < _vertexSize; ++j)
			{
				cout<<_matrix[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
	}

private:
	W**	 _matrix;		// �ٽӾ���
	V*	 _vertexs;		// ���㼯			
	int	 _vertexSize;	// ������
	//int	 _edgeSize;		// ������
};

// ����ͼ
void Test1()
{
	GraphMatrix<char, int> g("ABCDE", 5);
	g.AddEdge('A', 'D', 10);
	g.AddEdge('A', 'E', 20);
	g.AddEdge('B', 'C', 10);
	g.AddEdge('B', 'D', 20);
	g.AddEdge('B', 'E', 30);
	g.AddEdge('C', 'E', 40);

	g.Display();
}

// ����ͼ
void Test2()
{
	GraphMatrix<char, int> g("ABCDE", 5);
	g.AddEdge('A', 'D', 10);
	g.AddEdge('E', 'A', 20);
	g.AddEdge('B', 'C', 10);
	g.AddEdge('D', 'B', 20);
	g.AddEdge('E', 'B', 30);
	g.AddEdge('C', 'E', 40);

	g.Display();
}

//
// �ٽӱ�
//

template<class V, class W>
struct LinkEdge
{
	int _srcIndex;			// Դ�����±�
	int _dstIndex;			// Ŀ�궥���±�
	W _weight;				// Ȩ��
	LinkEdge<V, W>* _next;	// ָ����һ���ڵ��ָ�� 

	LinkEdge(int srcIndex = -1, int dstIndex = -1, const W& weight = W())
		:_srcIndex(srcIndex)
		,_dstIndex(dstIndex)
		,_weight(weight)
		,_next(NULL)
	{}
};

template<class V, class W>
struct LinkVertex
{
	V _vertex;				// ����
	LinkEdge<V, W>* _head;	// ָ���ٽӱ�ı�

	LinkVertex(const V& vertex = V())
		:_vertex(vertex)
		,_head(NULL)
	{}
};

template<class V, class W>
struct CompareLinkEdge
{
	bool operator()(LinkEdge<V, W>* lhs, LinkEdge<V, W>* rhs)
	{
		return lhs->_weight < rhs->_weight;
	}
};

template<class V, class W>
class GraphLink
{
public:
	GraphLink()
		:_linkTable(0)
		,_vertexSize(0)
	{}

	GraphLink(const V* ar, int size)
		:_vertexSize(size)
	{
		_linkTable = new LinkVertex<V, W>[size];
		for (int i = 0; i < size; ++i)
		{
			_linkTable[i]._vertex = ar[i];
		}
	}

	~GraphLink()
	{}

public:
	int GetVertexIndex(const V& vertex)
	{
		for (int i = 0; i < _vertexSize; ++i)
		{
			if(_linkTable[i]._vertex == vertex)
			{
				return i;
			}
		}

		return -1;
	}

	void _AddEdge(int srcIndex, int dstIndex, const W& weight)
	{
		LinkEdge<V, W>* head = _linkTable[srcIndex]._head;
		LinkEdge<V, W>* tmp = new LinkEdge<V, W>(srcIndex, dstIndex, weight);

		tmp->_next = head;
		_linkTable[srcIndex]._head = tmp;
	}

	void AddEdge(const V& src, const V& dst, const W& weight)
	{
		int srcIndex = GetVertexIndex(src);
		int dstIndex = GetVertexIndex(dst);

		assert(srcIndex != -1);
		assert(dstIndex != -1);

		// ����ͼ
		_AddEdge(srcIndex, dstIndex, weight);
		_AddEdge(dstIndex, srcIndex, weight);

		// ����ͼ
		//_AddEdge(srcIndex, dstIndex, weight);
	}

	void Display()
	{
		for (int i = 0; i < _vertexSize; ++i)
		{
			cout<<_linkTable[i]._vertex<<"["<<i<<"]->";
			LinkEdge<V, W>* begin = _linkTable[i]._head;
			while (begin)
			{
				cout<<begin->_weight<<"["<<begin->_dstIndex<<"]""->";
				begin = begin->_next;
			}

			cout<<"NULL"<<endl;
		}

		cout<<endl;
	}

	int _GetFirstVertex(int cur)
	{
		if (_linkTable[cur]._head)
			return _linkTable[cur]._head->_dstIndex;
		else
			return -1;
	}

	int _GetNextVertex(int cur, int next)
	{
		LinkEdge<V,W>* edge = _linkTable[cur]._head;
		while (edge)
		{
			if (edge->_dstIndex == next)
			{
				if (edge->_next)
					return edge->_next->_dstIndex;

				break;
			}
			edge = edge->_next;
		}

		return -1;
	}

	void DFS(int cur)
	{
		cout<<"DFS:";

		bool* visited = new bool[_vertexSize];
		memset(visited, false, sizeof(bool)*_vertexSize);

		_DFS(cur, visited);

		delete[] visited;

		cout<<endl;
	}

	void _DFS(int cur, bool* visited)
	{
		// 1.���ʵ�ǰ�ڵ�
		cout<<_linkTable[cur]._vertex<<" ";
		visited[cur] = true;

		// 2.��ȡ��ǰ�ٽӱ�ĵ�һ������
		int next = _GetFirstVertex(cur);

		// 3.���λ�ȡ�ٽӱ����Ķ������������ȱ���
		while (next != -1)
		{
			if (visited[next] == false)
			{
				_DFS(next, visited);
			}

			// 4.���ҵ�ǰ�������һ������
			next = _GetNextVertex(cur, next);
		}
	}

	void BFS(int cur)
	{
		cout<<"BFS:";
		bool* visited = new bool[_vertexSize];
		memset(visited, false, sizeof(bool)*_vertexSize);

		_BFS(cur, visited);

		delete[] visited;

		cout<<endl;
	}
	
	void _BFS(int cur, bool* visited)
	{
		cout<<_linkTable[cur]._vertex<<" ";
		visited[cur] = true;

		queue<int> q;
		q.push(cur);
		while (!q.empty())
		{
			cur = q.front();
			q.pop();

			int next = _GetFirstVertex(cur);
			while (next != -1)
			{
				if (visited[next] == false)
				{
					cout<<_linkTable[next]._vertex<<" ";
					visited[next] = true;
					q.push(next);
				}

				next = _GetNextVertex(cur, next);
			}
		}
	}

	bool Kruskal(GraphLink& minSpanTree)
	{
		// 1.��ʼ����С������
		minSpanTree._linkTable = new LinkVertex<V, W>[_vertexSize];
		minSpanTree._vertexSize = _vertexSize;
		for (int i = 0; i < _vertexSize; ++i)
		{
			minSpanTree._linkTable[i]._vertex = _linkTable[i]._vertex;
		}

		// 2.�����еı߷ŵ�һ����С��
		Heap<LinkEdge<V,W>*, CompareLinkEdge<V,W>> minHeap;
		for (int i = 0; i < _vertexSize; ++i)
		{
			LinkEdge<V, W>* begin = _linkTable[i]._head;
			while (begin)
			{
				// ����ͼ�ı���Ҫ���й���
				if (begin->_srcIndex < begin->_dstIndex)
				{
					minHeap.Insert(begin);
				}

				begin = begin->_next;
			}
		}
		
		// 3.ʹ�ò������С�ѹ�����С������
		UnionFindSet UFSet(_vertexSize);
		int count = _vertexSize;
		while (--count)
		{
			if (minHeap.Empty())
			{
				return false;
			}

			LinkEdge<V,W>* edge = minHeap.GetHeapTop();
			minHeap.Remove();
			int src = UFSet.Find(edge->_srcIndex);
			int dst = UFSet.Find(edge->_dstIndex);

			if(src != dst)
			{
				UFSet.Union(src, dst);
				minSpanTree._AddEdge(edge->_srcIndex, edge->_dstIndex, edge->_weight);
			}
		}

		return true;
	}

protected:
	LinkVertex<V, W>* _linkTable;	// �ٽӱ�
	int _vertexSize;				// �������
};

// ����ͼ
void Test3()
{
	GraphLink<char, int> g("ABCDE", 5);
	g.AddEdge('A', 'D', 10);
	g.AddEdge('A', 'E', 20);
	g.AddEdge('B', 'C', 10);
	g.AddEdge('B', 'D', 20);
	g.AddEdge('B', 'E', 30);
	g.AddEdge('C', 'E', 40);
	g.Display();

	// ������С������
	GraphLink<char, int> minSpanTree;
	g.Kruskal(minSpanTree);

	minSpanTree.Display();
	g.DFS(0);
	g.BFS(0);
}

// ����ͼ
void Test4()
{
	GraphLink<char, int> g("ABCDE", 5);
	g.AddEdge('A', 'D', 10);
	g.AddEdge('E', 'A', 20);
	g.AddEdge('B', 'C', 10);
	g.AddEdge('D', 'B', 20);
	g.AddEdge('E', 'B', 30);
	g.AddEdge('C', 'E', 40);

	g.Display();
}