#pragma once

#include <assert.h>
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
	GraphMatrix(const V* vertexs, int size, bool isDirected)
		:_vertexSize(size)
		,_isDirected(isDirected)
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
	W**	 _matrix;		// �ٽӾ���
	V*	 _vertexs;		// ���㼯			
	int	 _vertexSize;		// ������
	//int	 _edgeSize;		// ������

	bool _isDirected;
};

// ����ͼ
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

// ����ͼ
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
	vector<V> _vertexs;						// ���㼯��
	vector<LinkEdge<V,W>*> _linkTables;		// �ٽӱ�
	bool _isDirected;						// �Ƿ�������ͼ
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

		// ����ͼ
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

	// ��ȡ�ٽӱ������һ����
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
				// 1.���ʵ�ǰ�ڵ�
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
		// 2.��ȡ��ǰ�ٽӱ�ĵ�һ������
		LinkEdge<V,W>* edge = _linkTables[src];

		// 3.���λ�ȡ�ٽӱ����Ķ������������ȱ���
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
		// 1.��ʼ����С������
		minSpanTree._vertexs = _vertexs;
		minSpanTree._linkTables.resize(_vertexs.size());
		minSpanTree._isDirected = _isDirected;

		//
		// 2.�����еı߷ŵ�һ����С��
		// ������V�����㣬E����
		// 
		Heap<LinkEdge<V,W>*, CompareLinkEdge<V,W>> minHeap;
		for (int i = 0; i < _vertexs.size(); ++i)
		{
			LinkEdge<V, W>* begin = _linkTables[i];
			while (begin)
			{
				// ����ͼ�ı���Ҫ���й���
				if (begin->_srcIndex < begin->_dstIndex)
				{
					minHeap.Push(begin);
				}

				begin = begin->_next;
			}
		}
		
		// 3.ʹ�ò������С�ѹ�����С������
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
		// 1.��ʼ����С������
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
			// 2.ȡ��һ����������δ���ʹ����ٽӱ߷ŵ�һ����С������
			LinkEdge<V, W>* edge = _linkTables[src];
			while(edge)
			{
				if (visitedSet[edge->_dstIndex] == false)
				{
					minHeap.Push(edge);
				}

				edge = _GetNextEdge(src, edge->_dstIndex);
			}

			// 2.ѡ��������С�ı߼���������
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

	// �Ǹ���Դ���·��--Dijkstra(�Ͽ�˹��)
	// ��src��������������·��
	void _Dijkstra(int src, W* dist, int* path, bool* vSet, int size, const W& maxValue)
	{
		//
		// 1.dist��ʼ��src����������ĵľ���
		// 2.path��ʼ��src�����������·��
		// 3.��ʼ�����㼯��
		//
		for (int i = 0; i < size; ++i)
		{
			dist[i] = _GetWeight(src, i, maxValue);
			path[i] = src;
			vSet[i] = false;
		}

		// ��src���뼯��
		vSet[src] = true;

		int count = size;
		while(count--)
		{
			//
			// ѡ����src�������ӵı�����С�ı�
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
				// ����src->k�ľ���
				// ���dist(src,min)+dist(min, k)��ȨֵС��dist(src, k)
				// �����dist(src,k)��path(src->min->k)
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
		// 1.dist��ʼ��src����������ĵľ���
		// 2.path��ʼ��src�����������·��
		// 3.��ʼ�����㼯��
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

		// ��src���뼯��
		vSet[src] = true;

		int count = size;
		while(count--)
		{
			//
			// ѡ����src�������ӵı�����С�ı�
			// src->min

			if (minHeap.Empty())
				continue;

			int minIndex = minHeap.Top().second;
			minHeap.Pop();

			vSet[minIndex] = true;
			for (int k = 0; k < size; ++k)
			{
				// 
				// ���dist(src->min)+dist(min, k)��ȨֵС��dist(src, k)
				// �����dist(src,k)��path(src->min->k)
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

				//cout<<"���㣺"<<_linkTable[src]._vertex\
				<<"->���㣺"<<_linkTable[i]._vertex<<"��·��Ϊ��";
				cout<<src<<","<<i<<"��·��Ϊ:";
				while(count)
				{
					//cout<<_linkTable[ vSet[--count] ]._vertex<<"->";
					cout<<vPath[--count]<<"->";
				}

				cout<<"·������Ϊ��"<<dist[i]<<endl;
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

		// ��ӡ���·��
		PrintPath(src, dist, path, _vertexs.size());

		delete[] dist;
		delete[] path;
		delete[] vSet;
	}
};

// ����ͼ
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

	// ������С������
	GraphLink<char, int> minSpanTree1(false);
	g.Kruskal(minSpanTree1);

	minSpanTree1.Display();

	// ������С������
	GraphLink<char, int> minSpanTree2(false);
	g.Prim(minSpanTree2);
	minSpanTree2.Display();

	g.DFS();
	g.BFS();
}

// ����ͼ
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