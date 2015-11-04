#pragma once
#include "TypeTraits.hpp"
#include "Iterator.hpp"

// 此处的Copy可进行优化，萃取迭代器类型，根据不同类型的迭代器类型进行对应的处理
template <class InputIterator, class OutputIterator>
inline OutputIterator Copy(InputIterator first, InputIterator last,
						   OutputIterator result)
{
	// memcpy
	InputIterator cur = result;
	for ( ; first != last; ++first, ++cur)
		*cur = *first;

	return cur;
}

// 拷贝一段未初始化的数据
template <class InputIterator, class ForwardIterator>
inline ForwardIterator 
__UninitializedCopyAux(InputIterator first, InputIterator last,
						 ForwardIterator result, __TrueType)
{
	return Copy(first, last, result);
}

template <class InputIterator, class ForwardIterator>
ForwardIterator 
__UninitializedCopyAux(InputIterator first, InputIterator last,
						 ForwardIterator result, __FalseType)
{
	 ForwardIterator cur = result;
	 for ( ; first != last; ++first, ++cur)
		 Construct(&*cur, *first);

	 return cur;
}

template <class InputIterator, class ForwardIterator, class T>
inline ForwardIterator
__UninitializedCopy(InputIterator first, InputIterator last,
					ForwardIterator result, T*)
{
	return __UninitializedCopyAux(first, last, result, __TypeTraits<T>::IsPODType());
}

template <class InputIterator, class ForwardIterator>
inline ForwardIterator
UninitializedCopy(InputIterator first, InputIterator last, ForwardIterator result)
{
	return __UninitializedCopy(first, last, result, ValueType(result));
}

// 特化
inline char* 
UninitializedCopy(const char* first, const char* last, char* result)
{
	memmove(result, first, last - first);
	return result + (last - first);
}

inline wchar_t*
UninitializedCopy(const wchar_t* first, const wchar_t* last, wchar_t* result)
{
	memmove(result, first, sizeof(wchar_t) * (last - first));
	return result + (last - first);
}