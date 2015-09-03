#include<assert.h>

template<class T>
class SeqList
{
public:
	SeqList ()
		:_data(0)
		,_size(0)
		,_capacity(0)
	{
		_CheckExpand(7);
	}

	SeqList (const SeqList& v)
		:_size(v._size)
		,_capacity(v._capacity)
	{
		_data = new T[_capacity];

		// �˴���Ҫ������ȡ����д������Զ������ͽ������εĿ���
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
	//
	//		// �˴���Ҫ������ȡ����д������Զ������ͽ������εĿ���
	//		memcpy(_data, v._data, sizeof(_size)*_size);
	//	}
	//	*/
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
	 inline void _CheckExpand(size_t size)
	 {
		 if (_size < _capacity)
			 return;

		 _capacity = size;
		 T* tmp = new T[_capacity];
		 if (_data)
		 {
			 // �˴��������ȡ�Ժ��ٴ���
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
	// size > capacity ʱ����˳�����������ӵ�size
	void Reserve(size_t size)
	{
		_CheckExpand(size);
	}

	void PushBack (const T& x)
	{
		if (_capacity ==_size)
		{
			_CheckExpand(2*_capacity);
		}

		_data[_size++] = x;
	}

	void PopBack()
	{
		if (_size > 0)
			--_size;
	}

	// ��posλ���ϲ���һ������
	void Insert (size_t pos, const T& x)
	{
		assert (pos <= _size);

		if (_capacity ==_size)
		{
			_CheckExpand(2*_capacity);
		}

		size_t last = _size;
		while (pos < last)
		{
			_data[last] = _data[last - 1];
			--last;
		}

		_data[pos] = x;
		++_size;
	}

	void Earse (size_t pos)
	{
		assert(pos < _size);

		// ע������ı߽�����
		size_t begin = pos;
		while (begin < _size - 1)
		{
			_data[begin] = _data[begin + 1];
			++begin;
		}

		--_size;
	}

	T& operator[](size_t pos)
	{
		assert (pos < _size);

		return _data[pos];
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
	T*			_data;			// ���ݿ�ָ��
	size_t		_size;			// ���ݵĸ���
	size_t		_capacity;		// ����
};