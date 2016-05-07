#pragma once

static unsigned long _GetPrimeNum(unsigned long num)
{
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

	size_t pos = 0;
	while (pos < _PrimeSize)
	{
		if (_PrimeList[pos] > num)
			break;

		++pos;
	}

	return _PrimeList[pos];
}

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

size_t SDBMHash(const char *str)  
{  
	register size_t hash = 0;  
	while (size_t ch = (size_t)*str++)  
	{  
		hash = 65599 * hash + ch;         
		//hash = (size_t)ch + (hash << 6) + (hash << 16) - hash;  
	}  
	return hash;  
}  

size_t RSHash(const char *str)  
{  
	register size_t hash = 0;  
	size_t magic = 63689;     
	while (size_t ch = (size_t)*str++)  
	{  
		hash = hash * magic + ch;  
		magic *= 378551;  
	}  
	return hash;  
} 

size_t APHash(const char *str)  
{  
	register size_t hash = 0;  
	size_t ch;  
	for (long i = 0; ch = (size_t)*str++; i++)  
	{  
		if ((i & 1) == 0)  
		{  
			hash ^= ((hash << 7) ^ ch ^ (hash >> 3));  
		}  
		else  
		{  
			hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));  
		}  
	}  
	return hash;
}

size_t JSHash(const char *str)  
{  
	if(!*str)
		return 0;

	register size_t hash = 1315423911;  
	while (size_t ch = (size_t)*str++)  
	{  
		hash ^= ((hash << 5) + ch + (hash >> 2));  
	}  
	return hash;  
} 

template<class K>
struct __HashFunc1
{
	size_t operator()(const K& key)
	{
		return BKDRHash(key.c_str());
	}
};

template<class K>
struct __HashFunc2
{
	size_t operator()(const K& key)
	{
		return SDBMHash(key.c_str());
	}
};

template<class K>
struct __HashFunc3
{
	size_t operator()(const K& key)
	{
		return RSHash(key.c_str());
	}
};


template<class K>
struct __HashFunc4
{
	size_t operator()(const K& key)
	{
		return APHash(key.c_str());
	}
};

template<class K>
struct __HashFunc5
{
	size_t operator()(const K& key)
	{
		return JSHash(key.c_str());
	}
};