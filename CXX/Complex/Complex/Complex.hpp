/****************************************************************************************Complex.hpp:
	Copyright (c) Bit Software, Inc.(2013), All rights reserved.

Purpose:
	实现复数类
	1.练习对类和对象的理解
	2.练习运算符的重载
	3.练习返回引用和返回值的处理

Author:
	xxx

Created Time:
	2015-4-26
****************************************************************************************/

#pragma once
class Complex
{
public:
	// 带缺省值的构造函数
	Complex (double real = 0, double image = 0)
		:_real(real)
		,_image(image)
	{
		cout<<"Complex (double real = 0, double image = 0)"<<endl;
	}

	// 析构函数
	~Complex()
	{
		cout<<"~Complex()"<<endl;
	}

	// 拷贝构造函数
	Complex (const Complex& d)
		:_image(d._image)
		,_real(d._real)
	{
		cout<<"Complex (const Complex& d)"<<endl;
	}

	// 赋值运算符重载
	Complex& operator= (const Complex& d)
	{
		cout<<"operator= (const Complex& d)"<<endl;

		if (this != &d)
		{
			this->_real = d._real;
			this->_image = d._image;
		}

		return *this;
	}

	void Display()
	{
		cout<<"Real:"<<_real<<"--Image:"<<_image<<endl;
	}

public:
	//
	// 1.注意搞清楚这里什么时候可以返回引用（Complex&），什么时候可以返回值
	// 2.注意区分前置++和后置++的区别
	//

	Complex& operator++() //前置++
	{
		this->_real++;
		this->_image++;

		return *this;
	}

	Complex operator++(int) //后置++
	{
		Complex tmp(*this);

		this->_real++;
		this->_image++;
		return tmp;
	}

	Complex& operator--();	// 前置--
	Complex operator--(int); //后置--

	Complex operator+(const Complex& c);
	Complex operator-(const Complex& c);

	Complex& operator-=(const Complex& c);
	Complex& operator+=(const Complex& c);

	Complex operator*(const Complex& c);
	Complex operator/(const Complex& c);

	Complex& operator*=(const Complex& c);
	Complex& operator/=(const Complex& c);

private:
	double _real;
	double _image;
};

void TestComplex()
{
	Complex c1(2.2, 1.1);

	Complex c2 = c1++;
	c1.Display();
	c2.Display();
}