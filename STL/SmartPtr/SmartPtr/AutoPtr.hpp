#pragma once

template <class T>
class AutoPtr
{
public:
	AutoPtr(T * ptr = NULL)
		:_ptr(ptr )
	{}

	~ AutoPtr()
	{
		if (_ptr )
		{
			delete _ptr ;
		}
	}

	AutoPtr(AutoPtr<T>& ap)
		: _ptr(ap ._ptr)
	{
		ap._ptr = 0;
	}

	AutoPtr& operator=(AutoPtr<T>& ap)
	{
		if (this != &ap)
		{
			_ptr = ap ._ptr;
			ap._ptr = 0;
		}

		return *this ;
	}

	T* GetPtr()
	{
		return _ptr;
	}

	T& operator * ()
	{
		return *_ptr ;
	}

	T* operator -> ()
	{
		return _ptr ;
	}
private:
	T* _ptr ;
};

void TestAutoPtr()
{
	AutoPtr<int> p1 = new int (10);
	AutoPtr<int> p2 = p1;
	AutoPtr<int> p3;
	p3 = p2 ;

	// AutoPtrµÄÈ±ÏÝ
	//*p1 = 4;
}