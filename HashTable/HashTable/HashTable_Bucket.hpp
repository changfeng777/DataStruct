//#pragma once
//#include <vector>
//#include <string>
//
//#include "Common.h"
//
//namespace BUCKET
//{
//	template<class K, class V>
//	struct HashTableNode
//	{
//		K _key;
//		V _value;
//		HashTableNode<K, V>* _next;
//		
//		HashTableNode(const K& key, const V& value)
//			:_key(key)
//			,_value(value)
//			,_next(NULL)
//		{}
//	};
//
//	template<class K>
//	struct __HashFunc
//	{
//		size_t operator()(const K& t)
//		{
//			return t;
//		}
//	};
//
//	//
//	// 特化string类型，方便后续测试字典
//	// 若需支持其他类型，也一样可使用特化的方式
//	//
//	template<>
//	struct __HashFunc<string>
//	{
//		size_t operator()(const string& s)
//		{
//			return BKDRHash(s.c_str());
//		}
//	};
//
//	//template<class K, class V, class HashFunc, class EqualKey>
//	//template<class K, class V, class HashFunc>
//	template<class K, class V, template<class> class HashFunc = __HashFunc>
//	class HashTable
//	{
//	public:
//		typedef HashTableNode<K, V> Node;
//
//		HashTable()
//			:_size(0)
//		{}
//
//		~HashTable()
//		{
//			Clear();
//		}
//
//		HashTable(const HashTable& ht)
//		{
//			_Copy(ht);
//		}
//
//		HashTable& operator=(const HashTable& ht)
//		{
//			if (this != &ht)
//			{
//				Clear();
//				_Copy(ht);
//			}
//
//			return *this;
//		}
//
//	public:
//		void _Copy(const HashTable& ht)
//		{
//			_tables.resize(ht._tables.size());
//
//			for (size_t i = 0; i < ht._tables.size(); ++i)
//			{
//				HashTableNode<K, V>* cur = ht._tables[i];
//				while (cur)
//				{
//					HashTableNode<K, V>* newCur = new HashTableNode<K, V>(cur->_key, cur->_value);
//
//					newCur->_next = _tables[i];
//					_tables[i] = newCur;
//
//					cur = cur->_next;
//				}
//			}
//		}
//
//		void Clear()
//		{
//			for (size_t i = 0; i < _tables.size(); ++i)
//			{
//				HashTableNode<K, V>* cur = _tables[i];
//				while (cur)
//				{
//					HashTableNode<K, V>* del = cur;
//					cur = cur->_next;
//					delete del;
//				}
//
//				_tables[i] = NULL;
//			}
//		}
//
//		//InsertUnique
//		//InsertEquel
//		bool Insert(const K& key, const V& value)
//		{
//			_CheckCapacity(_size + 1);
//
//			// 1.查找key是否存在，存在则直接返回
//			size_t index = _HashFunc(key, _tables.size());
//			Node* begin = _tables[index];
//			while (begin)
//			{
//				if (begin->_key == key)
//				{
//					return false;
//				}
//				begin = begin->_next;
//			}
//
//			// 2.头插
//			Node* head = _tables[index];
//			Node* tmp = new Node(key, value);
//			tmp->_next = head;
//			_tables[index] = tmp;
//
//			++_size;
//
//			return true;
//		}
//		
//		HashTableNode<K, V>* Find(const K& key)
//		{
//			size_t index = _HashFunc(key, _tables.size());
//			Node* begin = _tables[index];
//			while (begin)
//			{
//				if (begin->_key == key)
//				{
//					return begin;
//				}
//
//				begin = begin->_next;
//			}
//
//			return NULL;
//		}
//		
//		bool Remove(const K& key)
//		{
//			size_t index = _HashFunc(key, _tables.size());
//
//			// 1.begin为桶的头结点
//			Node* begin = _tables[index];
//			if (begin == NULL)
//				return false;
//
//			if (begin->_key == key)
//			{
//				_tables[index] = begin->_next;
//				delete begin;
//				return true;
//			}
//
//			// 2.key在桶的中间节点
//			Node* prev = begin;
//			begin = begin->_next;
//			while (begin)
//			{
//				if (begin->_key == key)
//				{
//					prev->_next = begin->_next;
//					delete begin;
//					return true;
//				}
//				prev = prev;
//				begin = begin->_next;
//			}
//
//			return false;
//		}
//
//		void Print()
//		{
//			cout<<"HashTable"<<endl;
//			printf("Capacity:%d, Size:%d\n", _tables.size(), _size);
//			for (size_t i = 0; i < _tables.size(); ++i)
//			{
//				Node* begin = _tables[i];
//				if (begin == NULL)
//				{
//					continue;
//				}
//
//				printf("【%d】", i);
//
//				while(begin)
//				{
//					//printf("{%d,%.2f}->", begin->_key, begin->_value);
//					cout<<"{"<<begin->_key<<","<<begin->_value<<"}->";
//					begin = begin->_next;
//				}
//
//				cout<<"NULL"<<endl;
//			}
//		}
//
//		size_t Size()
//		{
//			return _size;
//		}
//		
//		size_t Capacity()
//		{
//			return _tables.size();
//		}
//
//	protected:
//
//		void _CheckCapacity(size_t size)
//		{
//			if (size < _tables.size())
//				return;
//
//			// 如果size大于table的大小，则进行重建，重新负载节点
//			size_t capacity = _GetPrimeNum(size);
//			vector<Node*> tmpHashTable;
//			tmpHashTable.reserve(capacity);
//			tmpHashTable.assign(capacity, 0);
//		
//			// 将旧表中的节点依次进行重新计算负载到新表中
//			for(size_t i = 0; i < _tables.size(); ++i)
//			{
//				Node* begin = _tables[i];
//				while (begin)
//				{
//					// 1.将这个节点摘下来
//					Node* tmp = begin;
//					begin = begin->_next;
//
//					// 2.重新计算在新表中的位置
//					size_t index = _HashFunc(tmp->_key, capacity);
//
//					// 3.将摘下来的tmp节点进行头插
//					Node* head = tmpHashTable[index];
//					tmp->_next = head;
//					tmpHashTable[index] = tmp;
//				}
//			}
//
//			_tables.swap(tmpHashTable);
//		}
//
//		size_t _HashFunc(const K& key, size_t capacity)
//		{
//			//
//			// 计算key Hash值仿函数对象，让程序的扩展性更强
//			//
//			//return _hash(key) % capacity;
//			return HashFunc<K>()(key) % capacity;
//		}
//
//	protected:
//		vector<Node*> _tables;
//		size_t _size;
//
//		//HashFunc _hash;		// 计算hash值的仿函数对象
//		//EqualKey _equal;		// 计算key值相等的仿函数
//	};
//
//	// 插入/查找/删除
//	void TestSome()
//	{
//		HashTable<int, double> ht1;
//		ht1.Insert(1,1);
//		ht1.Insert(1,1);
//		ht1.Insert(2,1);
//		ht1.Insert(3,1);
//		ht1.Insert(4,1);
//		ht1.Insert(5,1);
//		ht1.Insert(6,1);
//		ht1.Insert(7,1);
//		ht1.Insert(8,1);
//		ht1.Insert(9,1);
//
//		ht1.Insert(53,1);
//		ht1.Insert(54,1);
//		ht1.Insert(55,1);
//		ht1.Insert(56,1);
//
//		ht1.Print();
//
//		HashTable<int, double>::Node* ret = ht1.Find(2);
//		cout<<"Find 2 ?: "<<ret<<endl;
//
//		ret = ht1.Find(30);
//		cout<<"Find 30 ?: "<<ret<<endl;
//
//		ht1.Remove(2);
//		ht1.Remove(3);
//
//		ht1.Print();
//		
//		// 测试字典
//		HashTable<string, string> dict;
//		dict.Insert("tree", "树");
//		dict.Insert("flower", "花");
//		dict.Print();
//	}
//
//	// 测试哈希表扩张重建
//	void TestRebuilt()
//	{
//		HashTable<int, double> ht1;
//		ht1.Insert(53,53);
//		ht1.Insert(54,54);
//
//		for (size_t i = 0; i < 50; ++i)
//		{
//			ht1.Insert(i, i);
//		}
//
//		ht1.Print();
//
//		ht1.Insert(63,63);
//		ht1.Insert(64,64);
//		ht1.Insert(65,65);
//
//		ht1.Insert(97,97);
//		ht1.Insert(98,98);
//		ht1.Insert(99,99);
//
//		ht1.Print();
//
//		HashTable<int, double> ht2(ht1);
//		ht2.Print();
//	}
//
//	#include <time.h>
//
//	// 随机数据测试哈希表的负载
//	void TestOp()
//	{
//		HashTable<int, double> ht1;
//		srand(time(0));
//
//		for(size_t i = 0; i < 2000; ++i)
//		{
//			size_t key = rand();
//			ht1.Insert(key, key);
//		}
//
//		ht1.Print();
//	}
//}

