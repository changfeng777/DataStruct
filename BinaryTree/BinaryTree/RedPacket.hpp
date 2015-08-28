//
// ���������ݴ������⡿
// 2015�괺���ڼ䣬a��˾��֧�����ĳ����t��˾ĳ�ź������ս��
// ���ں�߷��Ժ󣬹�˾LeaderҪ���̨�Ĺ���ʨ�Ժ�̨�ĺ�����
// �ݽ��з�������Ҫ�������������������������ǰ100�û���
// ����֪����������s������Լ��1000w�û���Ҫ��дһ���㷨ʵ�֡�
//

// ˼·����N����������ǰK��ʹ����С�ѽ����


#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<assert.h>
#include<windows.h>
using namespace std;

const int N = 10000000;
const int K = 100;

// �����������
void CreateRedPacket(vector<int>& moneys)
{
	srand(time(0));
	moneys.reserve(N);
	for (int i = 0; i < N; ++i)
	{
		moneys.push_back(rand()%10000);
	}

	for(int j = N - K; j < N; ++j)
	{
		moneys[j] = rand() % N;
	}
}

// �ѵ�������С�ѣ�
void HeapAdjust (int* array, int root, int size )
{
	assert(array);

	// childΪ���ӵ��±�
	int child = root*2 + 1;
	while (child < size)
	{
		// �Ƚ����Ӻ��Һ��ӣ�childָ��С�ĺ��ӡ�
		if (child + 1 < size && array[child +1] < array[child])
		{
			child++;
		}

		// 1.��С�ĺ��ӽڵ���ڸ��ڵ㣬������Ҫ����������ѭ��
		// 2.���򣬽������ӽڵ�͸��ڵ㣬�����ڵ�������µ�����
		if(array[child] < array[root])
		{
			swap(array[child], array[root]);
			root = child;
			child = root *2 + 1;
		}
		else
		{
			break;
		}
	}
}

void GetTopK(const vector<int>& moneys)
{
	int redPacket[K];
	int index = 0;
	for(; index < K; ++index)
	{
		redPacket[index] = moneys[index];
	}

	//����һ����С��
	for(int j = (K-1)/2; j >= 0; --j)
	{
		HeapAdjust(redPacket, j, K);
	}

	for(; index < moneys.size(); ++index)
	{
		// ����ǰ������ڶѶ����ݣ����滻�Ѷ����ݣ�����һ�ζѡ�
		if (redPacket[0] < moneys[index])
		{
			redPacket[0] = moneys[index];
			HeapAdjust(redPacket, 0, K);
		}
	}

	// �����ӡ�����ݡ�
	for (int i = K; i >0; --i)
	{
		if (i%10 == 0)
		{
			printf("\n");
		}

		printf("%d, ", redPacket[0]);
		swap(redPacket[0], redPacket[i-1]);
		HeapAdjust(redPacket, 0, i);
	}

	cout<<endl;
}

int TestRedPacket()
{
	DWORD begin = GetTickCount();
	vector<int> moneys;
	CreateRedPacket(moneys);
	DWORD end = GetTickCount();

	DWORD gap1 = end - begin;

	begin = GetTickCount();
	GetTopK(moneys);
	end = GetTickCount();

	cout<<"Create Data:"<<gap1<<endl;
	cout<<"Get Top K:"<<end - begin<<endl;
	return 0;
}