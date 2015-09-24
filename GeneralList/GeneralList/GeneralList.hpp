#pragma once

enum TYPE
{
	HEAD_TYPE = 0,		// 附加头节点
	VALUE_TYPE = 1,		// 存储值的节点
	SUB_TYPE = 2,		// 指向子表
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
	TYPE _type;				// 节点类型
	GeneralListNode* _next;	// 指向同一层下一个节点的指针

	union
	{
		char _value;				// _type == VALUE_TYPE 存储值
		GeneralListNode* _subLink;	// _type == SUB_TYPE 指向子表的指针
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

		// 创建这一层的【头结点】
		head = new GeneralListNode(HEAD_TYPE);
		GeneralListNode* begin = head;

		// 此处str++跳过( , )等符号
		while(*str != '\0' && *str++ != ')')
		{
			//
			// 1. ( 是一个子表的开始，创建一个【子表节点】
			// 2. 创建一个【值节点】
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
			// 1.头节点，则打印(
			// 2.值节点，则打印值
			// 3.子表节点，则递归打印子表
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
	// 一层
	//GeneralList gl("(a,b)");
	//gl.Print();

	//// 两层
	//GeneralList g2("(a,b,(c,d),e)");
	//g2.Print();

	// 三层
	//GeneralList g3("(a,b,(c,d),(f,(g),()))");
	//g3.Print();

	// 多层空表嵌套
	//GeneralList g4("(((),()))");
	//g4.Print();
}