#pragma once
#include <vector>

//namespace Bucket
//{
//	template<class K, class V>
//	struct HashNode
//	{
//		pair<K, V> _kv;
//		HashNode<K, V>* _next;
//	};
//
//	template<class K, class V, class Ref, class Ptr>
//	struct __HashTableIterator
//	{
//		typedef HashNode<K, V> Node;
//		Node* _node;
//
//		typedef __HashTableIterator<K, V, Ref, Ptr> Self;
//
//		Ref operator*()
//		{
//			return _node->_kv;
//		}
//
//		Ptr operator->()
//		{
//			&(operator*());
//		}
//
//		Self operator++()
//		{
//
//		}
//
//		Node* _Next(Node* node)
//		{
//			if (node->_next)
//			{
//				return node->_next;
//			}
//			else
//			{
//				size_t index = HashTable<K, V>::_HashFunc(node->_kv.first, node->_tableSize);
//				for (size_t i = index+1; i < node->_tableSize; ++i)
//				{
//					if ()
//					{
//					}
//				}
//				
//			}
//		}
//	};
//
//	template<class K, class V>
//	class HashTable
//	{
//		typedef HashNode<K, V> Node;
//	public:
//		HashTable()
//			:_size(0)
//		{}
//
//		HashTable(size_t size)
//			:_size(0)
//		{
//			_tables.resize(_GetNextPrime(size));
//		}
//
//		~HashTable()
//		{
//			Clear();
//		}
//
//		void Clear()
//		{
//			for (size_t i = 0; i < _tables.size(); ++i)
//			{
//				Node* cur = _tables[i];
//				while (cur)
//				{
//					Node* del = cur;
//					cur = cur->_next;
//					delete del;
//				}
//
//				_tables[i] = NULL;
//			}
//		}
//
//		pair<Node*, bool> Insert(const pair<K, V> kv)
//		{
//			CheckCapacity();
//
//			size_t index = _HashFunc(kv.first, _tables.size());
//
//			// 查找是否已经有key
//			Node* cur = _tables[index];
//			while (cur)
//			{
//				if (cur->_kv.first == kv.first)
//				{
//					return make_pair(cur, false);
//				}
//
//				cur = cur->_next;
//			}
//
//			Node* tmp = new Node(kv, _tables.size());
//			tmp->_next = _tables[index];
//			_tables[index] = tmp;
//		
//			++_size;
//		}
//
//		Node* Find(const K& key)
//		{
//			size_t index = _HashFunc(key, _tables.size());
//			Node* cur = _tables[index];
//			while (cur)
//			{
//				if (cur->_kv.first == key)
//				{
//					return cur;
//				}
//
//				cur = cur->_next;
//			}
//
//			return NULL;
//		}
//
//		bool Erase(const K& key)
//		{
//			size_t index = _HashFunc(key, _tables.size());
//
//			Node* prev = NULL;
//			Node* cur = _tables[index];
//
//			//...
//			while (cur)
//			{
//				if (cur->_kv.first == key)
//				{
//					if (prev == NULL)
//						_tables[index] = cur->_next;
//					else
//						prev->_next = cur->_next;
//
//					delete cur;
//					return true;
//				}
//				
//				prev = cur;
//				cur = cur->_next;
//			}
//
//			return false;
//		}
//
//		static size_t _HashFunc(const K& key, size_t size)
//		{
//			return key % size;
//		}
//
//	protected:
//		void CheckCapacity()
//		{
//			// 如果负载因子到1，就进行扩容
//			if (_size == _tables.size())
//			{
//				//...
//			}
//		}
//
//		size_t _GetNextPrime(size_t num)
//		{
//			const int _PrimeSize = 28;
//			static const unsigned long _PrimeList [_PrimeSize] =
//			{
//				53ul,         97ul,         193ul,       389ul,       769ul,
//				1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
//				49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
//				1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
//				50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
//				1610612741ul, 3221225473ul, 4294967291ul
//			};
//
//			for(size_t i = 0; i < _PrimeSize; ++i)
//			{
//				if (_PrimeList[i] > num)
//				{
//					return _PrimeList[i];
//				}
//			}
//
//			return _PrimeList[_PrimeSize-1];
//		}
//
//	protected:
//		vector<Node*> _tables;
//		size_t _size;
//	};
//
//	class UnorderdMap
//	{};
//}

