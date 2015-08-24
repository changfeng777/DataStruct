#include<assert.h>

template<class T>
class SeqList
{
public:
	SeqList ()
		:_data(0)
		,_size(0)
		,_capacity(0)
		,_storeSize(3)
	{}

	SeqList (const SeqList& v)
		:_size(v._size)
		,_capacity(v._capacity)
		,_storeSize(v._storeSize)
	{
		_data = new T[_capacity];
		memcpy(_data, v._data, sizeof(_size)*_size);
	}

	//SeqList& operator=(const SeqList& v)
	//{
	//	if (&v != this)
	//	{
	//	/*	_Destory();
	//		_size = v._size;
	//		_capacity = v._capacity;
	//		_data = new T[_capacity];
	//		memcpy(_data, v._data, sizeof(_size)*_size);*/

	//		SeqList tmp(v);
	//		std::swap(_data, tmp._data);
	//		std::swap(_capacity, tmp._capacity);
	//		std::swap(_size, tmp._size);
	//	}

	//	return *this;
	//}

	void Swap(SeqList& tmp)
	{
		std::swap(_data, tmp._data);
		std::swap(_capacity, tmp._capacity);
		std::swap(_size, tmp._size);
	}

	SeqList& operator=(SeqList s)
	{
		Swap(s);
		return *this;
	}

	virtual ~SeqList ()
	{
		_Destory();
	}

protected:
	 inline void _CheckExpand()
	 {
		 if (_size < _capacity)
			 return;

		 _capacity = _capacity * 2 + _storeSize;
		 T* tmp = new T[_capacity];
		
		 if (_data)
		 {
			 memcpy(tmp, _data, sizeof(T)*_size);
			 delete [] _data;
		 }

		 _data = tmp;
	 }

	 void _Destory()
	 {
		 if(_data)
		 {
			 delete[] _data;
		 }

		 _capacity = 0;
		 _size = 0;
	 }

public:
	void PushBack (const T& x)
	{
		_CheckExpand();
		_data[_size++] = x;
	}

	void PopBack()
	{
		if (_size > 0)
			--_size;
	}

	// 在position位置上插入一个数据
	void Insert (size_t position, const T& x)
	{
		assert (position <= _size);

		_CheckExpand();

		size_t last = _size;
		while (position < last)
		{
			_data[last] = _data[last - 1];
			--last;
		}

		_data[position] = x;
		++_size;
	}

	void Earse (size_t position)
	{
		assert(position < _size);

		// 注意这里的边界条件
		size_t begin = position;
		while (begin < _size - 1)
		{
			_data[begin] = _data[begin + 1];
			++begin;
		}

		--_size;
	}

	T& operator[](size_t position)
	{
		assert (position < _size);

		return _data[position];
	}

	void Clear ()
	{
		_size = 0;
	}

	size_t GetSize ()
	{
		return _size;
	}

	void Print()
	{
		for (size_t i = 0; i < _size; ++i)
		{
			cout<<_data[i]<<" ";
		}

		cout<<endl;
	}

private:
	T*			_data;			// 数据块指针
	size_t		_size;			// 数据的个数
	size_t		_capacity;		// 容量
	const int	_storeSize;		// 存储大小（初始化的容量值） 
};