/***********************************************************************************
xxx.h:
    Copyright (c) Bit Software, Inc.(2013), All rights reserved.

Purpose: ģ��ʵ��boost/shared_ptrʵ��SharedPtr
��Ҫ��ѧϰshared_ptr��Դ�룬ȥ��shared_ptr��ï��֦Ҷ�������ڲ�ʵ�֡�
˼����ΪʲôҪ��ôʵ�֣�������������ָ�����⣬����C++�������ƵĹ���
ps:������Ӧ�ð���weak_ptr��Ƕ����ƣ���������ѵ�ǰ�ⲿ��������ˣ���ȥ��weak_ptr
���ֵ�����Ѿ����������⡣

Author: xujinghang

Reviser: xxx

Created Time: 2015-4-26
************************************************************************************/

#pragma once
#define __SMART_PTR_DEBUG__

namespace SECOND
{
	// ���ü����������Ϊ������
	class SPCountedBase
	{
	public :
		SPCountedBase(long count = 1)
			: _count(count)
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

#ifdef __SMART_PTR_DEBUG__
			printf("���ͷ����ü�������:0x%p\n", this);
#endif
		}

		virtual void Dispose()
		{
			if(_px )
			{
#ifdef __SMART_PTR_DEBUG__
				printf("��delete����:0x%p\n", _px);
#endif
				delete _px ;
			}
		}

	private :
		// ������������Ϊ˽�з�����
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
		SPCountedImpl_PD(T * ptr, D d)
			: _px(ptr )
			, _d(d )
		{}

		// ��дɾ���ͷŶ�����ͷ����ü���������麯��
		virtual void Destory()
		{
			delete this;

#ifdef __SMART_PTR_DEBUG__
			printf("���ͷ����ü�������:0x%p\n", this);
#endif
		}

		virtual void Dispose()
		{
			if(_px )
			{
	#ifdef __SMART_PTR_DEBUG__
				printf("������ɾ����ɾ������deleter:0x%p\n", _px);
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
	public:
		SPCountedImpl_PDA(T * ptr, D d, A a )
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
			_a.deallocate ((int*)this, sizeof(SPCountedImpl_PDA)/4);

#ifdef __SMART_PTR_DEBUG__
			printf("���ռ��������ͷ����ü�������:0x%p\n", this);
#endif
		}

		virtual void Dispose()
		{
			if(_px )
			{
	#ifdef __SMART_PTR_DEBUG__
				printf("������ɾ����ɾ������:0x%p\n", _px);
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
		template<class P>
		SharedCount(P* px)
		{
			pi_ = new SPCountedImpl_P<P>(px);
#ifdef __SMART_PTR_DEBUG__
			printf("��new���ü�������:0x%p\n", pi_);
#endif
		}
		
		//
		// �����D dΪ���õ�ɾ��������
		// �������ָ�������new�����ʱ������Ҫ�ö��õ�ɾ����
		// ��: malloc/free -- fopen/fclose��
		//
		template<class P, class D >
		SharedCount(P * ptr, D d )
		{
			pi_ = new SPCountedImpl_PD <P, D>(ptr , d);
#ifdef __SMART_PTR_DEBUG__
			printf("��new���ü�������:0x%p\n", pi_);
#endif
		}

		//
		// <1>:�����D dΪ���õ�ɾ��������ͬ��
		// <2>:�����A aΪ���õ��ڴ����������
		// ��ֹ����ʹ��ָ��ָ��ĳ����£�����������ü������������ڴ���Ƭ����
		//
		template<class P, class D , class A>
		SharedCount(P* px, D d , A a)
		{
			pi_ = (SPCountedBase*)a.allocate(sizeof(SPCountedImpl_PDA<P,D,A>)/4);
			new(pi_)SPCountedImpl_PDA<P,D,A>(px, d, a);
#ifdef __SMART_PTR_DEBUG__
			printf("���ռ��������������ü������󣬲�ʹ��new��λ���ʽ��ʼ����:0x%p\n", pi_);
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
		explicit SharedPtr(T * px = NULL)
			: _pn(px)
			, _px(px)
		{
	// __SMART_PTR_DEBUG__�����ڵ���ʱ�۲��Ƿ��ʼ�����ͷŶ���
	#ifdef __SMART_PTR_DEBUG__
			printf("����������ָ��������ָ�롿:0x%p\n", _px);
	#endif
		}

		template<class D>
		SharedPtr(T* px, D d)
			: _pn(px, d)
			, _px(px)
		{
			// __SMART_PTR_DEBUG__�����ڵ���ʱ�۲��Ƿ��ʼ�����ͷŶ���
#ifdef __SMART_PTR_DEBUG__
			printf("����������ָ��������ָ�롿:0x%p\n", _px);
#endif
		}

		template<class D, class A>
		SharedPtr(T* px, D d, A a)
			: _pn(px, d, a)
			, _px(px)
		{
			// __SMART_PTR_DEBUG__�����ڵ���ʱ�۲��Ƿ��ʼ�����ͷŶ���
#ifdef __SMART_PTR_DEBUG__
			printf("����������ָ��������ָ�롿:0x%p\n", _px);
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
			return *_px;
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

	class FClose
	{
	public :
		void operator() (void* ptr)
		{
			fclose((FILE *)ptr);
		}
	};

	// ���õ�ɾ�����º���
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
		// ����ɾ����
		SharedPtr<FILE> p1(fopen("test.txt" , "w"), FClose());

		// ����ɾ�����ͷ�����
		SharedPtr<int> p2((int*)malloc(sizeof (int)), Free(), allocator<int>());
	}
}