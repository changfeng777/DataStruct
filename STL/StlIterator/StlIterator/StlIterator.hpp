#pragma once

//
// 迭代器的型别
//
struct InputIteratorTag {};
struct OutputIteratorTag {};
struct ForwardIteratorTag : public InputIteratorTag {};
struct BidirectionalIteratorTag : public ForwardIteratorTag {};
struct RandomAccessIteratorTag : public BidirectionalIteratorTag {};

//
// 迭代器内嵌包含的5种相应的型别
// Iterator Category、Value Type、Difference Type、Pointer、Reference
// 这5种内嵌的型别定义，确保了能够更方便的跟STL融合。
// 且方便Iterator Traits的类型萃取
//
template <class Category, class T, class Distance = ptrdiff_t,
class Pointer = T*, class Reference = T&>
struct Iterator
{
	typedef Category  IteratorCategory;		// 迭代器类型
	typedef T         ValueType;			// 迭代器所指对象类型
	typedef Distance  DifferenceType;		// 两个迭代器之间的距离
	typedef Pointer   Pointer;				// 迭代器所指对象类型的指针
	typedef Reference Reference;			// 迭代器所指对象类型的引用
};

//
// Traits就像一台“特性萃取机”，榨取各个迭代器的特性（对应的型别）
//
template <class Iterator>
struct IteratorTraits
{
	typedef typename Iterator::IteratorCategory IteratorCategory;
	typedef typename Iterator::ValueType        ValueType;
	typedef typename Iterator::DifferenceType   DifferenceType;
	typedef typename Iterator::Pointer           Pointer;
	typedef typename Iterator::Reference         Reference;
};

//
// 偏特化原生指针类型
//
template <class T>
struct IteratorTraits<T*>
{
	typedef RandomAccessIteratorTag IteratorCategory;
	typedef T                          ValueType;
	typedef ptrdiff_t                  DifferenceType;
	typedef T*                         Pointer;
	typedef T&                         Reference;
};

//
// 偏特化const原生指针类型
//
template <class T>
struct IteratorTraits<const T*>
{
	typedef RandomAccessIteratorTag IteratorCategory;
	typedef T                          ValueType;
	typedef ptrdiff_t                  DifferenceType;
	typedef const T*                   Pointer;
	typedef const T&                   Reference;
};

//////////////////////////////////////////////////////////////
// Distance的实现

template <class InputIterator>
inline typename IteratorTraits<InputIterator>::DifferenceType
__Distance(InputIterator first, InputIterator last, InputIteratorTag)
{
	IteratorTraits<InputIterator>::DifferenceType n = 0;
	while (first != last) {
		++first; ++n;
	}
	return n;
}

template <class RandomAccessIterator>
inline typename IteratorTraits<RandomAccessIterator>::DifferenceType
__Distance(RandomAccessIterator first, RandomAccessIterator last,
		   RandomAccessIteratorTag)
{
	return last - first;
}

template <class InputIterator>
inline typename IteratorTraits<InputIterator>::DifferenceType
Distance(InputIterator first, InputIterator last)
{
	return __Distance(first, last, IteratorTraits<InputIterator>::IteratorCategory());
}

///////////////////////////////////////////////////////////
// Advance的实现

template <class InputIterator, class Distance>
inline void __Advance(InputIterator& i, Distance n, InputIteratorTag)
{
	while (n--) ++i;
}

template <class BidirectionalIterator, class Distance>
inline void __Advance(BidirectionalIterator& i, Distance n, 
					  BidirectionalIteratorTag)
{
	if (n >= 0)
		while (n--) ++i;
	else
		while (n++) --i;
}

template <class RandomAccessIterator, class Distance>
inline void __Advance(RandomAccessIterator& i, Distance n, 
					  RandomAccessIteratorTag)
{
	i += n;
}

template <class InputIterator, class Distance>
inline void Advance(InputIterator& i, Distance n) 
{
	__Advance(i, n, IteratorTraits<InputIterator>::IteratorCategory());
}

template <class Iterator>
class ReverseIterator 
{
public:
	typedef typename IteratorTraits<Iterator>::IteratorCategory
		IteratorCategory;
	typedef typename IteratorTraits<Iterator>::ValueType
		ValueType;
	typedef typename IteratorTraits<Iterator>::DifferenceType
		Difference_type;
	typedef typename IteratorTraits<Iterator>::Pointer
		Pointer;
	typedef typename IteratorTraits<Iterator>::Reference
		Reference;

	typedef Iterator IteratorType;
	typedef ReverseIterator<Iterator> Self;

public:
	ReverseIterator() {}
	explicit ReverseIterator(IteratorType x)
		: _current(x) {}

	Reference operator*() const
	{
		Iterator tmp = _current;
		return *--tmp;
	}

	Pointer operator->() const
	{ return &(operator*()); }

	Self& operator++() {
		--_current;
		return *this;
	}
	Self operator++(int) {
		Self tmp = *this;
		--_current;
		return tmp;
	}
	Self& operator--() {
		++_current;
		return *this;
	}
	Self operator--(int) {
		Self tmp = *this;
		++_current;
		return tmp;
	}
	
	bool operator != (const Self& x) {
		return _current != x._current;
	}

protected:
	Iterator _current;
};
