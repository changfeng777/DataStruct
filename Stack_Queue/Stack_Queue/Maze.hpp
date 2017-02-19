/******************************************************************************************
Copyright (c) Bit Software, Inc.(2013), All rights reserved.

Purpose: 使用栈解决迷宫问题

Author: 迷宫实现

Created Time: 2015-8-1
******************************************************************************************/
#pragma once
#include <stack>

// ps:1.作业扩展使用递归实现迷宫，并比较非递归实现
//	  2.求迷宫问题的最优解

struct Pos
{
	int row; // 行
	int col; // 列
};

int** CreateMaze(int n)
{
	int** ppMaze = new int*[n];
	for (int i = 0; i < n; ++i)
	{
		ppMaze[i] = new int[n];
		memset(ppMaze[i], 0, sizeof(int)*n);
	}

	return ppMaze;
}

Pos InitMaze(int** ppMaze, int n)
{
	Pos entry;
	entry.row = 2;
	entry.col = 0;

	FILE* fOut = fopen("MazeMap.txt", "r");
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n;)
		{
			char ch = fgetc(fOut);
			if (ch == '0' || ch == '1')
			{
				ppMaze[i][j++] = ch - '0';
			}
			else if (ch == EOF)
			{
				cout<<"Maze Map Error"<<endl;
			}
		}
	}

	fclose(fOut);

	return entry;
}

void PrintMaze(int** ppMaze, int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cout<<ppMaze[i][j]<<" ";
		}
		cout<<endl;
	}

	cout<<endl;
}

bool CheckIsAccess(int** ppMaze, int n, Pos pos)
{
	if (pos.col > 0 && pos.col < n 
		&& pos.row > 0 && pos.row < n
		&& ppMaze[pos.row][pos.col] == 0)
	{
		return true;
	}

	return false;
}

bool GetMazePath(int** ppMaze, int n, const Pos& entry, stack<Pos>& path)
{
	assert(entry.col < n && entry.row < n);
	
	Pos cur = entry;
	ppMaze[cur.row][cur.col] = 2;
	path.push(cur);

	while (!path.empty())
	{
		 Pos next = path.top();
		
		 //
		 // 出口在最后一行
		 //
		 if (next.row == n-1)
			 return true;

		 // 上
		 next.row -= 1;
		 if (CheckIsAccess(ppMaze, n, next))
		 {
			ppMaze[next.row][next.col] = 2;
			path.push(next);
			continue;
		 }

		 // 右
		 next = path.top();
		 next.col += 1;
		 if (CheckIsAccess(ppMaze, n, next))
		 {
			 ppMaze[next.row][next.col] = 2;
			 path.push(next);
			 continue;
		 }

		 // 下
		 next = path.top();
		 next.row += 1;
		 if (CheckIsAccess(ppMaze, n, next))
		 {
			 ppMaze[next.row][next.col] = 2;
			 path.push(next);
			 continue;
		 }

		 // 左
		 next = path.top();
		 next.col -= 1;
		 if (CheckIsAccess(ppMaze, n, next))
		 {
			 ppMaze[next.row][next.col] = 2;
			 path.push(next);
			 continue;
		 }

		 Pos tmp = path.top();
		 ppMaze[tmp.row][tmp.col] = 3;
		 path.pop();
	}

	return false;
}

bool CheckIsAccess(int** ppMaze, int n, Pos cur, Pos next)
{
	if (next.col < 0 || next.col >= n 
		|| next.row < 0 || next.row >= n
		|| ppMaze[next.row][next.col] == 1)
	{
		return false;
	}

	if (ppMaze[next.row][next.col] == 0)
	{
		return true;
	}
	else
	{
		return ppMaze[cur.row][cur.col]+1 < ppMaze[next.row][next.col];
	}
}

// 求迷宫的最优解--最短路径
void GetShortMazePath(int** ppMaze, int n, const Pos& entry,
					  stack<Pos>& path, stack<Pos>& minPath)
{
	assert(ppMaze);

	Pos cur = entry;
	Pos next = cur;

	path.push(cur);

	// 已经到达出口
	if (next.row == n-1)
	{
		if (minPath.empty() || minPath.size() > path.size())
		{
			minPath = path;

			PrintMaze(ppMaze,n);
		}
		return;
	}

	// 上
	next = cur;
	next.row -= 1;
	if(CheckIsAccess(ppMaze, n, cur, next))
	{
		ppMaze[next.row][next.col] = ppMaze[cur.row][cur.col]+1;
		GetShortMazePath(ppMaze, n, next, path, minPath);
	}

	// 右
	next = cur;
	next.col += 1;
	if(CheckIsAccess(ppMaze, n, cur, next))
	{
		ppMaze[next.row][next.col] = ppMaze[cur.row][cur.col]+1;
		GetShortMazePath(ppMaze, n, next, path, minPath);
	}


	// 下
	next = cur;
	next.row += 1;
	if(CheckIsAccess(ppMaze, n, cur, next))
	{
		ppMaze[next.row][next.col] = ppMaze[cur.row][cur.col]+1;
		GetShortMazePath(ppMaze, n, next, path, minPath);
	}

	// 左
	next = cur;
	next.col -= 1;
	if(CheckIsAccess(ppMaze, n, cur, next))
	{
		ppMaze[next.row][next.col] = ppMaze[cur.row][cur.col]+1;
		GetShortMazePath(ppMaze, n, next, path, minPath);
	}

	path.pop();
}

void TestMaze()
{
	int n = 10;
	int** ppMaze = CreateMaze(n);
	Pos entry = InitMaze(ppMaze, n);
	PrintMaze(ppMaze, n);

	stack<Pos> path, minPath;
	ppMaze[entry.row][entry.col] = 2;
	GetShortMazePath(ppMaze, n, entry, path, minPath);
	//GetMazePath(ppMaze, n, entry, path);
	PrintMaze(ppMaze, n);

	cout<<"minPath:";
	while (!minPath.empty())
	{
		const Pos& pos = minPath.top();
		cout<<"("<<pos.row<<"，"<<pos.col<<")"<<"<-";
		minPath.pop();
	}

	cout<<"Entry"<<endl;
}