namespace Bucket
{
	template<class K, class V>
	struct HashNode
	{
		pair<K, V> _kv;
		HashNode<K, V>* _next;
		//HashNode<K, V>* _prev;

		HashNode(const pair<K,V>& kv)
			:_kv(kv)
			,_next(NULL)
		{}
	};

	//template<class K, class V>
	//class HashTable;

	template<class K, class V, class Ref, class Ptr>
	struct __HashTableIterator
	{
		typedef HashNode<K, V> Node;
		Node* _node;
		HashTable<K, V>* _ht;

		typedef __HashTableIterator<K, V, Ref, Ptr> Self;

		__HashTableIterator(Node* node, HashTable<K, V>* ht)
			:_node(node)
			,_ht(ht)
		{}

		Ref operator*()
		{
			return _node->_kv;
		}

		Ptr operator->()
		{
			return &(operator*());
		}

		Self& operator++()
		{
			_node = _Next(_node);
			return *this;
		}

		//operator--
		//operator==

		bool operator!=(const Self& s) const
		{
			return _node != s._node;
		}

	protected:
		Node* _Next(Node* node)
		{
			Node* next = node->_next;
			if (next)
			{
				return next;
			}
			else
			{
				size_t index = _ht->_HashFunc(node->_kv.first)+1;
				for (; index < _ht->_tables.size(); ++index)
				{
					next = _ht->_tables[index];
					if (next)
					{
						return next;
					}
				}

				return NULL;
			}
		}
	};

