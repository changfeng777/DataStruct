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

	void Union(int root1, int root2)
	{
		_parent[root2] = root1;
	}

	int Find(int x)
	{
		int cur = x;
		while (_parent[cur] != -1)
		{
			cur = _parent[cur];
		}

		return cur;
	}

private:
	int* _parent;
	int _size;
};