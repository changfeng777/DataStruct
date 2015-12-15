/****************************************************************************************Complex.hpp:
	Copyright (c) Bit Software, Inc.(2013), All rights reserved.

Purpose:
	ʵ�ָ�����
	1.��ϰ����Ͷ�������
	2.��ϰ�����������
	3.��ϰ�������úͷ���ֵ�Ĵ���

Author:
	xxx

Created Time:
	2015-4-26
****************************************************************************************/

#pragma once
class Complex
{
public:
	// ��ȱʡֵ�Ĺ��캯��
	Complex (double real = 0, double image = 0)
		:_real(real)
		,_image(image)
	{
		cout<<"Complex (double real = 0, double image = 0)"<<endl;
	}

	// ��������
	~Complex()
	{
		cout<<"~Complex()"<<endl;
	}

	// �������캯��
	Complex (const Complex& d)
		:_image(d._image)
		,_real(d._real)
	{
		cout<<"Complex (const Complex& d)"<<endl;
	}

	// ��ֵ���������
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
	// 1.ע����������ʲôʱ����Է������ã�Complex&����ʲôʱ����Է���ֵ
	// 2.ע������ǰ��++�ͺ���++������
	//

	Complex& operator++() //ǰ��++
	{
		this->_real++;
		this->_image++;

		return *this;
	}

	Complex operator++(int) //����++
	{
		Complex tmp(*this);

		this->_real++;
		this->_image++;
		return tmp;
	}

	Complex& operator--();	// ǰ��--
	Complex operator--(int); //����--

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