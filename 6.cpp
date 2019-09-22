#include<iostream>        //��һ���棨9���� 
#include<queue>   
#define X 9
#define N 3    //����x�� 
#define M 3    //����y�� 
using namespace std;
int grid[9][9];
struct node
{
	int row;
	int col;
	int value;
	int sign;     //sign=1��ȷ����=0δȷ�� 
	int v[10]={0};
}no[81];       //no[?]:  ?=9*x+y

void count(int x,int y)
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

void init(int x,int y,int vv)   //ɨ�跽Բ������²��� ,ע��vv����Ϊ0 
{
	for(int i=0;i<X;i++)
	{
		no[X*x+i].v[vv]=1;   //��Ϊ���ɺ�ѡ״̬��1�� 
		no[X*i+y].v[vv]=1;
	}
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
	
	for(int i=0;i<X;i++)
	{
		count(i,y);
		count(x,i);
	}
	for(int i=xs;i<xs+N;i++)
	{
		for(int j=ys;j<ys+M;j++)
		{
			count(i,j);
		}
	}
}

void reset(int x)                        //�������ã����ڶ��ʹ�� 
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

int main()
{
	queue<struct node>q;
	struct node *p;
	p=new node;
	int re;
	cin>>re;
	while(re)
	{
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
					init(i,j,no[X*i+j].value);
					no[X*i+j].sign=1;           
				}
				else  no[X*i+j].sign=0;   //Ϊ0�Ĳ����� 
					
			}
		}                                    //��ʼ������ 
	
		for(int i=0;i<X;i++)
		{
			for(int j=0;j<X;j++)
			{
				if(no[X*i+j].sign==0)
				{
					count(i,j);
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
				
			init(p->row,p->col,no[X*(p->row)+p->col].value);
			
			for(int i=0;i<X;i++)                          //ÿ�θ��º�����ͳ����������
			{
				for(int j=0;j<X;j++)
				{
					if(no[X*i+j].sign==0)
					{
						count(i,j);            
						if(no[X*i+j].v[0]==1)
						{
							q.push(no[X*i+j]);          //��μ�����У� 
						}
					}
				}
			} 
			
		}
		cout<<endl;
		
		for(int i=0;i<X;i++)                 //��� 
		{
			for(int j=0;j<X;j++)
			{
				cout<<no[X*i+j].value<<" ";
			}
			cout<<endl;
		}	
		cout<<endl;	
		re--;
	}
	
}
