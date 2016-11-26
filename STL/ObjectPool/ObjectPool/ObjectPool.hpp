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
		void* _memory;		// 内存块指针
		size_t _blockCount;	// 内存对象计数
		BlockNode* _next;	// 指向下一个内存块的指针

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
	
	BlockNode* _firstNode;	// 指向第一个块节点
	BlockNode* _lastNode;	// 指向最后一个块节点
	static size_t _itemSize; // 一个内存块的大小
	size_t _countInNode;	// 节点中使用内存的计数 
	size_t _maxBlockCount;	// 最大的块的大小

	T* _lastDeleted;		// 指向最近被删除的一个对象 

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
		// 优先重复使用最近释放回来的对象
		if (_lastDeleted)
		{
			T* object = _lastDeleted;
			// 注意释放的时候当前对象保存的是上一个释放对象的地址
			_lastDeleted = *((T**)_lastDeleted);
			return new(object)T();
		}

		// 最后的节点中没有对象可以可供分配了，则分配新的块节点
		if (_countInNode >= _lastNode->_blockCount)
			_AllocateNewNode();

		// 在最后一个节点中取出一个对象返回
		char* object = (char*)_lastNode->_memory;
		object += _countInNode*_itemSize;
		++_countInNode;

		return new(object) T();
	}
	
	void Delete(T* object)
	{
		object->~T();

		// 将上一个释放对象的地址放到当前对象的开始位置
		*(T**)object = _lastDeleted;
		_lastDeleted = object;
	}
};

template<class T>
size_t ObjectPool<T>::_itemSize = ObjectPool<T>::_initItemSize();

// 测试内存对象池的常规使用和内存对象的重复使用
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

// 针对当前的内存对象池进行简单的性能测试
void TestObjectPoolOP()
{
	size_t begin , end;
	vector<string*> v;
	const size_t N = 1000000;
	v.reserve(N);

	cout<<"pool new/delete==============================="<<endl;
	// 反复申请释放5次
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