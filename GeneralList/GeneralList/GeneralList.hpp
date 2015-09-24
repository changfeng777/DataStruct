#pragma once

enum TYPE
{
	HEAD_TYPE = 0,		// ����ͷ�ڵ�
	VALUE_TYPE = 1,		// �洢ֵ�Ľڵ�
	SUB_TYPE = 2,		// ָ���ӱ�
};

class GeneralListNode
{
	friend class GeneralList;

public:
	GeneralListNode(TYPE type = VALUE_TYPE, const int value = 0)
		:_type(type)
		,_next(NULL)
		,_value(0)
	{
		if (_type == VALUE_TYPE)
		{
			_value = value;
		}
		else if (_type == SUB_TYPE)
		{
			_subLink = NULL;
		}
	}

private:
	TYPE _type;				// �ڵ�����
	GeneralListNode* _next;	// ָ��ͬһ����һ���ڵ��ָ��

	union
	{
		char _value;				// _type == VALUE_TYPE �洢ֵ
		GeneralListNode* _subLink;	// _type == SUB_TYPE ָ���ӱ��ָ��
	};
};

class GeneralList
{
public:
	GeneralList(const string& s = "")
		:_head(NULL)
	{
		const char* str = s.c_str();
		CreateList(_head, str);
	}

	~GeneralList()
	{}

public:
	void CreateList(GeneralListNode*& head, const char*& str)
	{
		if (*str == '\0')
			return;

		if (*str != '(')
		{
			cout<<"invalid str"<<endl;
		}

		// ������һ��ġ�ͷ��㡿
		head = new GeneralListNode(HEAD_TYPE);
		GeneralListNode* begin = head;

		// �˴�str++����( , )�ȷ���
		while(*str != '\0' && *str++ != ')')
		{
			//
			// 1. ( ��һ���ӱ�Ŀ�ʼ������һ�����ӱ�ڵ㡿
			// 2. ����һ����ֵ�ڵ㡿
			//
			if (*str == '(')
			{
				begin->_next = new GeneralListNode(SUB_TYPE);
				begin = begin->_next;

				CreateList(begin->_subLink, str);
			}
			else if(*str != ')')
			{
				begin->_next = new GeneralListNode(VALUE_TYPE, *str++);
				begin = begin->_next;
			}
		}
	}

	void Print()
	{
		_Print(_head);

		cout<<endl;
	}

	void _Print(GeneralListNode* head)
	{
		GeneralListNode* begin = head;
		while (begin)
		{
			//
			// 1.ͷ�ڵ㣬���ӡ(
			// 2.ֵ�ڵ㣬���ӡֵ
			// 3.�ӱ�ڵ㣬��ݹ��ӡ�ӱ�
			//
			if (begin->_type == HEAD_TYPE)
			{
				cout<<"(";
			}
			else if(begin->_type == VALUE_TYPE)
			{
				cout<<(char)begin->_value;

				if (begin->_next)
					cout<<",";
			}
			else
			{
				_Print(begin->_subLink);

				if (begin->_next)
					cout<<",";
			}

			begin = begin->_next;
		}

		cout<<")";
	}

	GeneralListNode* Find(char value)
	{}

	void Insert(GeneralListNode* pos, char value)
	{}

	void Erase(GeneralListNode* n)
	{}

	int Depth()
	{}

	int Size()
	{}

private:
	GeneralListNode* _head;
};

void Test1()
{
	// һ��
	//GeneralList gl("(a,b)");
	//gl.Print();

	//// ����
	//GeneralList g2("(a,b,(c,d),e)");
	//g2.Print();

	// ����
	//GeneralList g3("(a,b,(c,d),(f,(g),()))");
	//g3.Print();

	// ���ձ�Ƕ��
	//GeneralList g4("(((),()))");
	//g4.Print();
}