#include"pch.h"
#include<iostream>           //加强版，含3 4 5 6 8 9宫 
#include<stdlib.h>
#include<queue>
#pragma warning(disable : 4996)
using namespace std;
int grid[9][9];
int re;
int X;
FILE* fp = NULL;
FILE* fq = NULL;
int check(int x, int y, int vv, int X)   //扫描方圆几里，更新参数 ,注意vv不可为0 
{
	int N = 0;
	int M = 0;
	switch (X)
	{
	case 9:
	{
		N = 3; M = 3; break;
	}
	case 8:
	{
		N = 4; M = 2; break;
	}
	case 6:
	{
		N = 2; M = 3; break;
	}
	case 4:
	{
		N = 2; M = 2; break;
	}
	case 3:case 5:case 7:
	{
		N = 0; M = 0; break;
	}
	}

	for (int i = 0; i < X; i++)
	{
		if (grid[x][i] == vv || grid[i][y] == vv) return 0;   //有相同的就返回check失败 
	}

	if (M == 0 && N == 0) return 1;

	int xs, ys;
	xs = x / N * N;
	ys = y / M * M;
	for (int i = xs; i < xs + N; i++)
	{
		for (int j = ys; j < ys + M; j++)
		{
			if (grid[i][j] == vv) return 0;
		}
	}
	return 1;
}

void reset(int X)
{
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < X; j++)
		{
			grid[i][j] = 0;
		}
	}
}

void dfs(int x, int y, int X)
{
	if (x == X)
	{
		for (int i = 0; i < X; i++)
		{
			for (int j = 0; j < X; j++)
			{
				fprintf(fq, "%d ", grid[i][j]);
			}
			fprintf(fq, "\n");
		}
		return;
	}
	if (grid[x][y] == 0)
	{
		for (int i = 1; i <= X; i++)
		{
			if (check(x, y, i, X) == 1)
			{
				grid[x][y] = i;
				dfs(x + (y + 1) / X, (y + 1) % X, X);
			}
		}
		grid[x][y] = 0;//前面循环未找到最优解，则回溯 
	}
	else dfs(x + (y + 1) / X, (y + 1) % X, X);
}

int main(int argc, char* argv[])
{
	string inputname;                //命令行输入处理 
	string outputname;
	string a, b, c, d;
	a = "-m";
	b = "-n";
	c = "-i";
	d = "-o";
	for (int i = 1; i < argc; i++)
	{
		if (argv[i] == c)
		{
			fp = fopen(argv[++i], "r");     //以文本方式打开文件。
			if (fp == NULL)               //打开文件出错
			{
				cout << "Input not found.\n" << endl;
				return 0;
			}
			continue;
		}
		if (argv[i] == d)
		{
			fq = fopen(argv[++i], "w");     //以文本方式打开文件。
			if (fq == NULL)               //打开文件出错
			{
				cout << "Output not found.\n" << endl;
				return 0;
			}
			continue;
		}
		if (argv[i] == a)
		{
			X = argv[++i][0] - '0';
			continue;
		}
		if (argv[i] == b)
		{
			re = argv[++i][0] - '0';
			continue;
		}
	}


	while (re)
	{
		reset(X);
		for (int i = 0; i < X; i++)
		{
			for (int j = 0; j < X; j++)
			{
				fscanf_s(fp, "%d", &grid[i][j]);
			}
		}

		dfs(0, 0, X);

		fprintf_s(fq, "\n");
		re--;
	}
	if (fp != NULL)   fclose(fp);
	if (fq != NULL)  fclose(fq);
	return 0;
}