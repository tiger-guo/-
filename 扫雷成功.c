#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

#define ESC 27

char qipan[81][81],mine[81][81]={0};int grade[9]={0};
int y,x;
int width,mine_num,n;

void Pos(int x,int y);
void creatqipan();
void init_start();
void show();
void play_now();
int judge();
void blank();
void game();
void show_start();
void game_end();
void creatmine();
void success_judge();
void game_success();

void success_judge()
{
	int count=0;
	for(y=0;y<=2*n+1;y++)
	{
		for(x=0;x<=3*n;x++)
			if(qipan[y][x]=='@'||qipan[y][x]=='#')
				count++;
	}
	if(count==mine_num)
		game_success();
}

void init_start()												//��Ϸ��ʼ��
{
	show_start();
	Pos(0,14);
	printf("                                  ����һ�������ε��������ӣ���������ѡ����������ӵı߳���");
	scanf("%d",&width);			   //			shang 72
	printf("                                               ������������ĵ��׸�����");
	scanf("%d",&mine_num);
	n=width-1;
	system("cls");
	creatmine();
	creatqipan();
}

void show_start()
{
	char ch;
	Pos(0,14);
	printf("                                                 ����һ��ɨ����Ϸ\n");
	printf("                                       ��ʼ��Ϸ������ո񣬽�����Ϸ������ESC:");
	while(1)
	{
		ch=getch();
		if(ch==32)
		{
			system("cls");
			break;
		}
		if(ch==ESC)
		{
			system("cls");
			exit(1);
		}
	}
}


void creatmine()//   1 1 2 2 ��BUG��
{
	int i,j,count;
	srand(time(NULL));
	count=0;
	while(count<mine_num)
	{
		j=2*(rand()%n);
		i=3*(rand()%n);
		mine[j][i]=42;
		count=0;
		for(j=0;j<=2*n;j++)
		{
			for(i=0;i<=3*n;i++)
			{
				if(mine[j][i]==42)
					count++;
			}
		}
	}
}


int judge(int num,int y,int x)															//�ж�����
{
	if(mine[y][x]==42)
		num++;
	return num;
}
                                                                               //  ����
void blank(int y,int x)
{
	if(qipan[y][x]=='@')
	{
	int num=0;
	if(mine[y][x]==42)
		game_end();
	if(x-3>=0)
		num=judge(num,y,x-3);
	if(x+3<=3*n)
		num=judge(num,y,x+3);
	if(y-2>=0)
		num=judge(num,y-2,x);
	if(y+2<=2*n)
		num=judge(num,y+2,x);
	if(x-3>=0&&y-2>=0)
		num=judge(num,y-2,x-3);
	if(x-3>=0&&y+2<=2*n)
		num=judge(num,y+2,x-3);
	if(x+2<=3*n&&y-2>=0)
		num=judge(num,y-2,x+3);
	if(x+3<=3*n&&y+2<=2*n)
		num=judge(num,y+2,x+3);
	grade[num]++;
	
	if(num!=0)
		qipan[y][x]=num+48;
	else
		qipan[y][x]=32;

	if(num==0)
	{
		if(x-3>=0)
			blank(y,x-3);
		if(x+3<=3*n)
			blank(y,x+3);
		if(y-2>=0)
			blank(y-2,x);
		if(y+2<=2*n)
			blank(y+2,x);
	}
	
	}
	success_judge();
}


void judge2(int y,int x)
{
	if(mine[y][x]=='*')
	{
		if(qipan[y][x]!='#')
			game_end();
	}
	else
		blank(y,x);


}

void quickmine(int y,int x)
{
	if(x-3>=0)
		judge2(y,x-3);
	if(x+3<=3*n)
		judge2(y,x+3);
	if(y-2>=0)
		judge2(y-2,x);
	if(y+2<=2*n)
		judge2(y+2,x);
	if(x-3>=0&&y-2>=0)
		judge2(y-2,x-3);
	if(x-3>=0&&y+2<=2*n)
		judge2(y+2,x-3);
	if(x+2<=3*n&&y-2>=0)
		judge2(y-2,x+3);
	if(x+3<=3*n&&y+2<=2*n)
		judge2(y+2,x+3);
}





void main()
{
	init_start();					//#############################################################
	play_now();						//#############################################################
}

