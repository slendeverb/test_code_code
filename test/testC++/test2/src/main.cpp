/**
此程序识别的为LR(0)语法分析器
文法为：
(0) S'->S
(1) S->aRST
(2) S->aR
(3) R->+
(4) T->b
识别的输入语句为：a+a+b
如有其它文法和输入语句,大体程序不用改，只需修改部分数字，重新构造action表与goto表即可使用。
*/
#include<stdio.h>
#include<malloc.h>
#define OK 1
#define ERROR 0
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define X 8
#define Y1 4
#define Y2 3
typedef struct
{
	int *base;
	int *top;
	int stacksize;
}SqStack;
typedef struct
{
	char key;
	int data;
}Array;
typedef Array Action[X][Y1];
typedef Array Goto[X][Y2];
SqStack *StateStack, *SignStack;
int k=0;
char a[]={'a','+','a','+','b','#'};
int Gotofind(int,char,Goto);
void InitActionAndGoto(Action A,Goto G)
{
	/*action表 说明：将规约定在<10的数字，将移进定在>=10的数字*/
	A[0][0].key='a';A[0][1].key='+';A[0][2].key='b';A[0][3].key='#';
	A[0][0].data=2;A[0][1].data=-1;A[0][2].data=-1;A[0][3].data=-1;
	A[1][0].key='a';A[1][1].key='+';A[1][2].key='b';A[1][3].key='#';
	A[1][0].data=-1;A[1][1].data=-1;A[1][2].data=-1;A[1][3].data=0;
	A[2][0].key='a';A[2][1].key='+';A[2][2].key='b';A[2][3].key='#';
	A[2][0].data=-1;A[2][1].data=4;A[2][2].data=-1;A[2][3].data=-1;
	A[3][0].key='a';A[3][1].key='+';A[3][2].key='b';A[3][3].key='#';
	A[3][0].data=2;A[3][1].data=-1;A[3][2].data=20;A[3][3].data=20;
	A[4][0].key='a';A[4][1].key='+';A[4][2].key='b';A[4][3].key='#';
	A[4][0].data=30;A[4][1].data=-1;A[4][2].data=30;A[4][3].data=30;
	A[5][0].key='a';A[5][1].key='+';A[5][2].key='b';A[5][3].key='#';
	A[5][0].data=-1;A[5][1].data=-1;A[5][2].data=7;A[5][3].data=-1;
	A[6][0].key='a';A[6][1].key='+';A[6][2].key='b';A[6][3].key='#';
	A[6][0].data=-1;A[6][1].data=-1;A[6][2].data=10;A[6][3].data=10;
	A[7][0].key='a';A[7][1].key='+';A[7][2].key='b';A[7][3].key='#';
	A[7][0].data=-1;A[7][1].data=-1;A[7][2].data=40;A[7][3].data=40;
    /*goto表*/
	G[0][0].key='S';G[0][1].key='R';G[0][2].key='T';
	G[0][0].data=1;G[0][1].data=-1;G[0][2].data=-1;
	G[1][0].key='S';G[1][1].key='R';G[1][2].key='T';
	G[1][0].data=-1;G[1][1].data=-1;G[1][2].data=-1;
	G[2][0].key='S';G[2][1].key='R';G[2][2].key='T';
	G[2][0].data=-1;G[2][1].data=3;G[2][2].data=-1;
	G[3][0].key='S';G[3][1].key='R';G[3][2].key='T';
	G[3][0].data=5;G[3][1].data=-1;G[3][2].data=-1;
	G[4][0].key='S';G[4][1].key='R';G[4][2].key='T';
	G[4][0].data=-1;G[4][1].data=-1;G[4][2].data=-1;
	G[5][0].key='S';G[5][1].key='R';G[5][2].key='T';
	G[5][0].data=-1;G[5][1].data=-1;G[5][2].data=6;
	G[6][0].key='S';G[6][1].key='R';G[6][2].key='T';
	G[6][0].data=-1;G[6][1].data=-1;G[6][2].data=-1;
	G[7][0].key='S';G[7][1].key='R';G[7][2].key='T';
	G[7][0].data=-1;G[7][1].data=-1;G[7][2].data=-1;
}
int InitStack(SqStack *s)
{
	s->base=(int *)malloc(STACK_INIT_SIZE * sizeof(int));
	if(!s->base)
		return ERROR;
	s->top=s->base;
	s->stacksize=STACK_INIT_SIZE;
	    return OK;
}
template<typename T>
int Push(SqStack *s ,T e)
{
	if((s->top-s->base)>=s->stacksize)
	{
		s->base=(int *) realloc (s->base,(s->stacksize+STACKINCREMENT)*sizeof(int));
		if(!s->base) return ERROR;
		s->top=s->base+s->stacksize;
		s->stacksize+=STACKINCREMENT;
	}
	*s->top++=e;
	return OK;
}
int Pop(SqStack *s)
{
	int e;
	if(s->top==s->base) return ERROR;
	e=*--s->top;
	return OK;
}
int Gettop(SqStack *s)
{
	int e;
	if(s->top!=s->base)
		e=*(s->top-1);
	return e;
}
void Movein(int x,char h,Action A,Goto G,SqStack *StateStack,SqStack *SignStack)
{
	int i,j;
	for(j=0;j<Y1;j++)
	{
		if(A[x][j].key==h)
		{
			if(A[x][j].data<10 && A[x][j].data>0)
			{
				Push(StateStack,A[x][j].data);
				Push(SignStack,h);
				break;
			}
			else if(A[x][j].data==-1)
			{
				printf("不能识别，出错！");
				return;
			}
			else if(A[x][j].data>=10)
			{
				if(A[x][j].data==10)
				{
					for(i=0;i<4;i++)
					{
						Pop(SignStack);
						Pop(StateStack);
					}
                    Push(StateStack,Gotofind(Gettop(StateStack),'S',G));
					Push(SignStack,'S');
					k--;
					break;
				}
				else if(A[x][j].data==20)
				{
					for(i=0;i<2;i++)
					{
						Pop(SignStack);
						Pop(StateStack);
					}
					Push(StateStack,Gotofind(Gettop(StateStack),'S',G));
					Push(SignStack,'S');k--;
					break;
				}
				else if(A[x][j].data==30)
				{
					Pop(SignStack);
					Pop(StateStack);
					Push(StateStack,Gotofind(Gettop(StateStack),'R',G));
					Push(SignStack,'R');
					k--;
					break;
				}
				else
				{
					Pop(SignStack);
					Pop(StateStack);
					Push(StateStack,Gotofind(Gettop(StateStack),'T',G));
					Push(SignStack,'T');
					k--;
					break;
				}
			}
			else
			{
				printf("识别成功!^-^\n");
				return;
			}
		}
	}
	k++;
	Movein(Gettop(StateStack),a[k],A,G,StateStack,SignStack);
}
int Gotofind(int m,char c,Goto G)
{
	int n,dkey;
	for(n=0;n<Y2;n++)
	{
		if(G[m][n].key==c)
		{
			if(G[m][n].data>0)
			{
				dkey=G[m][n].data;
				return dkey;
			}
			else
			{
				printf("识别出错！");
				return 0;
			}
		}
	}
}
int main()
{
	SqStack *StateStack,*SignStack;
	Action A;
	Goto G;
	InitActionAndGoto(A,G);
    StateStack=(SqStack *) malloc (sizeof(SqStack));
	SignStack=(SqStack *) malloc (sizeof(SqStack));
	InitStack(StateStack);
    InitStack(SignStack);
	Push(StateStack,0);
	Push(SignStack,'#');
	Movein(Gettop(StateStack),a[k],A,G,StateStack,SignStack);
}