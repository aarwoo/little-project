#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<windows.h>
#include<conio.h>
#define max_width (100)
#define max_height (25)
const COORD max_pos={.X=max_width,.Y=max_height};
char screen_mapping[max_width][max_height];
bool eq_pos(COORD x,COORD y){
	return (x.X==y.X)&&(x.Y==y.Y);
}
void set_pos_attr(COORD pos,WORD attributes){
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle,pos);
	SetConsoleTextAttribute(handle,attributes);
	return;
}
void print_title(size_t node_size,size_t _max_node_size){
	char tmp[256];
	snprintf(tmp,sizeof(tmp),"Snake [%u/%u]",node_size,_max_node_size);
	SetConsoleTitle(tmp);
	return;
}
void print_char(char ch,COORD pos,WORD attributes){
	set_pos_attr(pos,attributes);
	putchar(ch);
	screen_mapping[pos.X][pos.Y]=ch;
	return;
}
#define max_node_size (max_width*max_height)
typedef struct{
	COORD node[max_node_size+1];
	COORD node_move;
	size_t node_size;
}snake;
COORD adjust_node(COORD node){
	return (COORD){.X=(node.X==-1)?(max_pos.X-1):((node.X==max_pos.X)?(0):(node.X)),
				   .Y=(node.Y==-1)?(max_pos.Y-1):((node.Y==max_pos.Y)?(0):(node.Y))};
}
void quit(char * msg);
void snake_move(snake * ps,COORD * food_pos){
	if((ps!=NULL)&&(food_pos!=NULL)&&(eq_pos(ps->node_move,(COORD){.X=0,.Y=0})==false)){
		memmove(ps->node+1,ps->node+0,sizeof(COORD)*(ps->node_size));
		ps->node[0]=adjust_node((COORD){.X=ps->node[0].X+ps->node_move.X,
										.Y=ps->node[0].Y+ps->node_move.Y});
		if(eq_pos(ps->node[0],*food_pos)==true){
			ps->node_size=(ps->node_size<max_node_size)?(ps->node_size+1):(ps->node_size);
			print_title(ps->node_size,max_node_size);
			if(ps->node_size==max_node_size){
				quit("You win!");
			}else{
				/*PASS*/
			}
			*food_pos=(COORD){.X=rand()%max_pos.X,.Y=rand()%max_pos.Y};
		}else if(screen_mapping[ps->node[0].X][ps->node[0].Y]=='#'){
			quit("You lose!");
		}else{
			/*PASS*/
		}
		print_char(' ',ps->node[ps->node_size],FOREGROUND_GREEN|FOREGROUND_INTENSITY);
		print_char('#',ps->node[0],FOREGROUND_GREEN|FOREGROUND_INTENSITY);
		print_char('#',*food_pos,FOREGROUND_GREEN|FOREGROUND_INTENSITY);
		return;
	}else{
		return;
	}
}
const DWORD std_sleep=100;
#define up  (72)
#define down  (80)
#define left  (75)
#define right  (77)
COORD get_node_move(){
	static COORD node_move={.X=0,.Y=0};
	int ch;
	if(_kbhit()==true){
		ch=_getch();
		if(ch==0xE0){
			ch=_getch();
			node_move=(COORD){.X=(ch==left)?(-1):((ch==right)?(+1):(0)),
						  	  .Y=(ch==up)?(-1):((ch==down)?(+1):(0))};
			return node_move;
		}else{
			node_move=(COORD){.X=0,.Y=0};
			return node_move;
		}
	}else{
		Sleep(std_sleep);
		return node_move;
	}
}
unsigned long long cputime() {
	unsigned long long msr;
	__asm__ __volatile__("rdtsc"
	                     : "=A" (msr));
	return msr;
}
void hide_cursor() {
	CONSOLE_CURSOR_INFO cursor_info = {10, FALSE};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void show_cursor() {
	CONSOLE_CURSOR_INFO cursor_info = {10, TRUE};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void init(size_t node_size,COORD snake_pos,COORD food_pos) {
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(handle,(COORD){.X=max_pos.X+1,.Y=max_pos.Y});
	SMALL_RECT rc={.Left=0,.Top=0,.Right=max_pos.X,.Bottom=max_pos.Y};
	SetConsoleWindowInfo(handle,true,&rc);
	hide_cursor();
	srand(cputime());
	memset(screen_mapping,0,sizeof(screen_mapping));
	system("cls");
	print_char('#',snake_pos,FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	print_char('#',food_pos,FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	print_title(node_size,max_node_size);
	return;
}
void quit(char * msg){
	if(msg!=NULL){
		MessageBox(NULL,msg,"Notice",MB_OK);
	}else{
		/*PASS*/
	}
	show_cursor();
	exit(0);
}
int main(){
	COORD food_pos=(COORD){.X=rand()%max_pos.X,.Y=rand()%max_pos.Y};
	COORD tmp={.X=0,.Y=0};
	snake sk={.node[0]=(COORD){.X=rand()%max_pos.X,.Y=rand()%max_pos.Y},.node_move=tmp,.node_size=1};
	init(sk.node_size,sk.node[0],food_pos);
	while(true){
		sk.node_move=get_node_move();
		snake_move(&sk,&food_pos);
	}
}
