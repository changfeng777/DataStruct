#pragma once

template<class K, class V>
struct Pair
{
	K _first;
	V _second;

	Pair(const K& key = K(), const V& value= V())
		:_first(key)
		,_second(value)
	{}
};