#include<iostream>           //��ǿ�棬��3 4 5 6 8 9�� 
#include<queue>
using namespace std;
int grid[9][9];
struct node
{
	int row;
	int col;
	int value;
	int sign;     //sign=1��ȷ����=0δȷ�� 
	int v[10]={0};
}no[81];       //no[?]:?=9*x+y

void count(int x,int y,int X)
{
	no[X*x+y].v[0]=0;
	for(int i=1;i<=X;i++)
	{
		if(no[X*x+y].v[i]==0)  //�ɺ�ѡ���� 
		{
			no[X*x+y].v[0]++;
		}
	}
}

void init(int x,int y,int vv,int X)   //ɨ�跽Բ������²��� ,ע��vv����Ϊ0 
{
	int N;
	int M;
	switch(X)
	{
		case 9:
		{
			N=3;M=3;break;
		}
		case 8:
		{
			N=4;M=2;break;
		}
		case 6:
		{
			N=2;M=3;break;
		}
		case 4:
		{
			N=2;M=2;break;
		}
		case 3:case 5:case 7:
		{
			N=0;M=0;break;
		}
	}
	
	for(int i=0;i<X;i++)
	{
		no[X*x+i].v[vv]=1;   //��Ϊ���ɺ�ѡ״̬��1�� 
		no[X*i+y].v[vv]=1;
	}
	
	for(int i=0;i<X;i++)
	{
		count(i,y,X);
		count(x,i,X);
	}
	
	if(M==0&&N==0) return ;
	
	int xs,ys;
	xs=x/N*N;
	ys=y/M*M;
	for(int i=xs;i<xs+N;i++)
	{
		for(int j=ys;j<ys+M;j++)
		{
			no[X*i+j].v[vv]=1;
		}
	}
	
	for(int i=xs;i<xs+N;i++)
	{
		for(int j=ys;j<ys+M;j++)
		{
			count(i,j,X);
		}
	}
}

void reset(int X)
{
	for(int i=0;i<X;i++)
	{
		for(int j=0;j<X;j++)
		{
			grid[i][j]=0;
			no[X*i+j].value=0;
			no[X*i+j].sign=0;
			for(int k=0;k<10;k++)
			{
				no[X*i+j].v[k]=0;
			}
		}
	}
} 

void fun(int X)
{
	queue<struct node>q;
	struct node *p;
	p=new node;
		reset(X);
		for(int i=0;i<X;i++)
		{
			for(int j=0;j<X;j++)
			{
				cin>>grid[i][j];
				no[X*i+j].row=i;
				no[X*i+j].col=j;
				no[X*i+j].value=grid[i][j];
			}
		}
	
		for(int i=0;i<X;i++)
		{
			for(int j=0;j<X;j++)
			{
				if(no[X*i+j].value!=0)   //��0������ͬ�С��С��� 
				{
					init(i,j,no[X*i+j].value,X);
					no[X*i+j].sign=1;           
				}
				else  no[X*i+j].sign=0;
					
			}
		}                                    //��ʼ������ 
	
		for(int i=0;i<X;i++)
		{
			for(int j=0;j<X;j++)
			{
				if(no[X*i+j].sign==0)
				{
					count(i,j,X);
					if(no[X*i+j].v[0]==1)      //���пո������У�������һ���ϲ�����״̬ 
					{
						q.push(no[X*i+j]);
					}
				}
			}
		}                               //�����ͳ��
		
		
		
		     
		while(q.empty()!=1)
		{
			*p=q.front();
			q.pop();
			if(p->sign==1) continue;
			for(int i=1;i<=X;i++)
			{
				if(no[X*(p->row)+p->col].v[i]==0)
				{
					no[X*(p->row)+p->col].value=i;
					no[X*(p->row)+p->col].sign=1;
				}
			}
			
			init(p->row,p->col,no[X*(p->row)+p->col].value,X);
			
			for(int i=0;i<X;i++)
			{
				for(int j=0;j<X;j++)
				{
					if(no[X*i+j].sign==0)
					{
						count(i,j,X);
						if(no[X*i+j].v[0]==1)
						{
							q.push(no[X*i+j]);
						}
					}
				}
			} 
			
		}
		cout<<endl;
		
		for(int i=0;i<X;i++)
		{
			for(int j=0;j<X;j++)
			{
				cout<<no[X*i+j].value<<" ";
			}
			cout<<endl;
		}	
}

int main()
{

	int re;
	int X;
	cin>>re;    //reΪ��������XΪ���� 
	cin>>X;
	while(re)
	{
		fun(X);
		cout<<endl;	
		re--;
	}
	
}
