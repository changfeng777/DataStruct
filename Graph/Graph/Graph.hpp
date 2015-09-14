#pragma once

#include<assert.h>

// �ٽӾ����ʾ����ͼ&����ͼ
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


template<class V, class W>
struct LinkEdge
{
	int _index;				// �����±�
	W _weight;				// Ȩ��
	LinkEdge<V, W>* _next;	// ָ����һ���ڵ��ָ�� 

	LinkEdge(int index = -1, const W& weight = W())
		:_index(index)
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
		LinkEdge<V, W>* tmp = new LinkEdge<V, W>(dstIndex, weight);

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
				cout<<begin->_weight<<"["<<begin->_index<<"]""->";
				begin = begin->_next;
			}

			cout<<"NULL"<<endl;
		}

		cout<<endl;
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