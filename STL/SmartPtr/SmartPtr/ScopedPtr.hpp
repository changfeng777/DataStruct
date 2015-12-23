#pragma once

// ºÚµ• µœ÷∑¿øΩ±¥∞Êµƒ÷«ƒ‹÷∏’Î

template <class T>
class ScopedPtr
{
public :
	ScopedPtr(T * ptr = NULL)
		: _ptr(ptr )
	{}

	~ ScopedPtr()
	{
		if (_ptr )
		{
			delete _ptr ;
		}
	}

	T* GetPtr()
	{
		return _ptr ;
	}

	T& operator * ()
	{
		return *_ptr ;
	}

	T* operator -> ()
	{
		return _ptr ;
	}

private :
	ScopedPtr(const ScopedPtr<T> & ap);
	ScopedPtr& operator=(const ScopedPtr<T>& ap);

private :
	T* _ptr ;
};

void TestScopedPtr ()
{
	// ∑¿øΩ±¥
	ScopedPtr<int > p1 = new int (10);
	//ScopedPtr<int> p2 = p1;
	//ScopedPtr<int> p3;
	//p3 = p2;
}

template <class T>
class ScopedArray
{
public :
	ScopedArray(T * ptr = NULL)
		: _ptr(ptr )
	{}

	~ ScopedArray()
	{
		if (_ptr )
		{
			delete _ptr ;
		}
	}

	T* GetPtr()
	{
		return _ptr ;
	}

	T& operator[](size_t index)
	{
		return _ptr[index];
	}

private :
	ScopedArray(const ScopedArray<T> & ap);
	ScopedArray& operator=(const ScopedArray<T>& ap);

private :
	T* _ptr;
};

void TestScopedArray ()
{
	// ∑¿øΩ±¥
	ScopedArray<int> p1 = new int[10];
	//ScopedArray<int> p2 = p1;
	//ScopedArray<int> p3;
	//p3 = p2;

	p1[0] = 0;
	p1[1] = 1;
}