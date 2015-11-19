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
	{
		Destory();
	}

	GeneralList(const GeneralList& g)
	{
		_head = g.Copy();
	}

	GeneralList& operator=(GeneralList g)
	{
		swap(_head, g._head);
		return *this;
	}

public:
	bool _IsValueChar(char ch)
	{
		if ((ch >= '0' && ch <= '9')
			|| (ch >= 'a' && ch <= 'z')
			|| (ch >= 'A' && ch <= 'Z'))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void CreateList(GeneralListNode*& head, const char*& str)
	{
		if (*str++ != '(')
		{
			cout<<"invalid str"<<endl;
		}

		// ������һ��ġ�ͷ��㡿
		head = new GeneralListNode(HEAD_TYPE);
		GeneralListNode* begin = head;

		while(*str != '\0')
		{
			//
			// 1. ( ��һ���ӱ�Ŀ�ʼ������һ�����ӱ�ڵ㡿
			// 2. ����һ����ֵ�ڵ㡿�����ǿձ�������
			//
			if (*str == '(')
			{
				begin->_next = new GeneralListNode(SUB_TYPE);
				begin = begin->_next;

				CreateList(begin->_subLink, str);
			}
			else if(*str == ')')
			{
				return;
			}
			else if(_IsValueChar(*str))
			{
				begin->_next = new GeneralListNode(VALUE_TYPE, *str++);
				begin = begin->_next;
			}
			else
			{
				++str;
			}
		}
	}

	void Print()
	{
		_Print(_head);

		cout<<endl;
	}

	int Depth()
	{
		return _Depth(_head);
	}

	int Size()
	{
		return _Size(_head);
	}

	void Destory()
	{
		_Destroy(_head);
		_head = NULL;
	}

	GeneralListNode* Copy() const
	{
		return _Copy(_head);
	}

protected:
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

	int _Depth(GeneralListNode* head)
	{
		int depth = 1;

		GeneralListNode* begin = head;
		while (begin)
		{
			if(begin->_type == SUB_TYPE)
			{
				int ret = _Depth(begin->_subLink);
				if (depth < ret + 1)
				{
					depth = ret + 1;
				}
			}

			begin = begin->_next;
		}

		return depth;
	}

	int _Size(GeneralListNode* head)
	{
		int size = 0;
		GeneralListNode* begin = head;
		while (begin)
		{
			if(begin->_type == SUB_TYPE)
			{	
				size += _Size(begin->_subLink);
			}
			else if(begin->_type == VALUE_TYPE)
			{
				++size;
			}

			begin = begin->_next;
		}

		return size;
	}

	void _Destroy(GeneralListNode* head)
	{
		GeneralListNode* begin = head;
		while (begin)
		{
			GeneralListNode* del = begin;
			begin = begin->_next;

			if(del->_type == SUB_TYPE)
			{
				_Destroy(del->_subLink);
			}

			delete del;
		}
	}

	GeneralListNode* _Copy(GeneralListNode* head) const
	{
		GeneralListNode* newHead = new GeneralListNode(HEAD_TYPE);

		GeneralListNode* prev = newHead;
		GeneralListNode* begin = head->_next;
		while (begin)
		{
			GeneralListNode* cur = new GeneralListNode();

			if(begin->_type == HEAD_TYPE)
			{
				cur->_type = HEAD_TYPE;
			}
			else if (begin->_type == SUB_TYPE)
			{
				cur->_type = SUB_TYPE;
				cur->_subLink = _Copy(begin->_subLink);
			}
			else
			{
				cur->_type = VALUE_TYPE;
				cur->_value = begin->_value;
			}

			prev->_next = cur;
			prev = cur;

			begin = begin->_next;
		}

		return newHead;
	}

private:
	GeneralListNode* _head;
};

//<1> A = ()
//<2> B = (a,b)
//<3> C = (a,b,(c,d))
//<4> D = (a,b,(c,d),(e,(f),h)) 
//<5> E = (((),()))

void Test1()
{
	// һ��
	GeneralList gl("(a,b)");
	gl.Print();

	cout<<"Depth:"<<gl.Depth()<<endl;

	// ����
	GeneralList g2("(a,b,(c,d))");
	g2.Print();

	cout<<"Depth:"<<g2.Depth()<<endl;

	// ���� + �пո��
	GeneralList g3("(a, b,(c,d),(e,(f),h))");
	g3.Print();

	cout<<"Depth:"<<g3.Depth()<<endl;
	cout<<"Size:"<<g3.Size()<<endl;

	// ���ձ�Ƕ��
	GeneralList g4("(((),()))");
	g4.Print();

	cout<<"Depth:"<<g4.Depth()<<endl;

	GeneralList g5(g3);
	g5.Print();

	GeneralList g6 = g5;
	g6.Print();
}