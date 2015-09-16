#pragma once

class UnionFindSet
{
public:
	UnionFindSet(int size)
		:_size(size)
	{
		_parent = new int[_size];
		memset(_parent, -1, sizeof(int)*_size);
	}

	~UnionFindSet()
	{
		delete[] _parent;
	}

	// 合并两个集合
	void Union(int root1, int root2)
	{
		_parent[root1] += _parent[root2];
		_parent[root2] = root1;
	}

	// 查找x的根节点
	int Find(int x)
	{
		int cur = x;
		while (_parent[cur] >= 0)
		{
			cur = _parent[cur];
		}

		return cur;
	}

	void Print()
	{
		for (int i = 0; i < _size; ++i)
		{
			cout<<_parent[i]<<" ";
		}
		cout<<endl;
	}

private:
	int* _parent;
	int _size;
};

void TestUnionFindSet()
{
	UnionFindSet s(10);
	s.Union(0, 6);
	s.Union(0, 7);
	s.Union(0, 8);

	s.Union(1, 4);
	s.Union(1, 9);

	s.Union(2, 3);
	s.Union(2, 5);

	s.Print();
}