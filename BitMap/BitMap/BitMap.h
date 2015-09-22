#include<iostream>
#include<vector>
using namespace std;

class BitSet
{
public:
	BitSet(size_t size)
	{
		// 计算需要多个int来存储这些数据。
		// 右移5 == /32
		_datas.reserve((size>>5) + 1);
		_datas.assign((size>>5) + 1, 0);
	}

	size_t _Converse(size_t size)
	{
		return size>>5;
	}

	bool IsInSet(size_t size)
	{
		size_t index = _Converse(size);
		size_t pos = size%32;
		return _datas[index]&(1<<pos);
	}

	void SetIn(size_t size)
	{
		size_t index = _Converse(size);
		size_t pos = size%32;
		_datas[index] |= (1<<pos);
	}

	void ClearIn(size_t size)
	{
		size_t index = _Converse(size);
		size_t pos = size%32;
		_datas[index] &= ~(1<<pos);
	}
private:
	vector<size_t> _datas;
};

void Test()
{
	BitSet s(-1);

	s.SetIn(100);
	s.SetIn(200);
	s.SetIn(300);

	cout<<"100 In BitMap:"<<s.IsInSet(100)<<endl;
	cout<<"200 In BitMap:"<<s.IsInSet(200)<<endl;
	cout<<"300 In BitMap:"<<s.IsInSet(300)<<endl;
	cout<<"101 Not In BitMap:"<<s.IsInSet(101)<<endl;

	s.ClearIn(100);
	cout<<"100 Not In BitMap:"<<s.IsInSet(100)<<endl;
}

