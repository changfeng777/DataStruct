#pragma once

class UnionFindSet
{
public:
	UnionFindSet(int size)
		:_size(size)
	{
		_parent = new int[_size];
		//memset(_parent, -1, sizeof(int)*_size);
		for (int i = 0; i < _size; ++i)
		{
			_parent[i] = -1;
		}
	}

	~UnionFindSet()
	{
		delete[] _parent;
	}

	// 将集合root2合并到集合root1中
	void Union(int root1, int root2)
	{
		assert(_parent[root1] < 0);
		assert(_parent[root2]< 0);

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

// C语言方式解决

// 将集合2合并到集合1中
void UnionSet(int* unionSet, int root1, int root2)
{
	unionSet[root1] += unionSet[root2];
	unionSet[root2] = root1;
}

int FindRoot(int* unionSet, int x)
{
	int cur = x;
	while (unionSet[cur] >= 0)
	{
		cur = unionSet[cur];
	}

	return cur;
}

//
// 小米的2016的面试题==具体描述参见课件
//
int Friends(int n, int m, int r[][2])
{
	assert(r);

	// 初始创建一个并查集
	const int N = n+1;
	int* unionSet = new int[N];
	memset(unionSet, -1, N*sizeof(int));

	for (int i = 0; i < m; ++i)
	{
		int first = r[i][0];
		int second = r[i][1];

		int parent1 = FindRoot(unionSet, first);
		int parent2 = FindRoot(unionSet, second);

		if (parent1 != parent2)
		{
			UnionSet(unionSet, parent1, parent2);
		}
	}

	int count = 0;
	for (int i = 1; i < N; ++i)
	{
		if (unionSet[i] < 0)
		{
			++count;
		}
	}

	delete[] unionSet;

	return count;
}

void TestFriends()
{
	int r[5][2] = {{1,2},{2,3},{4,5},{1,3},{2,4}};
	cout<<"N个朋友圈?"<<Friends(5, 5, r)<<endl;
}