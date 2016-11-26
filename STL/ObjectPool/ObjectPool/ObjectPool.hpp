#pragma once

#include <vector>
#include <string>
#include <Windows.h>

struct AllocateMemory
{
	static inline void* Allocate(size_t size)
	{
		return ::operator new(size);
	}

	static inline void Deallocate(void* ptr, size_t size)
	{
		::operator delete(ptr);
	}
};

template<class T>
class ObjectPool
{
protected:
	struct BlockNode
	{
		void* _memory;		// �ڴ��ָ��
		size_t _blockCount;	// �ڴ�������
		BlockNode* _next;	// ָ����һ���ڴ���ָ��

		BlockNode(size_t blockCount)
			:_blockCount(blockCount)
			,_next(NULL)
		{
			_memory = AllocateMemory::Allocate(blockCount*_itemSize);
		}

		~BlockNode()
		{
			AllocateMemory::Deallocate(_memory, _blockCount*_itemSize);
		}
	};
	
	BlockNode* _firstNode;	// ָ���һ����ڵ�
	BlockNode* _lastNode;	// ָ�����һ����ڵ�
	static size_t _itemSize; // һ���ڴ��Ĵ�С
	size_t _countInNode;	// �ڵ���ʹ���ڴ�ļ��� 
	size_t _maxBlockCount;	// ���Ŀ�Ĵ�С

	T* _lastDeleted;		// ָ�������ɾ����һ������ 

	static size_t _initItemSize()
	{
		if (sizeof(T) >= sizeof(void*))
			return sizeof(T);
		else
			return sizeof(void*);
	}
  
	void _AllocateNewNode()
	{
		size_t count = _lastNode->_blockCount;
		count *= 2;
		if (count > _maxBlockCount)
			count = _maxBlockCount;

		BlockNode* newNode = new BlockNode(count);
		_lastNode->_next = newNode;
		_lastNode = newNode;

		_countInNode = 0;
	}

public:
	ObjectPool(size_t initCount = 32, size_t maxBlockCount = 1000000)
		:_countInNode(0)
		,_maxBlockCount(maxBlockCount)
		,_lastDeleted(NULL)
	{
		if (maxBlockCount < initCount)
			throw std::invalid_argument("maxBlockCount must greater than initCount!");

		_firstNode = _lastNode = new BlockNode(initCount);
	}

	~ObjectPool()
	{
		BlockNode* cur = _firstNode;
		while (cur)
		{
			BlockNode* del = cur;
			cur = cur->_next;
			delete del;
		}

		_firstNode = _lastNode = NULL;
		_lastDeleted = NULL;
		_countInNode = 0;
	}

	T* New()
	{
		// �����ظ�ʹ������ͷŻ����Ķ���
		if (_lastDeleted)
		{
			T* object = _lastDeleted;
			// ע���ͷŵ�ʱ��ǰ���󱣴������һ���ͷŶ���ĵ�ַ
			_lastDeleted = *((T**)_lastDeleted);
			return new(object)T();
		}

		// ���Ľڵ���û�ж�����Կɹ������ˣ�������µĿ�ڵ�
		if (_countInNode >= _lastNode->_blockCount)
			_AllocateNewNode();

		// �����һ���ڵ���ȡ��һ�����󷵻�
		char* object = (char*)_lastNode->_memory;
		object += _countInNode*_itemSize;
		++_countInNode;

		return new(object) T();
	}
	
	void Delete(T* object)
	{
		object->~T();

		// ����һ���ͷŶ���ĵ�ַ�ŵ���ǰ����Ŀ�ʼλ��
		*(T**)object = _lastDeleted;
		_lastDeleted = object;
	}
};

template<class T>
size_t ObjectPool<T>::_itemSize = ObjectPool<T>::_initItemSize();

// �����ڴ����صĳ���ʹ�ú��ڴ������ظ�ʹ��
void TestObjectPool()
{
	vector<string*> v;

	ObjectPool<string> pool;
	for (size_t i = 0; i < 32; ++i)
	{
		v.push_back(pool.New());
		printf("Pool New [%d]: %p\n", i, v.back());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}

	for (size_t i = 0; i < 32; ++i)
	{
		v.push_back(pool.New());
		printf("Pool New [%d]: %p\n", i, v.back());
	}

	v.push_back(pool.New());
}

// ��Ե�ǰ���ڴ����ؽ��м򵥵����ܲ���
void TestObjectPoolOP()
{
	size_t begin , end;
	vector<string*> v;
	const size_t N = 1000000;
	v.reserve(N);

	cout<<"pool new/delete==============================="<<endl;
	// ���������ͷ�5��
	begin = GetTickCount();
	ObjectPool<string> pool;
	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(pool.New());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(pool.New());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(pool.New());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(pool.New());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(pool.New());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}


	end = GetTickCount();
	cout<<"Pool:"<<end - begin<<endl;

	cout<<"new/delete==============================="<<endl;
	begin = GetTickCount();

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(new string);
	}

	while (!v.empty())
	{
		delete v.back();
		v.pop_back();
	}

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(new string);
	}

	while (!v.empty())
	{
		delete v.back();
		v.pop_back();
	}

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(new string);
	}

	while (!v.empty())
	{
		delete v.back();
		v.pop_back();
	}

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(new string);
	}

	while (!v.empty())
	{
		delete v.back();
		v.pop_back();
	}

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(new string);
	}

	while (!v.empty())
	{
		delete v.back();
		v.pop_back();
	}

	end = GetTickCount();
	cout<<"new/delete:"<<end - begin<<endl;
}