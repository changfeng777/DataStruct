#pragma once

//
// 简单模拟最初版的shared_ptr的设计，这里不考虑线程安全和循环引用等问题。
//

namespace ONE
{
	template <class T>
	class SharedPtr
	{
	public :
		SharedPtr(T* ptr = NULL)
			: _ptr(ptr )
			, _countPtr(new int(1))
		{}     

		~ SharedPtr()
		{
			_Release();
		}

		SharedPtr(const SharedPtr<T>& ap)
			: _ptr(ap ._ptr)
			, _countPtr(ap ._countPtr)
		{
			++ _countPtr[0];
		}

		SharedPtr& operator =(const SharedPtr<T>& ap )
		{
			if (this != &ap)
			{
				this->_Release ();

				_ptr = ap ._ptr;
				_countPtr = ap ._countPtr;

				++ _countPtr[0];
			}

			return *this ;
		}

		T* GetPtr ()
		{
			return _ptr ;
		}

		int GetCount ()
		{
			return *_countPtr ;
		}

		T& operator * ()
		{
			return *_ptr ;
		}

		T* operator -> ()
		{
			return _ptr ;
		}

	protected :
		void _Release ()
		{
			if (--_countPtr [0] == 0)
			{
				delete _countPtr ;

				if (_ptr )
				{
					delete _ptr ;
				}
			}
		}

	private :
		T* _ptr ;
		int* _countPtr ;
	};

	void TestSharedPtr ()
	{
		SharedPtr<int > p1 = new int (1);
		cout<<"p1->count:" <<p1. GetCount()<<endl ;

		SharedPtr<int > p2 = p1;
		cout<<"p1->count:" <<p1. GetCount()<<" " ;
		cout<<"p2->count:" <<p2. GetCount()<<endl ;

		SharedPtr<int > p3;
		p3 = p2 ;
		cout<<"p1->count:" <<p1. GetCount()<<" " ;
		cout<<"p2->count:" <<p2. GetCount()<<" " ;
		cout<<"p3->count:" <<p3. GetCount()<<endl ;
	}


	template <class T>
	class SharedArray
	{
	public :
		SharedArray(T * ptr = NULL)
			: _ptr(ptr )
			, _countPtr(new int(1))
		{}

		~ SharedArray()
		{
			_Release();
		}

		SharedArray(const SharedArray<T>& ap)
			: _ptr(ap ._ptr)
			, _countPtr(ap ._countPtr)
		{
			++ _countPtr[0];
		}

		SharedArray& operator =(const SharedArray<T>& ap)
		{
			if (this != &ap)
			{
				this->_Release ();

				_ptr = ap ._ptr;
				_countPtr = ap ._countPtr;

				++ _countPtr[0];
			}

			return *this ;
		}

		T* Get()
		{
			return _ptr ;
		}

		int GetCount ()
		{
			return *_countPtr ;
		}

		T& operator [](size_t index)
		{
			return _ptr [index];
		}

	protected :
		void _Release ()
		{
			if (--_countPtr [0] == 0)
			{
				delete _countPtr ;

				if (_ptr )
				{
					delete[] _ptr ;
				}
			}
		}

	private :
		T* _ptr ;
		int* _countPtr ;
	};

	void TestSharedArray()
	{
		SharedArray<int > p1 = new int [20];
		cout<<"p1->count:" <<p1.GetCount()<<endl ;

		SharedArray<int > p2 = p1;
		cout<<"p1->count:" <<p1.GetCount()<<" " ;
		cout<<"p2->count:" <<p2.GetCount()<<endl ;

		SharedArray<int > p3;
		p3 = p2 ;
		cout<<"p1->count:" <<p1.GetCount()<<" " ;
		cout<<"p2->count:" <<p2.GetCount()<<" " ;
		cout<<"p3->count:" <<p3.GetCount()<<endl ;

		p1[1] = 1;
		p3[2] = 2;

		cout<<p1 [1]<<" "<< p1[2]<<endl ;
	}
}
