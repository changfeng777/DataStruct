/******************************************************************************************
Copyright (c) Bit Software, Inc.(2013), All rights reserved.

Purpose: 栈的使用单链表的适配器模式实现    

Author: 迷宫实现

Created Time: 2015-8-1
******************************************************************************************/
#pragma once

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

bool Maze(int** ppMaze, int n, const Pos& entry, Stack<Pos>& path)
{
	assert(entry.col < n && entry.row < n);
	
	Pos cur = entry;
	ppMaze[cur.row][cur.col] = 2;
	path.Push(cur);

	while (!path.Empty())
	{
		 Pos next = path.Top();
		
		 //
		 // 出口在最后一行
		 //
		 if (next.row == n-1)
		 {
			 return true;
		 }

		 // 上
		 next.row -= 1;
		 if (CheckIsAccess(ppMaze, n, next))
		 {
			ppMaze[next.row][next.col] = 2;
			path.Push(next);
			continue;
		 }

		 // 右
		 next = path.Top();
		 next.col += 1;
		 if (CheckIsAccess(ppMaze, n, next))
		 {
			 ppMaze[next.row][next.col] = 2;
			 path.Push(next);
			 continue;
		 }

		 // 下
		 next = path.Top();
		 next.row += 1;
		 if (CheckIsAccess(ppMaze, n, next))
		 {
			 ppMaze[next.row][next.col] = 2;
			 path.Push(next);
			 continue;
		 }

		 // 左
		 next = path.Top();
		 next.col -= 1;
		 if (CheckIsAccess(ppMaze, n, next))
		 {
			 ppMaze[next.row][next.col] = 2;
			 path.Push(next);
			 continue;
		 }

		 Pos tmp = path.Top();
		 ppMaze[tmp.row][tmp.col] = 3;
		 path.Pop();
	}

	return false;
}

void TestMaze()
{
	int n = 10;
	int** ppMaze = CreateMaze(n);
	Pos entry = InitMaze(ppMaze, n);
	PrintMaze(ppMaze, n);

	Stack<Pos> path;
	Maze(ppMaze, n, entry, path);
	PrintMaze(ppMaze, n);

	cout<<"Path:";
	while (!path.Empty())
	{
		const Pos& pos = path.Top();
		cout<<"("<<pos.row<<"，"<<pos.col<<")"<<"<-";
		path.Pop();
	}

	cout<<"Entry"<<endl;
}