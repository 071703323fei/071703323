#include"pch.h"
#include<iostream>           //加强版，含3 4 5 6 8 9宫 
#include<stdlib.h>
#include<queue>
using namespace std;
int grid[9][9];
int re;
int X;
struct node
{
	int row;
	int col;
	int value;
	int sign;     //sign=1已确定，=0未确定 
	int v[10] = { 0 };
}no[81];

void count(int x, int y, int X)
{
	no[X * x + y].v[0] = 0;
	for (int i = 1; i <= X; i++)
	{
		if (no[X * x + y].v[i] == 0)  //可候选个数 
		{
			no[X * x + y].v[0]++;
		}
	}
}

void init(int x, int y, int vv, int X)   //扫描方圆几里，更新参数 ,注意vv不可为0 
{
	int N;
	int M;
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
		no[X * x + i].v[vv] = 1;   //改为不可候选状态（1） 
		no[X * i + y].v[vv] = 1;
	}

	for (int i = 0; i < X; i++)
	{
		count(i, y, X);
		count(x, i, X);
	}

	if (M == 0 && N == 0) return;

	int xs, ys;
	xs = x / N * N;
	ys = y / M * M;
	for (int i = xs; i < xs + N; i++)
	{
		for (int j = ys; j < ys + M; j++)
		{
			no[X * i + j].v[vv] = 1;
		}
	}

	for (int i = xs; i < xs + N; i++)
	{
		for (int j = ys; j < ys + M; j++)
		{
			count(i, j, X);
		}
	}
}

void reset(int X)
{
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < X; j++)
		{
			grid[i][j] = 0;
			no[X * i + j].value = 0;
			no[X * i + j].sign = 0;
			for (int k = 0; k < 10; k++)
			{
				no[X * i + j].v[k] = 0;
			}
		}
	}
}

void fun(int X)
{
	queue<struct node>q;
	struct node* p;
	p = new node;

	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < X; j++)
		{
			if (no[X * i + j].value != 0)   //非0数更新同行、列、宫 
			{
				init(i, j, no[X * i + j].value, X);
				no[X * i + j].sign = 1;
			}
			else  no[X * i + j].sign = 0;

		}
	}                                    //初始化表盘 

	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < X; j++)
		{
			if (no[X * i + j].sign == 0)
			{
				count(i, j, X);
				if (no[X * i + j].v[0] == 1)      //所有空格加入队列，后续逐一填上并更新状态 
				{
					q.push(no[X * i + j]);
				}
			}
		}
	}                               //最初的统计

	while (q.empty() != 1)
	{
		*p = q.front();
		q.pop();
		if (p->sign == 1) continue;
		for (int i = 1; i <= X; i++)
		{
			if (no[X * (p->row) + p->col].v[i] == 0)
			{
				no[X * (p->row) + p->col].value = i;
				no[X * (p->row) + p->col].sign = 1;
			}
		}

		init(p->row, p->col, no[X * (p->row) + p->col].value, X);

		for (int i = 0; i < X; i++)
		{
			for (int j = 0; j < X; j++)
			{
				if (no[X * i + j].sign == 0)
				{
					count(i, j, X);
					if (no[X * i + j].v[0] == 1)
					{
						q.push(no[X * i + j]);
					}
				}
			}
		}
	}
}

int main(int argc, char* argv[])
{
	FILE* fp;
	fp = NULL;
	FILE* fq;
	fq = NULL;
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
				no[X * i + j].row = i;
				no[X * i + j].col = j;
				no[X * i + j].value = grid[i][j];
			}
		}

		fun(X);

		for (int i = 0; i < X; i++)
		{
			for (int j = 0; j < X; j++)
			{
				fprintf_s(fq, "%d ", no[X * i + j].value);
			}
			fprintf_s(fq, "\n");
		}
		fprintf_s(fq, "\n");
		re--;
	}
	if (fp != NULL)   fclose(fp);
	if (fq != NULL)  fclose(fq);
	return 0;
}