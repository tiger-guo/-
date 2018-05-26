#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>

#define ESC 27
char qipan[81][81],mine[81][81],book[81][81]={0};
int n,mine_num;                                         //n 是棋盘边长

void game_init();
void create_chessboard();
void show_chessboard();
void create_mineboard();
void game_play();
void quick_mine();
void blank(int x,int y);
void game_end(); 
void game_success();
/*##############################################游戏初始化##################################*/ 
void game_init()
{
	create_chessboard();
	create_mineboard();
//	show_mineboard();
//	show_chessboard();
}

void create_chessboard()
{
	int length,i,j;
	printf("The length of chessboard:");
	scanf("%d",&length);
	n=length;
	for(i=0;i<=n;i++)
		for(j=0;j<=n;j++)
		{
			qipan[i][j]='@';
			mine[i][j]='0';
		}
}

void create_mineboard()
{
	int next[8][2]={{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
	int i,j,x,y,tx,ty,count=0;
	srand(time(NULL));
	printf("\nThe number of mine:");
	scanf("%d",&mine_num);

	for(j=1;j<=mine_num;j++)
	{
		x=1+rand()%n;
		y=1+rand()%n;
		if(mine[x][y]=='*')
		{
			j--;
			count++;
			continue;
		}
		mine[x][y]='*';
		for(i=0;i<8;i++)  
		{
			tx=x+next[i][0];
			ty=y+next[i][1];
			if(mine[tx][ty]=='*'||tx<1||tx>n||ty<1||ty>n)
				continue;
			mine[tx][ty]++;
		}
	}
}

void show_chessboard()
{
	int i,j;
	system("cls");
	for(j=0;j<=n;j++)
		printf("%-4d",j);
	printf("\n");
	for(i=1;i<=n;i++)
	{
		for(j=0;j<=n;j++)
		{
			if(j==0)
			{
				printf("%-4d",i);
				continue;
			}
			printf("%-4c",qipan[i][j]);
		}
		printf("\n");
	}
}

void show_mineboard()
{
	int i,j;
	system("cls");
	for(j=0;j<=n;j++)
		printf("%-4d",j);
	printf("\n");
	for(i=1;i<=n;i++)
	{
		for(j=0;j<=n;j++)
		{
			if(j==0)
			{
				printf("%-4d",i);
				continue;
			}
			printf("%-4c",mine[j][i]);
		}
		printf("\n");
	}
}

//###################################开始游戏######################################################## 
void game_play()
{
	int x,y;
	char ch;
	while(1)
	{
		show_chessboard();
		printf("                输入坐标（输入格式为 x[纵坐标],y[横坐标]）:");
		scanf("%d,%d",&x,&y);
		printf("            'b'→双击翻牌 'y'→标记 'n'→取消标记 'm'→快速排雷\n"); 
		printf("                             输入操作指令：");
		ch=getch();
		if(ch==ESC)
			game_end();
		if(ch=='b'||ch=='B')
			blank(x,y);
		if(ch=='y'||ch=='Y')
		{
			if(qipan[x][y]=='@')
				qipan[x][y]='#';
			else
			{
				printf("输入的指令有误，重新输入！");
				Sleep(500);
			}
		}
		if(ch=='n'||ch=='N')
		{
			if(qipan[x][y]=='#')
				qipan[x][y]='@';
			else
			{		
				printf("输入的指令有误，重新输入！");
				Sleep(500); 
			}
		}
		if(ch=='m'||ch=='M')
			quick_mine(x,y);
		game_success();
	}
}

void quick_mine(int x,int y)
{
	int next[8][2]={{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
	int k,tx,ty;
	for(k=0;k<8;k++)
	{
		tx=x+next[k][0];
		ty=y+next[k][1];
		if(mine[tx][ty]=='*')
			if(qipan[tx][ty]!='#')
				game_end();
		else
			qipan[tx][ty]=mine[tx][ty];
		if(qipan[tx][ty]=='0')
			qipan[tx][ty]=0;
		 
	}
	
}
void blank(int x,int y)
{
	int next[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
	int k,tx,ty;
	if(mine[x][y]=='*')
		game_end();
	if(mine[x][y]!='0')
	{
		qipan[x][y]=mine[x][y];
		return;
	}
	qipan[x][y]=0;
	for(k=0;k<=3;k++)
	{
		tx=x+next[k][0];
		ty=y+next[k][1];
		if(tx<1||tx>n||ty<1||ty>n)
			continue;
		if(book[tx][ty]==0)
		{
			book[tx][ty]=1;
			blank(tx,ty);	
		}
	}
	return;
}
//####################################游戏结束与成功################################### 
void game_end()
{
	int i,j; 
	float cishu=0,grade=0;
	//    显示雷的位置 
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			if(mine[i][j]=='*')
				qipan[i][j]=mine[i][j];
				
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			if(qipan[i][j]!='@'||qipan[i][j]!='#'||qipan[i][j]!='*')
				{
					if(qipan[i][j]!=0)
					{
						grade+=qipan[i][j]-'0';
						cishu++;
					}
					else
						cishu++;
				}
	show_chessboard();
	printf("你的分数为%.3f",grade/cishu);
	getchar();getchar();
}
void game_success()
{
	int i,j,count=0; 
	float cishu=0,grade=0;
	//    显示雷的位置 
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			if(qipan[i][j]=='#'||qipan[i][j]=='@')
				count++;
	if(count==mine_num)
	{
		for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			if(mine[i][j]=='*')
				qipan[i][j]=mine[i][j];
				
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			if(qipan[i][j]!='@'||qipan[i][j]!='#'||qipan[i][j]!='*')
				{
					if(qipan[i][j]!=0)
					{
						grade+=qipan[i][j]-'0';
						cishu++;
					}
					else
						cishu++;
				}
	show_chessboard();
	printf("恭喜你获得胜利，你的分数为%.3f",grade/cishu);
	getchar();getchar();
	}
}
int main()
{
	game_init();
	game_play();
	return 0;
}
