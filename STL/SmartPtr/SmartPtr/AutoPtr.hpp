#pragma once

// 简单实现自动释放智能指针
// ps：分析以后可以发现AutoPtr拷贝对象时有非常大的缺陷，拷贝后会留下空智能指针对象的隐患

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

	// AutoPtr的缺陷
	//*p1 = 4;
}