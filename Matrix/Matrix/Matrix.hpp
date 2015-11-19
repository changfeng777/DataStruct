#pragma once

#include <vector>

// 对称矩阵存储
template<class T>
class SymmetricMatrix
{
public:
	SymmetricMatrix(size_t n)
		:_size(n*(n+1)/2)
	{
		_matrixs = new T[_size];
	}

	~SymmetricMatrix()
	{
		delete[] _matrixs;
	}
private:
	T* _matrixs;
	size_t _size;
};

// 三元组
template<class T>
struct Trituple
{
	int _row;	// 行
	int _col;	// 列
	T	_value; // 数据

	Trituple(int row = 0, int col = 0, const T& value = 0)
		:_row(row)
		,_col(col)
		,_value(value)
	{}
};

//
// 稀疏矩阵
// 定长的静态存储
// 动态存储
//
template<class T>
class SparseMatrix
{
public:
	SparseMatrix(T* ar = 0, int row = 0, int col = 0, const T& invalid = 0)
		:_rowSize(row)
		,_colSize(col)
		,_invalid(invalid)
	{
		for(int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				if (ar[i * col + j] != invalid)
				{
					_matrixs.push_back(Trituple<T>(i, j, ar[i * col + j]));
				}
			}
		}
	}

	~SparseMatrix()
	{}

	void Display()
	{
		size_t index = 0;
		for (int i = 0; i < _rowSize; ++i)
		{
			for (int j = 0; j < _colSize; ++j)
			{
				if (index < _matrixs.size()
					&& _matrixs[index]._row == i && _matrixs[index]._col == j)
				{
					cout<<" "<<_matrixs[index]._value;
					++index;
				}
				else
				{
					cout<<" "<<_invalid;
				}
			}

			cout<<endl;
		}

		cout<<endl;
	}

	// 矩阵转置
	SparseMatrix<T> Transpose()
	{
		SparseMatrix<T> sm;

		sm._rowSize = _colSize;
		sm._colSize = _rowSize;
		sm._invalid = _invalid;

		for (int i = 0; i < _colSize; ++i)
		{
			size_t index = 0;
			while (index < _matrixs.size()) 
			{
				if (_matrixs[index]._col == i)
				{
					sm._matrixs.push_back(Trituple<T>());
					sm._matrixs.back()._row = i;
					sm._matrixs.back()._col = _matrixs[index]._row;
					sm._matrixs.back()._value = _matrixs[index]._value;
				}

				++index;
			}
		}

		return sm;
	}

	// 矩阵转置
	SparseMatrix<T> FastTranspose()
	{
		SparseMatrix<T> sm;

		sm._rowSize = _colSize;
		sm._colSize = _rowSize;
		sm._invalid = _invalid;

		for (size_t i = 0; i < _matrixs.size(); ++i)
		{
			sm._matrixs.push_back(Trituple<T>());
		}

		int* rowCounts = new int[_colSize];
		int* rowStart = new int[_colSize];
		memset(rowCounts, 0, sizeof(int)*_colSize);
		memset(rowStart, 0, sizeof(int)*_colSize);

		// 统计转置后矩阵每一行的数据个数
		for (size_t i = 0; i < _matrixs.size(); ++i)
		{
			rowCounts[_matrixs[i]._col]++;
		}

		// 统计转置后的矩阵每行在压缩矩阵中存储的开始位置
		rowStart[0] = 0;
		for (int i = 1; i < _colSize; ++i)
		{
			rowStart[i] = rowStart[i - 1] + rowCounts[i - 1];
		}

		for (size_t i = 0; i < _matrixs.size(); ++i)
		{
			size_t index = rowStart[_matrixs[i]._col];
			sm._matrixs[index]._col = _matrixs[i]._row;
			sm._matrixs[index]._row = _matrixs[i]._col;
			sm._matrixs[index]._value = _matrixs[i]._value;

			++(rowStart[_matrixs[i]._col]);
		}

		delete[] rowCounts;
		delete[] rowStart;

		return sm;
	}

private:
	vector<Trituple<T> > _matrixs;
	int _rowSize;	// 行
	int _colSize;	// 列
	T _invalid;		// 无效值
};

void Test1()
{
	int array[6][5] = {{1, 0, 3, 0, 5},
					   {0, 0, 0, 0, 0},
	                   {0, 0, 0, 0, 0},
	                   {1, 0, 3, 0, 5},
					   {0, 0, 0, 0, 0},
					   {0, 0, 0, 0, 0}};

	SparseMatrix<int> sm((int*)array, 6, 5, 0);
	sm.Display();

	SparseMatrix<int> ret1 = sm.Transpose();
	ret1.Display();

	SparseMatrix<int> ret2 = sm.FastTranspose();
	ret2.Display();
}