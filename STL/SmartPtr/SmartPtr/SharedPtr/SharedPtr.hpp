/***********************************************************************************
xxx.h:
    Copyright (c) Bit Software, Inc.(2013), All rights reserved.

Purpose: 模拟实现boost/shared_ptr实现SharedPtr
主要用学习shared_ptr的源码，去除shared_ptr繁茂的枝叶，理清内部实现。
思考它为什么要这么实现？提升对象智能指针的理解，提升C++和软件设计的功力
ps:本来还应该包含weak_ptr的嵌套设计，不过如果把当前这部分理清楚了，再去看weak_ptr
部分的设计已经不再有问题。

Author: xujinghang

Reviser: xxx

Created Time: 2015-4-26
************************************************************************************/

#pragma once
#define __SMART_PTR_DEBUG__

namespace SECOND
{
	// 引用计数基类设计为抽象类
	class SPCountedBase
	{
	public :
		SPCountedBase(long count = 1)
			: _count(count)
		{}

		virtual ~SPCountedBase ()
		{}

		// 思考这里为什么要设计这两个虚函数接口Destory/Dispose?

		// 设计的删除引用计数对象的纯虚函数接口，留给派生类重写
		virtual void Destory() =  0;

		// 设计的释放管理对象的纯虚函数接口，留给派生类重写
		virtual void Dispose() = 0;

		// 增加引用计数
		void Add_Ref ()
		{
			//对应不同的环境，考虑加锁的问题
			++ _count;
		}

		// 减引用计数，最后一个管理对象时释放对象
		void Release ()
		{
			// 支持多线程环境需加锁
			if(--_count == 0)
			{
				Dispose();
			}
		}

		long GetCount ()
		{
			return _count ;
		}

	private :
		SPCountedBase(const SPCountedBase&);
		SPCountedBase& operator = (const SPCountedBase &);

	private :
		long _count;
	};

	template <class T>
	class SPCountedImpl_P : public SPCountedBase
	{
	public :
		SPCountedImpl_P(T * ptr)
			: _px(ptr )
		{}

		virtual ~SPCountedImpl_P ()
		{}

		// 重写删除释放对象和释放引用计数对象的虚函数
		virtual void Destory()
		{
			delete this;

#ifdef __SMART_PTR_DEBUG__
			printf("【释放引用计数对象】:0x%p\n", this);
#endif
		}

		virtual void Dispose()
		{
			if(_px )
			{
#ifdef __SMART_PTR_DEBUG__
				printf("【delete对象】:0x%p\n", _px);
#endif
				delete _px ;
			}
		}

	private :
		// 拷贝函数声明为私有防拷贝
		SPCountedImpl_P(const SPCountedImpl_P&);
		SPCountedImpl_P& operator =(const SPCountedImpl_P &);

	private :
		T* _px ;
	};

	// 定置管理对象删除
	template <class T, class D>
	class SPCountedImpl_PD : public SPCountedBase
	{
	public :
		SPCountedImpl_PD(T * ptr, D d)
			: _px(ptr )
			, _d(d )
		{}

		// 重写删除释放对象和释放引用计数对象的虚函数
		virtual void Destory()
		{
			delete this;

#ifdef __SMART_PTR_DEBUG__
			printf("【释放引用计数对象】:0x%p\n", this);
#endif
		}

		virtual void Dispose()
		{
			if(_px )
			{
	#ifdef __SMART_PTR_DEBUG__
				printf("【定置删除器删除对象】deleter:0x%p\n", _px);
	#endif
				// 使用定置的删除器进行删除
				_d(_px );
			}
		}
	private :
		T* _px ;
		D _d ;
	};

	// 定置引用计数对象的分配器
	template <class T, class D, class A >
	class SPCountedImpl_PDA : public SPCountedBase
	{
	public:
		SPCountedImpl_PDA(T * ptr, D d, A a )
			: _px(ptr )
			, _d(d )
			, _a(a )
		{}

		// 重写删除释放对象和释放引用计数对象的虚函数
		void Destory ()
		{
			//
			// 手动去调用析构函数，并使用定置的内存配置器释放内存
			// 思考这里为什么手动调用析构函数?而在前面只需要调用delete？
			//
			this->~SPCountedImpl_PDA <T, D,A >();
			_a.deallocate ((int*)this, sizeof(SPCountedImpl_PDA)/4);

#ifdef __SMART_PTR_DEBUG__
			printf("【空间配置器释放引用计数对象】:0x%p\n", this);
#endif
		}

		virtual void Dispose()
		{
			if(_px )
			{
	#ifdef __SMART_PTR_DEBUG__
				printf("【定置删除器删除对象】:0x%p\n", _px);
	#endif
				// 使用定置的删除进行删除
				_d(_px );
			}
		}

	private :
		T* _px ;
		D _d ;
		A _a ;
	};

	class SharedCount
	{
	public :
		template<class P>
		SharedCount(P* px)
		{
			pi_ = new SPCountedImpl_P<P>(px);
#ifdef __SMART_PTR_DEBUG__
			printf("【new引用计数对象】:0x%p\n", pi_);
#endif
		}
		
