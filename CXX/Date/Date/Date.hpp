/******************************************************************************************
Date.hpp:
	Copyright (c) Bit Software, Inc.(2013), All rights reserved.

Purpose:
	������ʵ��һ��������

Author:
	xxx

Created Time:
	2015-4-26
******************************************************************************************/
#include <assert.h>

class Date
{
public:
	Date (int year = 1900, int month = 1, int day = 1)
		:_year(year)
		,_month(month)
		,_day(day)
	{
		// ��������������ǷǷ�ʱ�䣬���ʼ��Ϊ1900-1-1
		assert(CheckDate());
	}

	Date (const Date& d)
		:_year(d._year)
		,_month(d._month)
		,_day(d._day)
	{}

	Date& operator= (const Date& d)
	{
		if (this != &d)
		{
			this->_year = d._year;
			this->_month = d._month;
			this->_day = d._day;
		}

		return *this;
	}

	// ���ʱ���Ƿ���Ч
	bool CheckDate ()
	{
		if(_year < 1900
			||(_month < 1 || _month > 12)
			||(_day < 1   || _day > DaysOfMonth(_year, _month)))
			return false;
		else
			return true;
	}

	void Display ()
	{
		cout<<_year<<"-"<<_month<<"-"<<_day<<endl<<endl;
	}

public:
	// �����ڷǷ�
	static int DaysOfMonth (int year, int month)
	{
		assert(year >= 1900 && (month > 0 && month < 13));

		static int monthDays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		int days = monthDays[month];

		// ����Ķ���Ҫ��һ��
		if (month == 2
			&& ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
		{
			days += 1;
		}

		return days;
	}

public:
	bool operator == (const Date& d)
	{
		return _year == d._year
			&& _month == d._month
			&& _day == d._day;
	}

	bool operator != (const Date& d)
	{
		return !(*this == d);
	}

	bool operator > (const Date& d)
	{
		return _year > d._year 
			|| (_year == d._year && _month > d._month)
			|| (_year == d._year && _month == d._month && _day > d._day);
	}

	/*bool operator > (const Date& d)
	{
		if(_year > d._year)
			return true;

		if (_year == d._year)
		{
			if (_month > d._month)
			{
				return true;
			}

			if (_month == d._month)
			{
				if (_day > d._day)
				{
					return true;
				}
			}
		}

		return false;
	}*/

	bool operator >= (const Date& d)
	{
		return *this > d || *this == d;
	}

	bool operator < (const Date& d)
	{
		return !(*this >= d);
	}

	bool operator <= (const Date& d)
	{
		return !(*this > d);
	}

	// ������ת��Ϊ��ȷ������
	void _ToCorrectDate()
	{
		// ��_dayΪ��������ʼУ������
		while(_day <= 0)
		{
			if (_month == 1)
			{
				_year--;
				_month = 12;
			}
			else
			{
				_month--;
			}
			
			_day += DaysOfMonth (_year, _month);
		}

		// ��_dayΪ��������ʼУ������
		while (_day >= DaysOfMonth(_year, _month))
		{
			_day -= DaysOfMonth (_year, _month);

			if (_month == 12)
			{
				_year++;
				_month = 1;
			}
			else
			{
				_month++;
			}
		}
	}

	//
	// ����һ�����ڼӼ�һ�������Ժ�����ڡ�
	//
	Date operator+(int day)
	{
		Date d(*this);
		d._day += day;
		d._ToCorrectDate();
		return d;
	}

	Date operator-(int day)
	{
		Date d(*this);
		d._day -= day;
		d._ToCorrectDate();
		return d;
	}

	Date& operator-=(int day)
	{
		this->_day -= day;
		this->_ToCorrectDate();
		return *this;
	}

	Date& operator+=(int day)
	{
		this->_day += day;
		this->_ToCorrectDate();
		return *this;
	}

	 // ǰ��++
	const Date& operator++()
	{
		*this += 1;
		return *this;
	}

	// ����++
	Date operator++(int)
	{
		Date tmp(*this);
		*this += 1;
		return tmp;
	}

	// ǰ��--
	const Date& operator--()
	{
		*this -= 1;
		return *this;
	}

	 // ����--
	Date operator--(int)
	{
		Date tmp(*this);
		*this -= 1;
		return tmp;
	}

	//
	// �����������û������
	// ����������������Ժ�Ĳ������
	//
	int operator-(const Date& d)
	{
		int flag = 1;
		Date min = *this, max = d;
		if (min < max)
		{
			flag = -1;
			min = d;
			max = *this;
		}
		
		int gapDays = 0;
		while (min != max)
		{
			++max;
			gapDays++;
		}

		return gapDays*flag;
	}

	friend istream& operator>>(istream& in, Date& d);
	friend ostream& operator<<(ostream& out, Date& d);
private:
	int _year;
	int _month;
	int _day;
};

istream& operator>>(istream& in, Date& d)
{
	cout<<"�������������ڵ���-��-��:"<<endl;
	in>>d._year>>d._month>>d._day;

	return in;
}

ostream& operator<<(ostream& out, Date& d)
{
	out<<d._year<<"-"<<d._month<<"-"<<d._day;

	return out;
}

void Test1()
{
	Date d1(2015, 12, 15);
	cout<<d1<<endl;

	d1 += 15;
	cout<<d1<<endl;

	d1 -= 30;
	cout<<d1<<endl;



}


void PromptInfo()
{
	cout<<"==============���ڼ�����================"<<endl;
	cout<<"1.�ƺ��������"<<endl;
	cout<<"2.�������ڲ�"<<endl;
	cout<<"0.�˳�"<<endl;
	cout<<"========================================"<<endl;
}

//
// ʵ�����ڼ�����
// http://bjtime.cn/riqi.asp
//
void TestDate()
{
	Date d1, d2;
	int option, days;
	do {
		PromptInfo();
		cin>>option;

		switch(option)
		{
		case 0:
			break;
		case 1:
			cin>>d1;
			if (!d1.CheckDate())
			{
				cout<<"�������ڷǷ���"<<endl;
				break;
			}
			cout<<"���������ƺ������"<<endl;
			cin>>days;
			d1+=days;
			cout<<d1<<endl;
			break;
		case 2:
			cin>>d1;
			if (!d1.CheckDate())
			{
				cout<<"�������ڷǷ���"<<endl;
				break;
			}
			cin>>d2;
			if (!d2.CheckDate())
			{
				cout<<"�������ڷǷ���"<<endl;
				break;
			}
			days = d1 - d2;
			cout<<"��������:"<<days<<endl;
			break;
		default:
			cout<<"ѡ�����������ѡ��"<<endl;
			break;
		}
	}while(option != 0);
}