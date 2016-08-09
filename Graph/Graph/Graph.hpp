#pragma once

#include <assert.h>
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
	GraphMatrix(const V* vertexs, int size, bool isDirected)
		:_vertexSize(size)
		,_isDirected(isDirected)
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

		if (_isDirected)
		{
			_matrix[srcIndex][dstIndex] = weight;
		}
		else
		{
			_matrix[srcIndex][dstIndex] = weight;
			_matrix[dstIndex][srcIndex] = weight;
		}
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
	int	 _vertexSize;		// 顶点数
	//int	 _edgeSize;		// 边条数

	bool _isDirected;
};

// 无向图
void Test1()
{
	GraphMatrix<char, int> g("ABCDE", 5, false);
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
	GraphMatrix<char, int> g("ABCDE", 5, true);
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
protected:
	vector<V> _vertexs;						// 顶点集合
	vector<LinkEdge<V,W>*> _linkTables;		// 临接表
	bool _isDirected;						// 是否是有向图
public:
	GraphLink(bool isDirected = false)
		:_isDirected(isDirected)
	{}

	GraphLink(const V* ar, int size, bool isDirected = false)
		:_isDirected(isDirected)
	{
		_vertexs.resize(size);
		_linkTables.resize(size);
		for (size_t i = 0; i < size; ++i)
		{
			_vertexs[i] = ar[i];
		}
	}

public:
	int GetVertexIndex(const V& vertex)
	{
		for (int i = 0; i < _vertexs.size(); ++i)
		{
			if(_vertexs[i] == vertex)
				return i;
		}

		return -1;
	}

	void _AddEdge(int srcIndex, int dstIndex, const W& weight)
	{
		LinkEdge<V, W>* tmp = new LinkEdge<V, W>(srcIndex, dstIndex, weight);

		tmp->_next = _linkTables[srcIndex];
		_linkTables[srcIndex] = tmp;
	}

	void AddEdge(const V& src, const V& dst, const W& weight)
	{
		int srcIndex = GetVertexIndex(src);
		int dstIndex = GetVertexIndex(dst);

		assert(srcIndex != -1);
		assert(dstIndex != -1);

		// 无向图
		if(_isDirected)
		{
			_AddEdge(srcIndex, dstIndex, weight);
		}
		else
		{
			_AddEdge(srcIndex, dstIndex, weight);
			_AddEdge(dstIndex, srcIndex, weight);
		}
	}

	void Display()
	{
		for (int i = 0; i < _vertexs.size(); ++i)
		{
			cout<<_vertexs[i]<<"["<<i<<"]->";
			LinkEdge<V, W>* begin = _linkTables[0];
			while (begin)
			{
				cout<<begin->_weight<<"["<<begin->_dstIndex<<"]""->";
				begin = begin->_next;
			}

			cout<<"NULL"<<endl;
		}

		cout<<endl;
	}

	// 获取临接表里的下一条边
	LinkEdge<V,W>* _GetNextEdge(int src, int cur)
	{
		LinkEdge<V,W>* edge = _linkTables[src];
		while (edge)
		{
			if (edge->_dstIndex == cur)
			{
				return edge->_next;
			}
			edge = edge->_next;
		}

		return NULL;
	}

	void DFS()
	{
		cout<<"DFS:";

		bool* visited = new bool[_vertexs.size()];
		memset(visited, false, sizeof(bool)*_vertexs.size());

		for (size_t i = 0; i < _vertexs.size(); ++i)
		{
			if (visited[i] == false)
			{
				// 1.访问当前节点
				cout<<_vertexs[i]<<" ";
				visited[i] = true;

				_DFS(i, visited);
			}
		}

		delete[] visited;

		cout<<endl;
	}

	void _DFS(int src, bool* visited)
	{
		// 2.获取当前临接表的第一个顶点
		LinkEdge<V,W>* edge = _linkTables[src];

		// 3.依次获取临接表后面的顶点进行深度优先遍历
		while (edge)
		{
			if (visited[edge->_dstIndex] == false)
			{
				cout<<_vertexs[edge->_dstIndex]<<" ";
				visited[edge->_dstIndex] = true;

				_DFS(edge->_dstIndex, visited);
			}

			edge = edge->_next;
		}
	}

	void BFS()
	{
		cout<<"BFS:";
		bool* visited = new bool[_vertexs.size()];
		memset(visited, false, sizeof(bool)*_vertexs.size());

		for (size_t i = 0; i < _vertexs.size(); ++i)
		{
			if (visited[i] == false)
			{
				_BFS(i, visited);
			}
		}

		delete[] visited;

		cout<<endl;
	}
	
	void _BFS(int cur, bool* visited)
	{
		cout<<_vertexs[cur]<<" ";
		visited[cur] = true;

		queue<int> q;
		q.push(cur);
		while (!q.empty())
		{
			cur = q.front();
			q.pop();

			LinkEdge<V,W>* edge = _linkTables[cur];
			while (edge)
			{
				if (visited[edge->_dstIndex] == false)
				{
					cout<<_vertexs[edge->_dstIndex]<<" ";

					visited[edge->_dstIndex] = true;
					q.push(edge->_dstIndex);
				}

				edge = edge->_next;
			}
		}
	}

	bool Kruskal(GraphLink& minSpanTree)
	{
		// 1.初始化最小生成树
		minSpanTree._vertexs = _vertexs;
		minSpanTree._linkTables.resize(_vertexs.size());
		minSpanTree._isDirected = _isDirected;

		//
		// 2.将所有的边放到一个最小堆
		// 假设有V个顶点，E条边
		// 
		Heap<LinkEdge<V,W>*, CompareLinkEdge<V,W>> minHeap;
		for (int i = 0; i < _vertexs.size(); ++i)
		{
			LinkEdge<V, W>* begin = _linkTables[i];
			while (begin)
			{
				// 无向图的边需要进行过滤
				if (begin->_srcIndex < begin->_dstIndex)
				{
					minHeap.Push(begin);
				}

				begin = begin->_next;
			}
		}
		
		// 3.使用并差集和最小堆构建最小生成树
		UnionFindSet UFSet(_vertexs.size());
		int count = _vertexs.size();
		while (--count)
		{
			if (minHeap.Empty())
			{
				return false;
			}

			LinkEdge<V,W>* edge = minHeap.Top();
			minHeap.Pop();
			int src = UFSet.FindRoot(edge->_srcIndex);
			int dst = UFSet.FindRoot(edge->_dstIndex);

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
		minSpanTree._vertexs = _vertexs;
		minSpanTree._linkTables.resize(_vertexs.size());
		minSpanTree._isDirected = _isDirected;

		bool* visitedSet = new bool[_vertexs.size()];
		memset(visitedSet, false, sizeof(bool)*_vertexs.size());

		int src = 0;
		visitedSet[src] = true;
		Heap<LinkEdge<V,W>*, CompareLinkEdge<V,W>> minHeap;

		int count = 1;
		do 
		{
			// 2.取出一个顶点所有未访问过的临接边放到一个最小堆里面
			LinkEdge<V, W>* edge = _linkTables[src];
			while(edge)
			{
				if (visitedSet[edge->_dstIndex] == false)
				{
					minHeap.Push(edge);
				}

				edge = _GetNextEdge(src, edge->_dstIndex);
			}

			// 2.选出堆中最小的边加入生成树
			while(!minHeap.Empty() && count < _vertexs.size())
			{
				edge = minHeap.Top();
				minHeap.Pop();
				if (visitedSet[edge->_dstIndex] == false)
				{
					minSpanTree._AddEdge(edge->_srcIndex, edge->_dstIndex,edge->_weight);
					visitedSet[edge->_dstIndex] = true;
					src = edge->_dstIndex;
					++count;

					break;
				}  
			}
		}while (count < _vertexs.size());

		return true;
	}

	W _GetWeight(int src, int dst, const W& maxValue)
	{
		if (src == dst)
			return maxValue;

		LinkEdge<V,W>* edge = _linkTables[src];
		while (edge)
		{
			if (edge->_dstIndex == dst)
			{
				return edge->_weight;
			}

			edge = edge->_next;
		}

		return maxValue;
	}

	// 非负单源最短路径--Dijkstra(迪科斯彻)
	// 求src到其他顶点的最短路径
	void _Dijkstra(int src, W* dist, int* path, bool* vSet, int size, const W& maxValue)
	{
		//
		// 1.dist初始化src到其他顶点的的距离
		// 2.path初始化src到其他顶点的路径
		// 3.初始化顶点集合
		//
		for (int i = 0; i < size; ++i)
		{
			dist[i] = _GetWeight(src, i, maxValue);
			path[i] = src;
			vSet[i] = false;
		}

		// 将src加入集合
		vSet[src] = true;

		int count = size;
		while(count--)
		{
			//
			// 选出与src顶点连接的边中最小的边
			// src->min
			W min = maxValue;
			int minIndex = src;
			for (int j = 0; j < size; ++j)
			{
				if (vSet[j] == false && dist[j] < min)
				{
					minIndex = j;
					min = dist[j];
				}
			}

			vSet[minIndex] = true;
			for (int k = 0; k < size; ++k)
			{
				if(k == src)
					continue;

				//  
				// 更新src->k的距离
				// 如果dist(src,min)+dist(min, k)的权值小于dist(src, k)
				// 则更新dist(src,k)和path(src->min->k)
				//
				W w = _GetWeight(minIndex, k, maxValue);
				if (vSet[k] == false && dist[minIndex] + w < dist[k])
				{
					dist[k] = dist[minIndex] + w;
					path[k] = minIndex;
				}
			}
		}
	}

	void _Dijkstra_OP(int src, W* dist, int* path,
		bool* vSet, int size, const W& maxValue)
	{
		//
		// 1.dist初始化src到其他顶点的的距离
		// 2.path初始化src到其他顶点的路径
		// 3.初始化顶点集合
		//
		for (int i = 0; i < size; ++i)
		{
			dist[i] = _GetWeight(src, i, maxValue);
			path[i] = src;
			vSet[i] = false;
		}

		struct Compare
		{
			bool operator()(const pair<W, int>& lhs, const pair<W, int>& rhs)
			{
				return lhs.first < rhs.first;
			}
		};

		Heap<pair<W, int>, Compare> minHeap;
		for (int i = 0; i < size; ++i)
		{
			if (dist[i] < maxValue)
			{
				minHeap.Push(make_pair(dist[i], i));
			}
		}

		// 将src加入集合
		vSet[src] = true;

		int count = size;
		while(count--)
		{
			//
			// 选出与src顶点连接的边中最小的边
			// src->min

			if (minHeap.Empty())
				continue;

			int minIndex = minHeap.Top().second;
			minHeap.Pop();

			vSet[minIndex] = true;
			for (int k = 0; k < size; ++k)
			{
				// 
				// 如果dist(src->min)+dist(min, k)的权值小于dist(src, k)
				// 则更新dist(src,k)和path(src->min->k)
				//
				W w = _GetWeight(minIndex, k, maxValue);
				if (vSet[k] == false && dist[minIndex] + w < dist[k])
				{
					dist[k] = dist[minIndex] + w;
					path[k] = minIndex;

					minHeap.Push(make_pair(dist[k], k));
				}
			}
		}
	}

	void PrintPath(int src, W* dist, int* path, int size)
	{
		int* vPath = new int[size];
		for (int i = 0; i < size; ++i)
		{
			if (i != src)
			{
				int index = i, count = 0;
				do{
					vPath[count++] = index;
					index = path[index];
				}while (index != src);

				vPath[count++] = src;

				//cout<<"顶点："<<_linkTable[src]._vertex\
				<<"->顶点："<<_linkTable[i]._vertex<<"的路径为：";
				cout<<src<<","<<i<<"的路径为:";
				while(count)
				{
					//cout<<_linkTable[ vSet[--count] ]._vertex<<"->";
					cout<<vPath[--count]<<"->";
				}

				cout<<"路径长度为："<<dist[i]<<endl;
			}
		}
	}

	void Dijkstra(int src, const W& maxValue)
	{
		W* dist = new W[_vertexs.size()];
		int* path = new int[_vertexs.size()];
		bool* vSet = new bool[_vertexs.size()];

		//_Dijkstra(src, dist, path, vSet, _vertexs.size(), maxValue);
		_Dijkstra_OP(src, dist, path, vSet, _vertexs.size(), maxValue);

		// 打印最短路径
		PrintPath(src, dist, path, _vertexs.size());

		delete[] dist;
		delete[] path;
		delete[] vSet;
	}
};

// 无向图
void Test3()
{
	GraphLink<char, int> g("ABCDE", 5, false);
	g.AddEdge('A', 'D', 10);
	g.AddEdge('A', 'E', 20);
	g.AddEdge('B', 'C', 10);
	g.AddEdge('B', 'D', 20);
	g.AddEdge('B', 'E', 30);
	g.AddEdge('C', 'E', 40);
	g.Display();

	// 生成最小生成树
	GraphLink<char, int> minSpanTree1(false);
	g.Kruskal(minSpanTree1);

	minSpanTree1.Display();

	// 生成最小生成树
	GraphLink<char, int> minSpanTree2(false);
	g.Prim(minSpanTree2);
	minSpanTree2.Display();

	g.DFS();
	g.BFS();
}

// 有向图
void Test4()
{
	GraphLink<char, int> g("ABCDE", 5, true);
	g.AddEdge('A', 'D', 10);
	g.AddEdge('E', 'A', 20);
	g.AddEdge('B', 'C', 10);
	g.AddEdge('D', 'B', 20);
	g.AddEdge('E', 'B', 30);
	g.AddEdge('C', 'E', 40);

	g.AddEdge('A', 'C', 50);
	g.AddEdge('A', 'E', 50);

	g.Display();

	g.Dijkstra(0, 10000);
	//g.Dijkstra(1, 10000);
}