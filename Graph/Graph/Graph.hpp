#pragma once

#include<assert.h>
#include <queue>
#include "Heap.hpp"
#include "UnionFindSet.hpp"

//
// 临接矩阵表示无向图&有向图
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
		// 开辟矩阵和边集
		_matrix = new W*[_vertexSize];
		_vertexs = new V[_vertexSize];

		for (int i = 0; i < _vertexSize; ++i)
		{
			// 初始化矩阵
			_matrix[i] = new W[_vertexSize];
			memset(_matrix[i], 0, sizeof(W)*_vertexSize);

			// 初始化边集
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
	W**	 _matrix;		// 临接矩阵
	V*	 _vertexs;		// 顶点集			
	int	 _vertexSize;	// 顶点数
	//int	 _edgeSize;		// 边条数
};

// 无向图
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

// 有向图
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
// 临接表
//

template<class V, class W>
struct LinkEdge
{
	int _srcIndex;			// 源顶点下标
	int _dstIndex;			// 目标顶点下标
	W _weight;				// 权重
	LinkEdge<V, W>* _next;	// 指向下一个节点的指针 

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
	V _vertex;				// 顶点
	LinkEdge<V, W>* _head;	// 指向临接表的边

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

		// 无向图
		_AddEdge(srcIndex, dstIndex, weight);
		_AddEdge(dstIndex, srcIndex, weight);

		// 有向图
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

	LinkEdge<V,W>* _GetFirstEdge(int src)
	{
		return _linkTable[src]._head;
	}

	LinkEdge<V,W>* _GetNextEdge(int src, int next)
	{
		LinkEdge<V,W>* edge = _linkTable[src]._head;
		while (edge)
		{
			if (edge->_dstIndex == next)
			{
				return edge->_next;
			}
			edge = edge->_next;
		}

		return NULL;
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

	void _DFS(int src, bool* visited)
	{
		// 1.访问当前节点
		//cout<<_linkTable[src]._vertex<<" ";
		visited[src] = true;

		// 2.获取当前临接表的第一个顶点
		LinkEdge<V,W>* edge = _GetFirstEdge(src);

		// 3.依次获取临接表后面的顶点进行深度优先遍历
		while (edge)
		{
			if (visited[edge->_dstIndex] == false)
			{
				cout<<_linkTable[edge->_srcIndex]._vertex<<"->"
					<<_linkTable[edge->_dstIndex]._vertex<<" ";

				_DFS(edge->_dstIndex, visited);
			}

			// 4.查找当前顶点的下一个顶点
			edge = _GetNextEdge(src, edge->_dstIndex);
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
		//cout<<_linkTable[cur]._vertex<<" ";
		visited[cur] = true;

		queue<int> q;
		q.push(cur);
		while (!q.empty())
		{
			cur = q.front();
			q.pop();

			LinkEdge<V,W>* edge = _GetFirstEdge(cur);
			while (edge)
			{
				if (visited[edge->_dstIndex] == false)
				{
					//cout<<_linkTable[edge->_dstIndex]._vertex<<" ";
					cout<<_linkTable[edge->_srcIndex]._vertex<<"->"
						<<_linkTable[edge->_dstIndex]._vertex<<" ";

					visited[edge->_dstIndex] = true;
					q.push(edge->_dstIndex);
				}

				edge = _GetNextEdge(cur, edge->_dstIndex);
			}
		}
	}

	bool Kruskal(GraphLink& minSpanTree)
	{
		// 1.初始化最小生成树
		minSpanTree._linkTable = new LinkVertex<V, W>[_vertexSize];
		minSpanTree._vertexSize = _vertexSize;
		for (int i = 0; i < _vertexSize; ++i)
		{
			minSpanTree._linkTable[i]._vertex = _linkTable[i]._vertex;
		}

		// 2.将所有的边放到一个最小堆
		Heap<LinkEdge<V,W>*, CompareLinkEdge<V,W>> minHeap;
		for (int i = 0; i < _vertexSize; ++i)
		{
			LinkEdge<V, W>* begin = _linkTable[i]._head;
			while (begin)
			{
				// 无向图的边需要进行过滤
				if (begin->_srcIndex < begin->_dstIndex)
				{
					minHeap.Insert(begin);
				}

				begin = begin->_next;
			}
		}
		
		// 3.使用并差集和最小堆构建最小生成树
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

	bool Prim(GraphLink& minSpanTree)
	{
		// 1.初始化最小生成树
		minSpanTree._linkTable = new LinkVertex<V, W>[_vertexSize];
		minSpanTree._vertexSize = _vertexSize;
		for (int i = 0; i < _vertexSize; ++i)
		{
			minSpanTree._linkTable[i]._vertex = _linkTable[i]._vertex;
		}

		bool* visitedSet = new bool[_vertexSize];
		memset(visitedSet, false, sizeof(bool)*_vertexSize);

		int src = 0;
		visitedSet[src] = true;
		Heap<LinkEdge<V,W>*, CompareLinkEdge<V,W>> minHeap;

		int count = 1;
		do 
		{
			// 2.取出一个顶点所有未访问过的临接边放到一个最小堆里面
			LinkEdge<V, W>* edge = _GetFirstEdge(src);
			while(edge)
			{
				if (visitedSet[edge->_dstIndex] == false)
				{
					minHeap.Insert(edge);
				}

				edge = _GetNextEdge(src, edge->_dstIndex);
			}

			// 2.选出堆中最小的边加入生成树
			while(!minHeap.Empty() && count < _vertexSize)
			{
				edge = minHeap.GetHeapTop();
				minHeap.Remove();
				if (visitedSet[edge->_dstIndex] == false)
				{
					minSpanTree._AddEdge(edge->_srcIndex, edge->_dstIndex,edge->_weight);
					visitedSet[edge->_dstIndex] = true;
					src = edge->_dstIndex;
					++count;

					break;
				}  
			}
		}while (count < _vertexSize);

		return true;
	}

protected:
	LinkVertex<V, W>* _linkTable;	// 临接表
	int _vertexSize;				// 顶点个数
};

// 无向图
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

	// 生成最小生成树
	GraphLink<char, int> minSpanTree1;
	g.Kruskal(minSpanTree1);

	minSpanTree1.Display();

	// 生成最小生成树
	GraphLink<char, int> minSpanTree2;
	g.Prim(minSpanTree2);
	minSpanTree2.Display();

	g.DFS(0);
	g.BFS(0);
}

// 有向图
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