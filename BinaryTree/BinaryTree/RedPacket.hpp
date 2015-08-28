//
// 【海量数据处理问题】
// 2015年春节期间，a公司的支付软件某宝和t公司某信红包大乱战。
// 春节后高峰以后，公司Leader要求后台的攻城狮对后台的海量数
// 据进行分析。先要求分析出各地区发红包金额最多的前100用户。
// 现在知道人数最多的s地区大约有1000w用户。要求写一个算法实现。
//

// 思路：求N个数中最大的前K，使用最小堆解决。


#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<assert.h>
#include<windows.h>
using namespace std;

const int N = 10000000;
const int K = 100;

// 创建红包数据
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

// 堆调整（最小堆）
void HeapAdjust (int* array, int root, int size )
{
	assert(array);

	// child为左孩子的下标
	int child = root*2 + 1;
	while (child < size)
	{
		// 比较左孩子和右孩子，child指向小的孩子。
		if (child + 1 < size && array[child +1] < array[child])
		{
			child++;
		}

		// 1.若小的孩子节点大于根节点，则不再需要调整，跳出循环
		// 2.否则，交换孩子节点和根节点，将根节点继续往下调整。
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

	//创建一个最小堆
	for(int j = (K-1)/2; j >= 0; --j)
	{
		HeapAdjust(redPacket, j, K);
	}

	for(; index < moneys.size(); ++index)
	{
		// 若当前红包大于堆顶数据，则替换堆顶数据，调整一次堆。
		if (redPacket[0] < moneys[index])
		{
			redPacket[0] = moneys[index];
			HeapAdjust(redPacket, 0, K);
		}
	}

	// 按序打印堆数据。
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