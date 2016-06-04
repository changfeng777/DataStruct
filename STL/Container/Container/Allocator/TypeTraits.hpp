#pragma once

//
// POD: plain old data 平凡类型（无关痛痒的类型）
// 指在C++ 中与 C兼容的类型，可以按照 C 的方式处理。
//

struct __TrueType
{
	bool Get ()
	{
		return true ;
	}
};

struct __FalseType
{
	bool Get ()
	{
		return false ;
	}
};

template <class _Tp>
struct __TypeTraits
{
	typedef __FalseType    HasTrivialDefaultConstructor;
	typedef __FalseType    HasTrivialCopyConstructor;
	typedef __FalseType    HasTrivialAssignmentOperator;
	typedef __FalseType    HasTrivialDestructor;

	typedef __FalseType	   IsPODType;
};

// 特化
template <>
struct __TypeTraits< bool>
{
	typedef __TrueType    HasTrivialDefaultConstructor;
	typedef __TrueType    HasTrivialCopyConstructor;
	typedef __TrueType    HasTrivialAssignmentOperator;
	typedef __TrueType    HasTrivialDestructor;
	typedef __TrueType    IsPODType;
};

template <>
struct __TypeTraits< char>
{
	typedef __TrueType    HasTrivialDefaultConstructor;
	typedef __TrueType    HasTrivialCopyConstructor;
	typedef __TrueType    HasTrivialAssignmentOperator;
	typedef __TrueType    HasTrivialDestructor;
	typedef __TrueType     IsPODType;
};

template <>
struct __TypeTraits< unsigned char >
{
	typedef __TrueType    HasTrivialDefaultConstructor;
	typedef __TrueType    HasTrivialCopyConstructor;
	typedef __TrueType    HasTrivialAssignmentOperator;
	typedef __TrueType    HasTrivialDestructor;
	typedef __TrueType     IsPODType;
};

template <>
struct __TypeTraits< short>
{
	typedef __TrueType    HasTrivialDefaultConstructor;
	typedef __TrueType    HasTrivialCopyConstructor;
	typedef __TrueType    HasTrivialAssignmentOperator;
	typedef __TrueType    HasTrivialDestructor;
	typedef __TrueType     IsPODType;
};

template <>
struct __TypeTraits< unsigned short >
{
	typedef __TrueType    HasTrivialDefaultConstructor;
	typedef __TrueType    HasTrivialCopyConstructor;
	typedef __TrueType    HasTrivialAssignmentOperator;
	typedef __TrueType    HasTrivialDestructor;
	typedef __TrueType     IsPODType;
};

template <>
struct __TypeTraits< int>
{
	typedef __TrueType    HasTrivialDefaultConstructor;
	typedef __TrueType    HasTrivialCopyConstructor;
	typedef __TrueType    HasTrivialAssignmentOperator;
	typedef __TrueType    HasTrivialDestructor;
	typedef __TrueType     IsPODType;
};

template <>
struct __TypeTraits< unsigned int >
{
	typedef __TrueType    HasTrivialDefaultConstructor;
	typedef __TrueType    HasTrivialCopyConstructor;
	typedef __TrueType    HasTrivialAssignmentOperator;
	typedef __TrueType    HasTrivialDestructor;
	typedef __TrueType     IsPODType;
};

template <>
struct __TypeTraits< long>
{
	typedef __TrueType    HasTrivialDefaultConstructor;
	typedef __TrueType    HasTrivialCopyConstructor;
	typedef __TrueType    HasTrivialAssignmentOperator;
	typedef __TrueType    HasTrivialDestructor;
	typedef __TrueType     IsPODType;
};

template <>
struct __TypeTraits< unsigned long >
{
	typedef __TrueType    HasTrivialDefaultConstructor;
	typedef __TrueType    HasTrivialCopyConstructor;
	typedef __TrueType    HasTrivialAssignmentOperator;
	typedef __TrueType    HasTrivialDestructor;
	typedef __TrueType     IsPODType;
};

template <>
struct __TypeTraits< long long >
{
	typedef __TrueType    HasTrivialDefaultConstructor;
	typedef __TrueType    HasTrivialCopyConstructor;
	typedef __TrueType    HasTrivialAssignmentOperator;
	typedef __TrueType    HasTrivialDestructor;
	typedef __TrueType     IsPODType;
};

template <>
struct __TypeTraits< unsigned long long>
{
	typedef __TrueType    HasTrivialDefaultConstructor;
	typedef __TrueType    HasTrivialCopyConstructor;
	typedef __TrueType    HasTrivialAssignmentOperator;
	typedef __TrueType    HasTrivialDestructor;
	typedef __TrueType     IsPODType;
};

template <>
struct __TypeTraits< float>
{
	typedef __TrueType    HasTrivialDefaultConstructor;
	typedef __TrueType    HasTrivialCopyConstructor;
	typedef __TrueType    HasTrivialAssignmentOperator;
	typedef __TrueType    HasTrivialDestructor;
	typedef __TrueType     IsPODType;
};

template <>
struct __TypeTraits< double>
{
	typedef __TrueType    HasTrivialDefaultConstructor;
	typedef __TrueType    HasTrivialCopyConstructor;
	typedef __TrueType    HasTrivialAssignmentOperator;
	typedef __TrueType    HasTrivialDestructor;
	typedef __TrueType     IsPODType;
};

template <>
struct __TypeTraits< long double >
{
	typedef __TrueType    HasTrivialDefaultConstructor;
	typedef __TrueType    HasTrivialCopyConstructor;
	typedef __TrueType    HasTrivialAssignmentOperator;
	typedef __TrueType    HasTrivialDestructor;
	typedef __TrueType     IsPODType;
};

template <class _Tp>
struct __TypeTraits< _Tp*>
{
	typedef __TrueType    HasTrivialDefaultConstructor;
	typedef __TrueType    HasTrivialCopyConstructor;
	typedef __TrueType    HasTrivialAssignmentOperator;
	typedef __TrueType    HasTrivialDestructor;
	typedef __TrueType     IsPODType;
};