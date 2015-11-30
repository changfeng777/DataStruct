#pragma once

//
// 哈希表的闭散列线性探测法，使用懒删除的标记法来处理删除的问题。
//

enum Status
{
	EMPTY = 0,		// 空
	EXIST = 1,		// 存在
	DELETED = 2,	// 删除
};

// 一次探测
namespace ONE_DETECT
{
	template<class K>
	class HashTable
	{
	public:
		HashTable(const size_t capaciy = 10)
			:_size(0)
			,_capaciy(capaciy)
		{
			_table = new K[_capaciy];
			_status = new Status[_capaciy];
			memset(_status, EMPTY, _capaciy*sizeof(Status));
			memset(_table, 0, _capaciy*sizeof(K));
		}

		~HashTable()
		{
			if (_table)
			{
				delete [] _table;
			}

			if (_status)
			{
				delete [] _status;
			}
		}

	public:
		bool Insert(const K& key)
		{
			if (_size == _capaciy)
			{
				cout<<"Hash Table Is Full\n"<<endl;
				return false;
			}

			size_t hashIndex = HashFunc1(key);
			while (_status[hashIndex] == EXIST)
			{
				if (_table[hashIndex] == key)
				{
					return false;
				}

				++hashIndex;
				if (hashIndex == _capaciy)
				{
					hashIndex = 0;
				}
			}
			_table[hashIndex] = key;
			_status[hashIndex] = EXIST;
			++_size;

			return true;
		}

		bool Find(const K& key, size_t& index)
		{
			if (_size == 0)
			{
				cout<<"Hash Table Is Empty"<<endl;
				return false;
			}
			size_t hashIndex = HashFunc1(key);
			size_t begin = hashIndex;
			do 
			{
				if (_status[begin] == EXIST && _table[begin] == key)
				{
					index = begin;
					return true;
				}

				++begin;
				if (begin == _capaciy)
				{
					begin = 0;
				}
			} while (begin != hashIndex && _status[begin] != EMPTY);

			return false;
		}

		bool Remove(const K& key)
		{
			size_t index;
			if(Find(key, index))
			{
				// 使用懒删除法做标记
				_status[index] = DELETED;
				--_size;
				return true;
			}

			return false;
		}

		void Print()
		{
			for (size_t i = 0; i < _capaciy; ++i)
			{
				cout<<"【"<<_table[i]<<":"<<_status[i]<<"】 ";
			}
			cout<<endl;
		}
	protected:
		// 线性探测
		size_t HashFunc1(const K& key)
		{
			return key%_capaciy;
		}

	private:
		K*		_table;		// 哈希表内存块
		Status* _status;	// 数据状态
		size_t	_size;		// 表中数据个数
		size_t	_capaciy;	// 容量
	};

	void Test1()
	{
		HashTable<int> ht1;
		ht1.Insert(10);
		ht1.Insert(20);
		ht1.Insert(30);
		ht1.Insert(40);
		ht1.Insert(50);
		ht1.Insert(21);
		ht1.Insert(22);
		ht1.Insert(23);
		ht1.Insert(24);
		ht1.Insert(25);
		ht1.Print();

		ht1.Remove(10);
		ht1.Remove(20);
		ht1.Print();


		size_t index;
		cout<<"Find 40 ? "<<ht1.Find(40, index)<<endl;
		cout<<"Find 100 ? "<<ht1.Find(100, index)<<endl;
	}

	void Test2()
	{
		HashTable<int> ht1;
		ht1.Insert(89);
		ht1.Insert(18);
		ht1.Insert(49);
		ht1.Insert(58);
		ht1.Insert(9);
		ht1.Print();
	}
}

// 二次探测
namespace SECOND_DETECT
{
	template<class K>
	class HashTable
	{
	public:
		HashTable(const size_t capaciy = 10)
			:_size(0)
			,_capaciy(capaciy)
		{
			_table = new K[_capaciy];
			_status = new Status[_capaciy];
			memset(_status, EMPTY, _capaciy*sizeof(Status));
			memset(_table, 0, _capaciy*sizeof(K));
		}

		~HashTable()
		{
			if (_table)
			{
				delete [] _table;
			}

			if (_status)
			{
				delete [] _status;
			}
		}

	public:
		bool Insert(const K& key)
		{
			if (_size == _capaciy)
			{
				cout<<"Hash Table Is Full\n"<<endl;
				return false;
			}

			size_t hashIndex = HashFunc1(key);
			int i = 1;
			while (_status[hashIndex] == EXIST)
			{
				if (_table[hashIndex] == key)
				{
					return false;
				}

				hashIndex = HashFunc2(hashIndex, i++);
				if (hashIndex == _capaciy)
				{
					hashIndex = 0;
				}
			}
			_table[hashIndex] = key;
			_status[hashIndex] = EXIST;
			++_size;

			return true;
		}

		bool Find(const K& key, size_t& index)
		{
			if (_size == 0)
			{
				cout<<"Hash Table Is Empty"<<endl;
				return false;
			}
			size_t hashIndex = HashFunc1(key);
			size_t begin = hashIndex;
			int i = 1;
			do 
			{
				if (_status[begin] == EXIST && _table[begin] == key)
				{
					index = begin;
					return true;
				}

				begin = HashFunc2(begin, i++);
				if (begin == _capaciy)
				{
					begin = 0;
				}
			} while (begin != hashIndex && _status[begin] != EMPTY);

			return false;
		}

		bool Remove(const K& key)
		{
			size_t index;
			if(Find(key, index))
			{
				// 使用懒删除法做标记
				_status[index] = DELETED;
				--_size;
				return true;
			}

			return false;
		}

		void Print()
		{
			for (size_t i = 0; i < _capaciy; ++i)
			{
				cout<<"【"<<_table[i]<<":"<<_status[i]<<"】 ";
			}
			cout<<endl;
		}
	protected:
		// 线性探测
		size_t HashFunc1(const K& key)
		{
			return key%_capaciy;
		}

		// 二次探测
		size_t HashFunc2(size_t last, size_t i)
		{
			return (last + (2*i - 1) % _capaciy);
		}

	private:
		K*		_table;		// 哈希表内存块
		Status* _status;	// 数据状态
		size_t	_size;		// 表中数据个数
		size_t	_capaciy;	// 容量
	};

	void Test1()
	{
		HashTable<int> ht1;
		ht1.Insert(10);
		ht1.Insert(20);
		ht1.Insert(30);
		ht1.Insert(40);
		ht1.Insert(50);
		ht1.Insert(21);
		ht1.Insert(22);
		ht1.Insert(23);
		ht1.Insert(24);

		ht1.Print();

		//ht1.Insert(25);
		//ht1.Print();

		ht1.Remove(10);
		ht1.Remove(20);
		ht1.Print();


		size_t index;
		cout<<"Find 40 ? "<<ht1.Find(40, index)<<endl;
		cout<<"Find 100 ? "<<ht1.Find(100, index)<<endl;
	}

	void Test2()
	{
		HashTable<int> ht1;
		ht1.Insert(89);
		ht1.Insert(18);
		ht1.Insert(49);
		ht1.Insert(58);
		ht1.Insert(9);
		ht1.Print();
	}
}