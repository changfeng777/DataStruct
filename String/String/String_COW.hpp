#include <Windows.h>

namespace COW1
{
	class String
	{
	public:
		String(const char* str)
			: _str(new char [ strlen(str )+1])
		{
			strcpy(_str , str);
			_refCount = new int(1);
		}

		String(const String& str)
			: _refCount(str._refCount)
			, _str(str._str)
		{
			// �������ü���
			++ _refCount[0];
		}

		String& operator =(const String& str )
		{
			if (this != &str)
			{
				// --�ɵ����ü�������������һ�����ö������ͷŶ���
				_Release();

				// ��Ա������ֵ�����������ü���
				_str = str ._str;
				_refCount = str ._refCount;
				++ _refCount[0];
			}

			return *this ;
		}

		char& operator[](size_t index)
		{
			// Copy On Write
			if (*_refCount > 1)
			{
				_Release();

				char* tmpPtr = new char[strlen(_str) + 1];
				int* tmpCount = new int(1);
				strcpy(tmpPtr, _str);

				_str = tmpPtr;
				_refCount = tmpCount;
			}

			return _str[index];
		}

		size_t GetSize ()
		{
			return strlen (_str);
		}

		char* GetStr ()
		{
			return _str ;
		}

		void _Release()
		{
			// --�ɵ����ü�������������һ�����ö������ͷŶ���
			if (--_refCount [0] == 0)
			{
				delete[] _str ;
				delete [] _refCount;
			}
		}

		~ String()
		{
			_Release();
		}
	private:
		char* _str ;
		int* _refCount ;     // ���ü���
	};
}

namespace COW2
{
	class String
	{
	public:
		String(const char* str)
			:_str(new char[strlen(str) + 5])
		{
			// ��ʼ�����ü���
			_str += 4;
			GetRefCount(_str) = 1;

			strcpy(_str, str);
		}

		String(const String& str)
			:_str(str._str)
		{
			// �������ü���
			++GetRefCount(_str);
		}

		String& operator=(const String& str)
		{
			if (this != &str)
			{
				Release(_str);

				_str = str._str;

				++GetRefCount(_str);
			}
			return *this;
		}

		char& operator[](size_t index)
		{
			// Copy On Write
			if (GetRefCount(_str) > 1)
			{
				// �����ü���
				--GetRefCount(_str);

				char* tmpPtr = new char[strlen(_str) + 5];
				tmpPtr += 4;
				GetRefCount(tmpPtr) = 1;
				strcpy(tmpPtr, _str);

				_str = tmpPtr;
			}

			return _str[index];
		}

		~String()
		{
			Release(_str);
		}

		size_t GetSize()
		{
			return strlen(_str);
		}

		char* GetStr()
		{
			return _str;
		}

	protected:
		// ��ȡ���ü�����ע�����ﷵ�����ã���ע�⴫���ָ����������㣩
		inline int& GetRefCount(char* str)
		{
			return *(int*)(str-4);
		}

		// ���ü�����1���������һ�����ö������ͷŶ���
		inline void Release(char* str)
		{
			if ((--GetRefCount(str)) == 0)
			{
				delete[] (str-4);
			}
		}

	private:
		char* _str;
	};
}

void TestString_COW1 ()
{
	COW1::String s1("hello world!");
	COW1::String s2 = s1;

	cout<<"s1:"<<s1.GetStr()<<endl;
	cout<<"s2:"<<s2.GetStr()<<endl<<endl;

	s1[0] = 'x';

	cout<<"s1:"<<s1.GetStr()<<endl;
	cout<<"s2:"<<s2.GetStr()<<endl<<endl;

	COW1::String s3("");
	s3 = s1;
	cout<<"s3:"<<s3.GetStr()<<endl<<endl;
}

// ����COW1Ч��
void TestString_COW2 ()
{
	COW1::String s1 = "hello world";

	int begin = GetTickCount();

	for (int i = 0; i < 10000; ++i)
	{
		COW1::String s2 = s1;

		// do something
		// cout<<s2.GetStr()<<endl;
	}

	int end = GetTickCount();

	cout<<"cost time:"<<end - begin<<endl;
}

// ����ʲôʱ��дʱ����
void TestString_COW3()
{
	COW1::String s1("hello world!");
	COW1::String s2 = s1;

	cout<<"s1:"<<(int*)s1.GetStr()<<endl;
	cout<<"s2:"<<(int*)s2.GetStr()<<endl;
	s2[0] = 'x';
	cout<<"s1:"<<(int*)s1.GetStr()<<endl;
	cout<<"s2:"<<(int*)s2.GetStr()<<endl;
};