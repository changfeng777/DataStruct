#pragma once
#include <vector>
#include <string>

namespace BUCKET
{
	template<class K, class V>
	struct HashTableNode
	{
		K _key;
		V _value;
		HashTableNode<K, V>* _next;
		
		HashTableNode(const K& key, const V& value)
			:_key(key)
			,_value(value)
			,_next(NULL)
		{}
	};

	// 使用素数表对齐做哈希表的容量，降低哈希冲突
	const int _PrimeSize = 28;
	static const unsigned long _PrimeList[_PrimeSize] =
	{
		53ul,         97ul,         193ul,       389ul,       769ul,
		1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
		49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
		1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
		50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul, 
		1610612741ul, 3221225473ul, 4294967291ul
	};

	template<class K>
	struct __HashFunc
	{
		size_t operator()(const K& t)
		{
			return t;
		}
	};

	//
	// 特化string类型，方便后续测试字典
	// 若需支持其他类型，也一样可使用特化的方式
	//
	template<>
	struct __HashFunc<string>
	{
		static size_t BKDRHash(const char *str)
		{
			unsigned int seed = 131; // 31 131 1313 13131 131313
			unsigned int hash = 0;

			while (*str)
			{
				hash = hash * seed + (*str++);
			}

			return (hash & 0x7FFFFFFF);
		}

		size_t operator()(const string& s)
		{
			return BKDRHash(s.c_str());
		}
	};

	//template<class K, class V, class HashFunc, class EqualKey>
	//template<class K, class V, class HashFunc>
	template<class K, class V, template<class> class HashFunc = __HashFunc>
	class HashTable
	{
	public:
		typedef HashTableNode<K, V> Node;

		HashTable()
			:_size(0)
		{}

		~HashTable()
		{}

		HashTable(const HashTable& ht);
		HashTable& operator=(const HashTable& ht);

	public:
		//InsertUnique
		//InsertEquel
		bool Insert(const K& key, const V& value)
		{
			_CheckCapacity(_size + 1);

			// 1.查找key是否存在，存在则直接返回
			size_t index = _HashFunc(key, _tables.size());
			Node* begin = _tables[index];
			while (begin)
			{
				if (begin->_key == key)
				{
					return false;
				}
				begin = begin->_next;
			}

			// 2.头插
			Node* head = _tables[index];
			Node* tmp = new Node(key, value);
			tmp->_next = head;
			_tables[index] = tmp;

			++_size;

			return true;
		}
		
		HashTableNode<K, V>* Find(const K& key)
		{
			size_t index = _HashFunc(key, _tables.size());
			Node* begin = _tables[index];
			while (begin)
			{
				if (begin->_key == key)
				{
					return begin;
				}

				begin = begin->_next;
			}

			return NULL;
		}
		
		bool Remove(const K& key)
		{
			size_t index = _HashFunc(key, _tables.size());

			// 1.begin为桶的头结点
			Node* begin = _tables[index];
			if (begin == NULL)
				return false;

			if (begin->_key == key)
			{
				_tables[index] = begin->_next;
				delete begin;
				return true;
			}

			// 2.key在桶的中间节点
			Node* prev = begin;
			begin = begin->_next;
			while (begin)
			{
				if (begin->_key == key)
				{
					prev->_next = begin->_next;
					delete begin;
					return true;
				}
				prev = prev;
				begin = begin->_next;
			}

			return false;
		}

		void Print()
		{
			cout<<"HashTable"<<endl;
			printf("Capacity:%d, Size:%d\n", _tables.size(), _size);
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				Node* begin = _tables[i];
				if (begin == NULL)
				{
					continue;
				}

				printf("【%d】", i);

				while(begin)
				{
					//printf("{%d,%.2f}->", begin->_key, begin->_value);
					cout<<"{"<<begin->_key<<","<<begin->_value<<"}->";
					begin = begin->_next;
				}

				cout<<"NULL"<<endl;
			}
		}

		size_t Size()
		{
			return _size;
		}
		
		size_t Capacity()
		{
			return _tables.size();
		}

	protected:

		unsigned long _GetPrimeNum(unsigned long num)
		{
			size_t pos = 0;
			while (pos < _PrimeSize)
			{
				if (_PrimeList[pos] > num)
					break;

				++pos;
			}

			return _PrimeList[pos];
		}

		void _CheckCapacity(size_t size)
		{
			if (size < _tables.size())
				return;

			// 如果size大于table的大小，则进行重建，重新负载节点
			size_t capacity = _GetPrimeNum(size);
			vector<Node*> tmpHashTable;
			tmpHashTable.reserve(capacity);
			tmpHashTable.assign(capacity, 0);
		
			// 将旧表中的节点依次进行重新计算负载到新表中
			for(size_t i = 0; i < _tables.size(); ++i)
			{
				Node* begin = _tables[i];
				while (begin)
				{
					// 1.将这个节点摘下来
					Node* tmp = begin;
					begin = begin->_next;

					// 2.重新计算在新表中的位置
					size_t index = _HashFunc(tmp->_key, capacity);

					// 3.将摘下来的tmp节点进行头插
					Node* head = tmpHashTable[index];
					tmp->_next = head;
					tmpHashTable[index] = tmp;
				}
			}

			_tables.swap(tmpHashTable);
		}

		size_t _HashFunc(const K& key, size_t capacity)
		{
			//
			// 计算key Hash值仿函数对象，让程序的扩展性更强
			//
			//return _hash(key) % capacity;
			return HashFunc<K>()(key) % capacity;
		}

	protected:
		vector<Node*> _tables;
		size_t _size;

		//HashFunc _hash;		// 计算hash值的仿函数对象
		//EqualKey _equal;		// 计算key值相等的仿函数
	};

	// 插入/查找/删除
	void TestSome()
	{
		HashTable<int, double> ht1;
		ht1.Insert(1,1);
		ht1.Insert(1,1);
		ht1.Insert(2,1);
		ht1.Insert(3,1);
		ht1.Insert(4,1);
		ht1.Insert(5,1);
		ht1.Insert(6,1);
		ht1.Insert(7,1);
		ht1.Insert(8,1);
		ht1.Insert(9,1);

		ht1.Insert(53,1);
		ht1.Insert(54,1);
		ht1.Insert(55,1);
		ht1.Insert(56,1);

		ht1.Print();

		HashTable<int, double>::Node* ret = ht1.Find(2);
		cout<<"Find 2 ?: "<<ret<<endl;

		ret = ht1.Find(30);
		cout<<"Find 30 ?: "<<ret<<endl;

		ht1.Remove(2);
		ht1.Remove(3);

		ht1.Print();
		
		// 测试字典
		HashTable<string, string> dict;
		dict.Insert("tree", "树");
		dict.Insert("flower", "花");
		dict.Print();
	}

	// 测试哈希表扩张重建
	void TestRebuilt()
	{
		HashTable<int, double> ht1;
		ht1.Insert(53,53);
		ht1.Insert(54,54);

		for (size_t i = 0; i < 50; ++i)
		{
			ht1.Insert(i, i);
		}

		ht1.Print();

		ht1.Insert(63,63);
		ht1.Insert(64,64);
		ht1.Insert(65,65);

		ht1.Insert(97,97);
		ht1.Insert(98,98);
		ht1.Insert(99,99);

		ht1.Print();
	}

	#include <time.h>

	// 随机数据测试哈希表的负载
	void TestOp()
	{
		HashTable<int, double> ht1;
		srand(time(0));

		for(size_t i = 0; i < 2000; ++i)
		{
			size_t key = rand();
			ht1.Insert(key, key);
		}

		ht1.Print();
	}
}