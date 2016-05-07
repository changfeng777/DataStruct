#pragma once

#include"../../BitMap/BitMap/BitMap.h"
#include "Common.h"

//
// 布隆过滤器检查到不存在的数据一定不存在
// 检查到可能存在的数据，是不一定存在的，因为可能是其他值占据了这个位置，存在的误判
// 特点：节省空间、高效。缺点：存在误判
//
template<class K = string,
class HashFunc1 = __HashFunc1<K>,
class HashFunc2 = __HashFunc2<K>,
class HashFunc3 = __HashFunc3<K>,
class HashFunc4 = __HashFunc4<K>,
class HashFunc5 = __HashFunc5<K>>
class BloomFilter
{
public:
	BloomFilter(size_t size)
	{
		// 取素数做容量大小，减少哈希冲突
		_capacity = _GetPrimeNum(size);
		_bitSet.Resize(_capacity);
	}

	void Set(const K& key)
	{
		size_t index1 = HashFunc1()(key);
		size_t index2 = HashFunc2()(key);
		size_t index3 = HashFunc3()(key);
		size_t index4 = HashFunc4()(key);
		size_t index5 = HashFunc5()(key);

		cout<<index1<<" "<<index2<<" "<<index3<<" "<<index4<<" "<<index5<<endl;

		_bitSet.Set(index1%_capacity);
		_bitSet.Set(index2%_capacity);
		_bitSet.Set(index3%_capacity);
		_bitSet.Set(index4%_capacity);
		_bitSet.Set(index5%_capacity);
	}

	bool IsIn(const K& key)
	{
		size_t index1 = HashFunc1()(key);
		if (!_bitSet.Test(index1%_capacity))
			return false;

		size_t index2 = HashFunc2()(key);
		if (!_bitSet.Test(index2%_capacity))
			return false;

		size_t index3 = HashFunc3()(key);
		if (!_bitSet.Test(index3%_capacity))
			return false;

		size_t index4 = HashFunc4()(key);
		if (!_bitSet.Test(index4%_capacity))
			return false;

		size_t index5 = HashFunc5()(key);
		if (!_bitSet.Test(index5%_capacity))
			return false;

		return true;
	}
protected:
	BitSet _bitSet;
	size_t _capacity;
};

void TestBloomFilter()
{
	BloomFilter<> bf(40);
	bf.Set("HashFunc");
	bf.Set("TestBloomFilter");
	bf.Set("测试");
	bf.Set("工具");
	bf.Set("链接");

	cout<<"IsIn ?"<<bf.IsIn("HashFunc")<<endl;
	cout<<"IsIn ?"<<bf.IsIn("TestBloomFilter")<<endl;
	cout<<"IsIn ?"<<bf.IsIn("测试")<<endl;
	cout<<"IsIn ?"<<bf.IsIn("工具")<<endl;
	cout<<"IsIn ?"<<bf.IsIn("链接")<<endl;

	cout<<"IsIn ?"<<bf.IsIn("链接x")<<endl;
	cout<<"IsIn ?"<<bf.IsIn("HashFunc1")<<endl;
}