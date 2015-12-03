namespace SECOND
{
	class SPCountedBase
	{
	public :
		SPCountedBase(long count = 1)
			: _count(count )
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
		}

		virtual void Dispose()
		{
			if(_px )
			{
	#ifdef __SMART_PTR_DEBUG__
				cout<<"delete:" <<_px<< endl;
	#endif
				delete _px ;
			}
		}

	private :
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
		SPCountedImpl_PD(T * ptr, const D & d)
			: _px(ptr )
			, _d(d )
		{}

		// 重写删除释放对象和释放引用计数对象的虚函数
		virtual void Destory()
		{
			delete this ;
		}

		virtual void Dispose()
		{
			if(_px )
			{
	#ifdef __SMART_PTR_DEBUG__
				cout<<"delete:" <<_px<< endl;
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
		SPCountedImpl_PDA(T * ptr, const D & d, const A& a )
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
			_a.deallocate (this, 1);
		}

		virtual void Dispose()
		{
			if(_px )
			{
	#ifdef __SMART_PTR_DEBUG__
				cout<<"delete:" <<_px<< endl;
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
		template<class T>
		SharedCount(T * ptr)
		{
			pi_ = new SPCountedImpl_P< T>(ptr);
		}
		
		//
		// 这里的D d为定置的删除器对象
		// 当管理的指针对象不是new分配的时，则需要用定置的删除器
		// 如: malloc/free 、 fopen/fclose等
		//
		template<class T, class D >
		SharedCount(T * ptr, D& d )
		{
			pi_ = new SPCountedImpl_PD <T, D>(ptr , d);
		}

		//
		// <1>:这里的D d为定置的删除器对象，同上
		// <2>:这里的A a为定置的内存分配器对象。
		// 防止大量使用指针指针的场景下，分配大量引用计数对象引发内存碎片问题
		//
		template<class T, class D , class A>
		SharedCount(T * ptr, D& d , A& a)
		{
			pi_ = a.allocate(1);
			new(pi_)SPCountedImpl_PD<T,D,A>(ptr, d, a);
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
		explicit SharedPtr(T * ptr = NULL)
			: _pn(ptr )
			, _px(ptr )
		{
	// __SMART_PTR_DEBUG__宏用于调试时观察是否初始化和释放对象。
	#ifdef __SMART_PTR_DEBUG__
			if (_px )
			{
				cout<<"new:" <<_px<< endl;
			}
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
			return *_px ;
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
}