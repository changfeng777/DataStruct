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

		// ˼������ΪʲôҪ����������麯���ӿ�Destory/Dispose?

		// ��Ƶ�ɾ�����ü�������Ĵ��麯���ӿڣ�������������д
		virtual void Destory() =  0;

		// ��Ƶ��ͷŹ������Ĵ��麯���ӿڣ�������������д
		virtual void Dispose() = 0;

		// �������ü���
		void Add_Ref ()
		{
			//��Ӧ��ͬ�Ļ��������Ǽ���������
			++ _count;
		}

		// �����ü��������һ���������ʱ�ͷŶ���
		void Release ()
		{
			// ֧�ֶ��̻߳��������
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

		// ��дɾ���ͷŶ�����ͷ����ü���������麯��
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

	// ���ù������ɾ��
	template <class T, class D>
	class SPCountedImpl_PD : public SPCountedBase
	{
	public :
		SPCountedImpl_PD(T * ptr, const D & d)
			: _px(ptr )
			, _d(d )
		{}

		// ��дɾ���ͷŶ�����ͷ����ü���������麯��
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
				// ʹ�ö��õ�ɾ��������ɾ��
				_d(_px );
			}
		}
	private :
		T* _px ;
		D _d ;
	};

	// �������ü�������ķ�����
	template <class T, class D, class A >
	class SPCountedImpl_PDA : public SPCountedBase
	{
		SPCountedImpl_PDA(T * ptr, const D & d, const A& a )
			: _px(ptr )
			, _d(d )
			, _a(a )
		{}

		// ��дɾ���ͷŶ�����ͷ����ü���������麯��
		void Destory ()
		{
			//
			// �ֶ�ȥ����������������ʹ�ö��õ��ڴ��������ͷ��ڴ�
			// ˼������Ϊʲô�ֶ�������������?����ǰ��ֻ��Ҫ����delete��
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
				// ʹ�ö��õ�ɾ������ɾ��
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
		// �����D dΪ���õ�ɾ��������
		// �������ָ�������new�����ʱ������Ҫ�ö��õ�ɾ����
		// ��: malloc/free �� fopen/fclose��
		//
		template<class T, class D >
		SharedCount(T * ptr, D& d )
		{
			pi_ = new SPCountedImpl_PD <T, D>(ptr , d);
		}

		//
		// <1>:�����D dΪ���õ�ɾ��������ͬ��
		// <2>:�����A aΪ���õ��ڴ����������
		// ��ֹ����ʹ��ָ��ָ��ĳ����£�����������ü������������ڴ���Ƭ����
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
			// ��������������ü���
			pi_->Add_Ref ();
		}

		SharedCount& operator = (const SharedCount& sc)
		{
			if (this != & sc)
			{
				// �ͷ�ԭ��������ü����������¶�������ü���
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
	// __SMART_PTR_DEBUG__�����ڵ���ʱ�۲��Ƿ��ʼ�����ͷŶ���
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
			// �˴�boost��ʹ��swap���ִ�д�����
			// ���ǵ���ҪĿ����ѧϰboost��Դ��ʵ��
			// ����ͼ�Ϊֱ�ӵ���SharedCount��operator=
			// SharedCount��������������ü���������0���ͷŶ��������
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
		T* _px;				// ���ܹ����ָ�����px
		SharedCount _pn;	// �������ü�������
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