	template<class K, class V>
	class HashTable
	{
		typedef HashNode<K, V> Node;
	public:
		typedef __HashTableIterator<K, V, pair<K,V>&, pair<K,V>*> Iterator;
		typedef __HashTableIterator<K, V, const pair<K,V>&, const pair<K,V>*> ConstIterator;

		friend struct Iterator;
		friend struct ConstIterator;

		HashTable()
			:_size(0)
		{}

		HashTable(size_t size)
			:_size(0)
		{
			_tables.resize(_GetNextPrime(size));
		}

		~HashTable()
		{
			Clear();
		}

		void Clear()
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* del = cur;
					cur = cur->_next;
					delete del;
				}

				_tables[i] = NULL;
			}
		}

		pair<Iterator, bool> Insert(const pair<K, V> kv)
		{
			CheckCapacity();

			size_t index = _HashFunc(kv.first);

			// 查找是否已经有key
			Node* cur = _tables[index];
			while (cur)
			{
				if (cur->_kv.first == kv.first)
				{
					return make_pair(Iterator(cur,this), false);
				}

				cur = cur->_next;
			}

			Node* tmp = new Node(kv);
			tmp->_next = _tables[index];
			_tables[index] = tmp;

			++_size;

			return make_pair(Iterator(tmp,this), true);
		}

		Node* Find(const K& key)
		{
			size_t index = _HashFunc(key);
			Node* cur = _tables[index];
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					return cur;
				}

				cur = cur->_next;
			}

			return NULL;
		}

		bool Erase(const K& key)
		{
			size_t index = _HashFunc(key);

			Node* prev = NULL;
			Node* cur = _tables[index];

			//...
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					if (prev == NULL)
						_tables[index] = cur->_next;
					else
						prev->_next = cur->_next;

					delete cur;
					return true;
				}

				prev = cur;
				cur = cur->_next;
			}

			return false;
		}

		Iterator Begin()
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				if (_tables[i])
				{
					return Iterator(_tables[i], this);
				}
			}

			return End();
		}

		Iterator End()
		{
			return Iterator(NULL, this);
		}

		void Swap(HashTable<K, V>& ht)
		{
			_tables.swap(ht._tables);
			swap(_size, ht._size);
		}

	protected:
		size_t _HashFunc(const K& key)
		{
			return key % _tables.size();
		}

		void CheckCapacity()
		{
			// 如果负载因子到1，就进行扩容
			if (_size == _tables.size())
			{
				size_t newSize = _GetNextPrime(_tables.size());

				HashTable<K, V> tmp;
				tmp._tables.resize(newSize);
				for (size_t i = 0; i < _tables.size(); ++i)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						tmp.Insert(cur->_kv);
						cur = cur->_next;
					}
				}

				Swap(tmp);
			}
		}

		size_t _GetNextPrime(size_t num)
		{
			const int _PrimeSize = 28;
			static const unsigned long _PrimeList [_PrimeSize] =
			{
				53ul,         97ul,         193ul,       389ul,       769ul,
				1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
				49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
				1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
				50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
				1610612741ul, 3221225473ul, 4294967291ul
			};

			for(size_t i = 0; i < _PrimeSize; ++i)
			{
				if (_PrimeList[i] > num)
				{
					return _PrimeList[i];
				}
			}

			return _PrimeList[_PrimeSize-1];
		}

	protected:
		vector<Node*> _tables;
		size_t _size;
	};

	template<class K, class V>
	class UnorderdMap //  UnorderdMutilMap  C++11
	{
	public:
		// Insert
		// Erase
		// Find
		// operator[]
	protected:
		HashTable<K, V> _ht;
	};

	void TestHashTable()
	{
		HashTable<int, int> ht1;
		ht1.Insert(make_pair(51, 3));
		ht1.Insert(make_pair(105, 3));
		ht1.Insert(make_pair(52, 3));
		ht1.Insert(make_pair(3, 3));
		ht1.Insert(make_pair(55, 3));
		ht1.Insert(make_pair(2, 3));
		ht1.Insert(make_pair(106, 3));
		ht1.Insert(make_pair(53, 3));
		ht1.Insert(make_pair(0, 3));

		HashTable<int, int>::Iterator it = ht1.Begin();
		while (it != ht1.End())
		{
			cout<<it->first<<":"<<it->second<<endl;
			++it;
		}

		UnorderdMap<string, string> dict;
		dict["sort"] = "排序";
		dict["left"] = "左边";
		dict["left"] = "剩余";
	}
}