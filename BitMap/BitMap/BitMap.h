#include<iostream>
#include<vector>
using namespace std;

//
// ����ʵ�ֵ���λͼBitMap��ʹ��BitSetΪ�˸�STL�е�bit_setһ�¡�
//
class BitSet
{
public:
	BitSet(size_t size)
	{
		// ������Ҫ���int���洢��Щ���ݡ�
		// ����5 == /32
		_datas.reserve((size>>5) + 1);
		_datas.assign((size>>5) + 1, 0);
	}

	size_t _Converse(size_t size)
	{
		return size>>5;
	}

	bool Test(size_t size)
	{
		size_t index = _Converse(size);
		size_t pos = size%32;
		return _datas[index]&(1<<pos);
	}

	void Set(size_t size)
	{
		size_t index = _Converse(size);
		size_t pos = size%32;
		_datas[index] |= (1<<pos);
	}

	void Reset(size_t size)
	{
		size_t index = _Converse(size);
		size_t pos = size%32;
		_datas[index] &= ~(1<<pos);
	}

	void Clear()
	{
		_datas.clear();
	}
private:
	vector<size_t> _datas;
};

void Test()
{
	BitSet s(-1);

	s.Set(100);
	s.Set(200);
	s.Set(300);

	cout<<"100 In BitMap:"<<s.Test(100)<<endl;
	cout<<"200 In BitMap:"<<s.Test(200)<<endl;
	cout<<"300 In BitMap:"<<s.Test(300)<<endl;
	cout<<"101 Not In BitMap:"<<s.Test(101)<<endl;

	s.Reset(100);
	cout<<"100 Not In BitMap:"<<s.Test(100)<<endl;
}