		//
		// 这里的D d为定置的删除器对象
		// 当管理的指针对象不是new分配的时，则需要用定置的删除器
		// 如: malloc/free -- fopen/fclose等
		//
		template<class P, class D >
		SharedCount(P * ptr, D d )
		{
			pi_ = new SPCountedImpl_PD <P, D>(ptr , d);
#ifdef __SMART_PTR_DEBUG__
			printf("【new引用计数对象】:0x%p\n", pi_);
#endif
		}

		//
		// <1>:这里的D d为定置的删除器对象，同上
		// <2>:这里的A a为定置的内存分配器对象。
		// 防止大量使用指针指针的场景下，分配大量引用计数对象引发内存碎片问题
		//
		template<class P, class D , class A>
		SharedCount(P* px, D d , A a)
		{
			pi_ = (SPCountedBase*)a.allocate(sizeof(SPCountedImpl_PDA<P,D,A>)/4);
			new(pi_)SPCountedImpl_PDA<P,D,A>(px, d, a);
#ifdef __SMART_PTR_DEBUG__
			printf("【空间配置器分配引用计数对象，并使用new定位表达式初始化】:0x%p\n", pi_);
#endif
		}

		~ SharedCount()
		{
			pi_->Release ();

			if (pi_ ->GetCount() == 0)
			{
				//delete pi_;
				pi_->Destory ();
			}
		}

		SharedCount(const SharedCount& sc)
			: pi_(sc .pi_)
		{
			// 拷贝构造添加引用计数
			pi_->Add_Ref ();
		}

		SharedCount& operator = (const SharedCount& sc)
		{
			if (this != & sc)
			{
				// 释放原对象的引用计数，增加新对象的引用计数
				pi_->Release ();
				pi_ = sc .pi_;
				pi_->Add_Ref ();
			}

			return *this ;
		}

		long GetCount ()
		{
			return pi_->GetCount();
		}

	private :
		SPCountedBase* pi_;
	};

	template <class T>
	class SharedPtr
	{
	public :
		explicit SharedPtr(T * px = NULL)
			: _pn(px)
			, _px(px)
		{
	// __SMART_PTR_DEBUG__宏用于调试时观察是否初始化和释放对象。
	#ifdef __SMART_PTR_DEBUG__
			printf("【构造智能指针对象管理指针】:0x%p\n", _px);
	#endif
		}

		template<class D>
		SharedPtr(T* px, D d)
			: _pn(px, d)
			, _px(px)
		{
			// __SMART_PTR_DEBUG__宏用于调试时观察是否初始化和释放对象。
#ifdef __SMART_PTR_DEBUG__
			printf("【构造智能指针对象管理指针】:0x%p\n", _px);
#endif
		}

		template<class D, class A>
		SharedPtr(T* px, D d, A a)
			: _pn(px, d, a)
			, _px(px)
		{
			// __SMART_PTR_DEBUG__宏用于调试时观察是否初始化和释放对象。
#ifdef __SMART_PTR_DEBUG__
			printf("【构造智能指针对象管理指针】:0x%p\n", _px);
#endif
		}

		~ SharedPtr()
		{}

		SharedPtr(const SharedPtr<T>& sp)
			: _px(sp._px)
			, _pn(sp._pn)
		{}

		SharedPtr& operator=(const SharedPtr<T>& sp)
		{
			//
			// 此处boost中使用swap的现代写法完成
			// 我们的主要目的是学习boost的源码实现
			// 这里就简化为直接调用SharedCount的operator=
			// SharedCount中来处理对象引用计数到减到0后释放对象的问题
			//
			if (this != &sp)
			{
				_px = sp._px;
				_pn = sp._pn;
			}
			return *this ;
		}

		T* GetPtr()
		{
			return _px ;
		}

		int GetCount()
		{
			return _pn.GetCount();
		}

		T& operator* ()
		{
			return *_px;
		}

		T* operator->()
		{
			return _px ;
		}

	private :
		T* _px;				// 智能管理的指针对象px
		SharedCount _pn;	// 共享引用计数对象
	};

	void TestSharedPtr()
	{
		SharedPtr<int> p1(new int (1));
		cout<<"p1->count:" <<p1. GetCount()<<endl ;

		SharedPtr<int> p2 = p1;
		cout<<"p1->count:" <<p1. GetCount()<<" " ;
		cout<<"p2->count:" <<p2. GetCount()<<endl ;

		SharedPtr<int> p3;
		p3 = p2 ;
		cout<<"p1->count:" <<p1. GetCount()<<" ";
		cout<<"p2->count:" <<p2. GetCount()<<" ";
		cout<<"p3->count:" <<p3. GetCount()<<endl;
	}

	class FClose
	{
	public :
		void operator() (void* ptr)
		{
			fclose((FILE *)ptr);
		}
	};

	// 定置的删除器仿函数
	class Free
	{
	public :
		void operator() (void* ptr)
		{
			free(ptr );
		}
	};


	void TestSharedPtr_DA()
	{
		// 定制删除器
		SharedPtr<FILE> p1(fopen("test.txt" , "w"), FClose());

		// 定制删除器和分配器
		SharedPtr<int> p2((int*)malloc(sizeof (int)), Free(), allocator<int>());
	}
}