void game_success()
{
	int i;
	float all_grade=0,cishu=0;
	for(y=0;y<=2*n+1;y++)
	{
		for(x=0;x<=3*n;x++)
			if(mine[y][x]=='*')
				qipan[y][x]='*';
	}
	system("cls");
	show();
	Pos(60,11);
	printf("                YOU SUCCEED!");
	Pos(60,14);
	for(i=0;i<9;i++)
	{
		cishu+=grade[i];
		all_grade+=i*grade[i];
	}
	if(cishu==0)
		printf("              ��ķ���Ϊ:0");
	else
		printf("              ��ķ���Ϊ:%.2f",all_grade/cishu);
	Pos(60,16);
	printf("             ���س���������Ϸ��");
	getchar();getchar();
	system("cls");
	exit(1);
}

void game_end()
{
	int i,j;
	float all_grade=0,cishu=0;
	for(j=0;j<=2*n;j++)
		{
			for(i=0;i<=3*n;i++)
			{
				if(mine[j][i]==42)
					qipan[j][i]=mine[j][i];
			}
		}
	system("cls");
	show();
	Pos(60,11);
	printf("                GAME OVER");
	Pos(60,14);
	for(i=0;i<9;i++)
	{
		cishu+=grade[i];
		all_grade+=i*grade[i];
	}
	if(cishu==0)
		printf("              ��ķ���Ϊ:0");
	else
		printf("              ��ķ���Ϊ:%.2f",all_grade/cishu);
	Pos(60,16);
	printf("             ���س���������Ϸ��");
	getchar();getchar();
	system("cls");
	exit(1);
}





void creatqipan()												//��������
{
	for(y=0;y<=2*n+1;y++)
		for(x=0;x<=3*n;x++)
			qipan[y][x]=32;
	for(y=0;y<=2*n;y+=2)
		for(x=0;x<=3*n;x+=3)
			qipan[y][x]=64;
	qipan[1][0]=94;
	show();
	Pos(60,10);
	printf("       '%c'����ָ꣩���'%c'���㵱ǰѡ�еĸ��ӣ�   ",94,64);
	Pos(60,11);
	printf("�����ͨ��'��'��'��'��'��'��'��'�ƶ�λ��,�ո񷭿����ָ���");
	Pos(60,12);
	printf(" ���ӣ�ͨ��˫��'Y'����ǹ��ָ��ĸ��ӣ�˫��'N'��������ı�");
	Pos(60,13);
	printf("               �ǣ�˫��'B'�����п������ײ�����");
	Pos(60,15);
	printf("                      ��Ϸ��ʼ��\n");
	Pos(60,16);
	printf("                  ������Ĳ���ָ� ");	
}
void show()														//show����
{
	for(y=0;y<=2*n+1;y++)
	{
		Pos(0,y+1);
		for(x=0;x<=3*n;x++)
			printf("%c",qipan[y][x]);
	}
}



void play_now()													//��ʼ����Ϸ
{
	int i,j;
	char ch;
	i=0,j=1;
	while(1)
	{
		qipan[j][i]=32;
		while(1)
		{
			ch=getch();
			ch=getch();
			if(ch==72&&j!=1)
			{	
				j-=2;
				break;
			}
			if(ch==75&&i!=0)
			{
				i-=3;
				break;
			}
			if(ch==77&&i!=3*n)
			{
				i+=3;
				break;
			}
			if(ch==80&&j!=2*n+1)
			{
				j+=2;
				break;
			}
			if(ch==ESC)
			{
				exit(1);
			}
			if(qipan[j-1][i]!=32&&!(qipan[j-1][i]>48&&qipan[j-1][i]<58))
			{
				if(ch==89||ch==121)			//#################���##############################
				{
					qipan[j-1][i]='#';
					break;
				}
				if(ch==78||ch==110)
				{
					qipan[j-1][i]='@';
					break;
				}
			}
			if(qipan[j-1][i]>'0'&&qipan[j-1][i]<'9')//#############��������####################################
			{
				if(ch=='B'||ch=='b')
					quickmine(j-1,i);
			}                                  
			if(ch==32)						//#########################����#####################
			{
				blank(j-1,i);
/*				cishu++;
				j-=1;
				grade+=fen;
				if(fen!=0)
				{
					qipan[j][i]=fen+48;
				}
				else
					qipan[j][i]=32;
				j+=1;*/
				break;
			}
		}
		qipan[j][i]=94;
		system("cls");
		show();
		Pos(25,0);
		printf("������                                            ������");
		Pos(55,22);
		printf("    ��");
		Pos(55,24);
		printf("��  ��  ��");
		Pos(50,26);
		printf("  ������Ĳ���ָ�");
	}
}







































void Pos(int x,int y)
{
	COORD pos;
	HANDLE hOutput;
	pos.X=x;
	pos.Y=y;
	hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput,pos);

}