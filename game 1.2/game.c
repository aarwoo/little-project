#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#define printme() printf("█")
#define cleanme() printf("  ")
#define intcputime() ((int)cputime())
#define randnum(a) randnum_base(0,a)
#define flag(a) ((a<0)?(-1):(1))
#define load(x,y) load_base(&(x),&(y))
#define up  (72)
#define down  (80)
#define left  (75)
#define right  (77)
#define stop   ' '
#define size_width (80)
#define size_height (25)
#define bgc (15)
#define mec (12)
#define bjc (9)
#define fdc (13)
#define tdc (6)
#define ycd (10)
#define title_size (500)
#define version "1.2"
int foodx=0,foody=0,tdx=0,tdy=0,mark=0,goal=0,mode=1;
char title[title_size];
/*
对应的颜色码表：
0 = 黑色       8 = 灰色
1 = 蓝色       9 = 淡蓝色
2 = 绿色       10 = 淡绿色
3 = 浅绿色     11 = 淡浅绿色
4 = 红色       12 = 淡红色
5 = 紫色       13 = 淡紫色
6 = 黄色       14 = 淡黄色
7 = 白色       15 = 亮白色
*/
unsigned long long cputime() {
	unsigned long long msr;
	__asm__ __volatile__("rdtsc"
	                     : "=A" (msr));
	return msr;
}
void setcolor(unsigned short ForeColor,unsigned short BackGroundColor) {
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);//获取当前窗口句柄
	SetConsoleTextAttribute(handle,ForeColor|(BackGroundColor<<4));//设置颜色
}
void conreset() {
	char tmp[24]="Game";
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleTitle(title,title_size);
	SetConsoleTitle(tmp);
	COORD size = {size_width, size_height};
	SetConsoleScreenBufferSize(hOut,size);
	SMALL_RECT rc = {0,0, size_width-1, size_height-1};
	SetConsoleWindowInfo(hOut,true,&rc);
	return;
}
void gotoxy(int x,int y) {
	COORD c;
	c.X=x;
	c.Y=y;
	SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE),c);
}
void hidecursor() {
	CONSOLE_CURSOR_INFO cursor_info = {10, 0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void showcursor() {
	CONSOLE_CURSOR_INFO cursor_info = {10, 1};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void unload(char * msg) {
	setcolor(7,0);
	system("cls");
	SetConsoleTitle(title);
	gotoxy(0,0);
	showcursor();
	printf(msg);
	Sleep(5000);
	exit(0);
}
void fullprint() {
	int a=(size_width)*(size_height);
	while(a--)
		putchar(' ');
}
void printbj() {
	int x=0,y=0;
	setcolor(bgc,bjc);
	fullprint();
	setcolor(bjc,bgc);
	for(x=0; x<=size_width-3; x++) {
		for(y=0; y<=size_height-1; y++) {
			gotoxy(x,y);
			putchar(' ');
		}
	}
	return;
}
int randnum_base(int _min,int _max) {
	srand(intcputime());
	return ((rand()%(_max-_min+1))+_min);
}
void rand_food(int x,int y) {
	setcolor(fdc,bgc);
	gotoxy(foodx,foody);
	cleanme();
	while((foodx==x&&foody==y)||(foodx==tdx&&foody==tdy)) {
		foodx=(randnum((size_width-4)>>1))<<1;
		foody=(randnum(size_height-1)>>1)<<1;
	}

	gotoxy(foodx,foody);
	printme();
	setcolor(mec,bgc);
	return;
}
void tdmove(int x,int y) {
	int dx=x-tdx,dy=y-tdy;
	switch(mode) {
		case 1:
			break;
		case 2:
			srand(time(NULL));
			if((rand()%10)>4)
				return;
			break;
		case 3:
			if(randnum(9)>4)
				return;
			break;
		case 4:
			if(abs(dx)>2&&abs(dy)>2)
				return;
			break;
		case 5:
			return;
			break;
	}
	gotoxy(tdx,tdy);
	cleanme();
	if(abs(dx)>abs(dy)&&dx!=0&&dy!=0) {
		tdx+=flag(dx)*2;
	}
	if(abs(dy)>abs(dx)&&dx!=0&&dy!=0) {
		tdy+=flag(dy)*2;
	}
	if(dx==0&&dy!=0) {
		tdy+=flag(dy)*2;
	}
	if(dy==0&&dx!=0) {
		tdx+=flag(dx)*2;
	}
	setcolor(tdc,bgc);
	gotoxy(tdx,tdy);
	printme();
	if(tdx==x&&tdy==y) {
		Sleep(1000);
		unload("Oh!\nYou were eaten!");
	}
	if(tdx==foodx&&tdx==foody) {
		rand_food(x,y);
	}
	setcolor(mec,bgc);
	return;
}
int load_base(int *x,int *y) {
	conreset();
	printf("Game version %s\nDesigned by 101011100a\n",version);
	setcolor(mec,0);
	printme();
	setcolor(7,0);
	puts(" : Youself.\n");
	setcolor(fdc,0);
	printme();
	setcolor(7,0);
	printf(" : Food, eating it will increase the mark. [note:mark type:int]\n\n");
	setcolor(tdc,0);
	printme();
	setcolor(7,0);
	printf(" : Natural enemy will eat you.\n\n");
	setcolor(bjc,0);
	printme();
	setcolor(7,0);
	printf(" : Boundary line.\n\n");
	printf("Press 0 ~ 9 to change speed.\nPress direction key to change direction.\nPress space key to stop.\n");
	printf("You goal=");
	scanf("%d",&goal);
	printf("Choose mode:\n1 Very Hard\n2 Hard\n3 Normal\n4 Easy\n5 Very Easy\nNOTE:Press other key will enter Very Hard mode.\nChoose:");
	scanf("%d",&mode);
	if(mode<1&&mode>5)
		mode=1;
	printf("Press any key to continue.");
	_getch();
	system("cls");
	hidecursor();
	printbj();
	*x=(randnum((size_width-4)>>1))<<1;
	*y=(randnum(size_height-1)>>1)<<1;
	foodx=*x;
	foody=*y;
	tdx=*x;
	tdy=*y;
	rand_food(*x,*y);
	setcolor(tdc,bgc);
	while((tdx==(*x)&&tdy==(*y))||(tdx==foodx&&tdy==foody)) {
		tdx=(randnum((size_width-4)>>1))<<1;
		tdy=(randnum(size_height-1)>>1)<<1;
	}
	gotoxy(tdx,tdy);
	printme();
	setcolor(mec,bgc);
	gotoxy(*x,*y);
	printme();
}
int main() {
	char tmp[10000];
	int x=0,y=0,dx=0,dy=0,sr,ssd=200,ts=0;
	load(x,y);
	while(1) {
		sprintf(tmp,"Game mark=%d goal=%d your speed=%d ms/move",mark,goal,ssd);
		SetConsoleTitle(tmp);
		if(_kbhit()) {
			if((sr=_getch())==224)
				sr=_getch();
		} else {
			Sleep(ssd);
		}
		switch(sr) {
			case up:
				dx=0;
				dy=-2;
				break;
			case down:
				dx=0;
				dy=2;
				break;
			case left:
				dx=-2;
				dy=0;
				break;
			case right:
				dx=2;
				dy=0;
				break;
			case stop:
				dx=0;
				dy=0;
				break;
		}
		if(sr>='0'&&sr<='9') {
			ssd=(sr-'0')*100;
		}
		if((dx!=0||dy!=0)&&(x+dx)>=0&&(x+dx)<=(size_width-3)&&(y+dy)>=0&&(y+dy)<=(size_height-1)) {
			gotoxy(x,y);
			cleanme();
			x+=dx;
			y+=dy;
			if(x==foodx||y==foody) {
				if(ts==0) {
					setcolor(ycd,bgc);
					gotoxy(x,y);
					printme();
					gotoxy(foodx,foody);
					printme();
					Sleep(50);
					setcolor(fdc,bgc);
					gotoxy(foodx,foody);
					printme();
					setcolor(mec,bgc);
					gotoxy(x,y);
					printme();
					ts=1;
				} else {
					gotoxy(x,y);
					printme();
				}
			} else {
				gotoxy(x,y);
				printme();
				ts=0;
			}
			if(x==foodx&&y==foody) {
				putchar('\a');
				mark++;
				if(mark==goal) {
					Sleep(1000);
					unload("Game Over!\nYou Win!");
				}
				rand_food(x,y);
			}
			if(x==tdx&&y==tdy) {
				unload("OMG!\nYou killed youself.");
			}
		}
		if(dx!=0||dy!=0)
			tdmove(x,y);
	}
	return 0;
}
