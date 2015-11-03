#pragma once

//
// ���������ͱ�
//
struct InputIteratorTag {};
struct OutputIteratorTag {};
struct ForwardIteratorTag : public InputIteratorTag {};
struct BidirectionalIteratorTag : public ForwardIteratorTag {};
struct RandomAccessIteratorTag : public BidirectionalIteratorTag {};

//
// ��������Ƕ������5����Ӧ���ͱ�
// Iterator Category��Value Type��Difference Type��Pointer��Reference
// ��5����Ƕ���ͱ��壬ȷ�����ܹ�������ĸ�STL�ںϡ�
// �ҷ���Iterator Traits��������ȡ
//
template <class Category, class T, class Distance = ptrdiff_t,
class Pointer = T*, class Reference = T&>
struct Iterator
{
	typedef Category  IteratorCategory;		// ����������
	typedef T         ValueType;			// ��������ָ��������
	typedef Distance  DifferenceType;		// ����������֮��ľ���
	typedef Pointer   Pointer;				// ��������ָ�������͵�ָ��
	typedef Reference Reference;			// ��������ָ�������͵�����
};

//
// Traits����һ̨��������ȡ������եȡ���������������ԣ���Ӧ���ͱ�
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
// ƫ�ػ�ԭ��ָ������
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
// ƫ�ػ�constԭ��ָ������
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
// Distance��ʵ��

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
// Advance��ʵ��

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

// ���ص�����������
template <class Iterator>
inline typename IteratorTraits<Iterator>::IteratorCategory
IteratorCategory(const Iterator&)
{
	return IteratorTraits<Iterator>::IteratorCategory();
}

template <class Iterator>
inline typename IteratorTraits<Iterator>::ValueType*
DistanceType(const Iterator&)
{
	return static_cast<typename IteratorTraits<Iterator>::DifferenceType*>(0);
}

template <class Iterator>
inline typename IteratorTraits<Iterator>::ValueType*
ValueType(const Iterator&)
{
	return static_cast<typename IteratorTraits<Iterator>::ValueType*>(0);
}