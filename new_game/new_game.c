/*Just For Windows*/
#ifndef UNICODE
#define UNICODE
#endif
#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define class_name (L"Window")
#define title (L"new game  1.0")
#define base_rate (0.01)
#define base_mark (0.05)
#define begin_mark (0.5)
#define mov_rate (base_rate)
#define me_mov_rate (mov_rate*1.2)
#define enemy_mov_rate (mov_rate)
#define size_rate (base_rate*3)
#define blood_width_rate (base_rate*2.5)
#define min_rate (0)
#define max_rate (1-size_rate)
#define color_background (RGB(255,255,255))
#define color_blood (RGB(255,0,0))
#define color_text_blood (RGB(255,255,255))
#define color_text_blood_background (color_blood)
#define color_text_info (color_blood)
#define color_win_background (color_blood)
#define color_lose_background (color_blood)
#define color_food (RGB(0,255,0))
#define color_me (RGB(255,255,0))
#define color_enemy (RGB(0,0,255))
#define info_food (L" is food that I should eat to increase my blood.I will win when my blood full.")
#define info_me (L" is me moved by press keys ↑or ↓or ←or →.Now,Press any key to start.Pause when I is stop moving.")
#define info_enemy (L" is enemy that will eat me and discrease my blood.I will lose when my blood empty.")
#define info_win (L"WIN!!!")
#define info_lose (L"LOSE!!!")
#define vertical_spacing_info (size_rate+0.1)
#define exit_pause_ms (5000)
typedef struct{
	double x_rate;
	double y_rate;
}pos_rate;
int is_overlap_pos_rate(pos_rate m,pos_rate n){
	return (fabs(m.x_rate-n.x_rate)<size_rate)&&(fabs(m.y_rate-n.y_rate)<size_rate);
}
double sgn(double x){
	if(x<0){
		return -1;
	}else if(x==0){
		return x;
	}else{
		return 1;
	}
}
double distance_pos_rate(pos_rate x, pos_rate y){
	return sqrt(pow(x.x_rate-y.x_rate,2)+pow(x.y_rate-y.y_rate,2));
}
double efficve_xy_rate(double x){
	if(x<min_rate){
		return min_rate;
	}else if(x<max_rate){
		return x;
	}else{
		return max_rate;
	}
}
double efficve_mark(double x){
	if(x<0){
		return 0;
	}else if(x<1){
		return floor(x/base_mark)*base_mark;
	}else{
		return 1;
	}
}
double rand_base(){
	double ans;
		ans=min_rate+(double)(rand()%((int)((max_rate-min_rate)/base_rate)))*base_rate;
	return ans;
}
pos_rate rand_pos_rate(){
	return (pos_rate){rand_base(),rand_base()};
}
RECT torect_pos_rate(pos_rate p,RECT r){
	RECT ans;
	ans.left=(LONG)(p.x_rate*(r.right-r.left));
	ans.top=(LONG)(p.y_rate*(r.bottom-r.top));
	ans.right=(LONG)((p.x_rate+size_rate)*(r.right-r.left));
	ans.bottom=(LONG)((p.y_rate+size_rate)*(r.bottom-r.top));
	return ans;
}
void paint_rect(HDC hdc,RECT rt,COLORREF color){
	HBRUSH hbr=CreateSolidBrush(color);
	FillRect(hdc,&rt,hbr);
	DeleteObject((HGDIOBJ)(hbr));
	return;
}
void paint_text(HDC hdc,RECT rt,wchar_t * str,COLORREF color__text,COLORREF color__text__background,UINT format){
	SetTextColor(hdc,color__text);
	SetBkColor(hdc,color__text__background);
	HFONT hft=CreateFont((rt.bottom-rt.top),0,0,0,0&FW_BOLD,
	                     FALSE,FALSE,FALSE,
						 DEFAULT_CHARSET,
						 OUT_TT_ONLY_PRECIS,CLIP_DEFAULT_PRECIS,
						 PROOF_QUALITY,DEFAULT_PITCH|FF_MODERN,
						 NULL);
	SelectObject(hdc,hft);
	DrawText(hdc,str,-1,&rt,format);
	DeleteObject((HGDIOBJ)(hft));
	return;
}
void paint_main(HWND hwnd,pos_rate food,pos_rate me,pos_rate enemy,double mark){
	RECT rt,rt_blood;
	HDC hdc = GetDC(hwnd);
	wchar_t str[1024];
	swprintf(str,1024,L"%.3lg%%",mark*100);
	GetClientRect(hwnd,&rt);
	rt_blood=(RECT){.left=0,.top=0,
				    .right=mark*(rt.right-rt.left),.bottom=blood_width_rate*(rt.bottom-rt.top)};
	paint_rect(hdc,rt,color_background);
	paint_rect(hdc,rt_blood,color_blood);
	paint_text(hdc,rt_blood,str,color_text_blood,color_text_blood_background,
			   DT_SINGLELINE|DT_VCENTER|DT_CENTER|DT_NOCLIP);
	paint_rect(hdc,torect_pos_rate(food,rt),color_food);
	paint_rect(hdc,torect_pos_rate(me,rt),color_me);
	paint_rect(hdc,torect_pos_rate(enemy,rt),color_enemy);
    ReleaseDC(hwnd,hdc);
    return;
}
void paint_welcome_info(HDC hdc,pos_rate p,RECT rt,wchar_t * info_text,COLORREF color_info){
	RECT t=torect_pos_rate(p,rt);
	paint_rect(hdc,t,color_info);
	paint_text(hdc,(RECT){.left=t.right,.top=t.top,.right=t.right,.bottom=t.bottom},
	           info_text,color_text_info,color_background,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_NOCLIP);
	return;
}
void paint_welcome(HWND hwnd){
	RECT rt;
	HDC hdc = GetDC(hwnd);
	GetClientRect(hwnd,&rt);
	paint_rect(hdc,rt,color_background);
	paint_welcome_info(hdc,(pos_rate){.x_rate=0.1,.y_rate=0.5-vertical_spacing_info},rt,info_food,color_food);
	paint_welcome_info(hdc,(pos_rate){.x_rate=0.1,.y_rate=0.5},rt,info_me,color_me);
	paint_welcome_info(hdc,(pos_rate){.x_rate=0.1,.y_rate=0.5+vertical_spacing_info},rt,info_enemy,color_enemy);
	ReleaseDC(hwnd,hdc);
}
void paint_win(HWND hwnd){
	RECT rt;
	HDC hdc = GetDC(hwnd);
	GetClientRect(hwnd,&rt);
	paint_rect(hdc,rt,color_background);
	paint_text(hdc,(RECT){.left=rt.left,.top=(rt.bottom-rt.top)*0.3,
		            	  .right=rt.right,.bottom=(rt.bottom-rt.top)*0.7},
			   info_win,color_text_info,color_background,DT_SINGLELINE|DT_VCENTER|DT_CENTER|DT_NOCLIP);
	ReleaseDC(hwnd,hdc);
	Sleep(exit_pause_ms);
}
void paint_lose(HWND hwnd){
	RECT rt;
	HDC hdc = GetDC(hwnd);
	GetClientRect(hwnd,&rt);
	paint_rect(hdc,rt,color_background);
		paint_text(hdc,(RECT){.left=rt.left,.top=(rt.bottom-rt.top)*0.3,
		            	  .right=rt.right,.bottom=(rt.bottom-rt.top)*0.7},
			   info_lose,color_text_info,color_background,DT_SINGLELINE|DT_VCENTER|DT_CENTER|DT_NOCLIP);
	ReleaseDC(hwnd,hdc);
	Sleep(exit_pause_ms);
}
void try_exit(HWND hwnd,double mark){
	if(mark==0){
		paint_lose(hwnd);
		DestroyWindow(hwnd);
	}else if(mark==1){
		paint_win(hwnd);
		DestroyWindow(hwnd);
	}else{
		return;
	}
}
LRESULT WndProc(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp) {
	static pos_rate food;
	static pos_rate me;
	static pos_rate enemy;
	static double mark=begin_mark;
	static int is_boot=1; 
switch(msg){
case WM_CREATE:{
	srand(time(NULL));
	do{
	food=rand_pos_rate();
	me=rand_pos_rate();
	enemy=rand_pos_rate();
	}while(is_overlap_pos_rate(food,me)||is_overlap_pos_rate(food,enemy)||
		   is_overlap_pos_rate(me,enemy));
	SetFocus(hwnd);
	break;
}
case WM_SIZING:{
	if(is_boot==1){
		paint_welcome(hwnd);
	}else{
		paint_main(hwnd,food,me,enemy,mark);
	}
	SetFocus(hwnd);
	break;
}
case WM_SIZE:{
	if(is_boot==1){
		paint_welcome(hwnd);
	}else{
		paint_main(hwnd,food,me,enemy,mark);
	}
	SetFocus(hwnd);
	break;
}
case WM_KEYDOWN:{
	switch(wp){
		case VK_UP:{
			me.y_rate=efficve_xy_rate(me.y_rate-me_mov_rate);
			break;
		}
		case VK_DOWN:{
			me.y_rate=efficve_xy_rate(me.y_rate+me_mov_rate);
			break;
		}
		case VK_RIGHT:{
			me.x_rate=efficve_xy_rate(me.x_rate+me_mov_rate);
			break;
		}
		case VK_LEFT:{
			me.x_rate=efficve_xy_rate(me.x_rate-me_mov_rate);
			break;
		}
		default:{
			/*PASS*/
			break;
		}
	}
	is_boot=0; 
	if(!is_overlap_pos_rate(me,enemy)){
		double x=efficve_xy_rate(enemy.x_rate+sgn(me.x_rate-enemy.x_rate)*enemy_mov_rate);
		double y=efficve_xy_rate(enemy.y_rate+sgn(me.y_rate-enemy.y_rate)*enemy_mov_rate);
		if(distance_pos_rate(me,(pos_rate){x,enemy.y_rate})<
		   distance_pos_rate(me,(pos_rate){enemy.x_rate,y})){
		enemy.x_rate=x;
		}else{
		enemy.y_rate=y; 
		}
	}else{
		/*Pass*/
	}
	paint_main(hwnd,food,me,enemy,mark);
	if(is_overlap_pos_rate(food,me)){
		mark=efficve_mark(mark+base_mark);
		while(is_overlap_pos_rate(food,me)||is_overlap_pos_rate(food,enemy)){
			food=rand_pos_rate();
		}
	}else{
		/*Pass*/
	}
	if(is_overlap_pos_rate(me,enemy)){
		mark=efficve_mark(mark-base_mark);
		while(is_overlap_pos_rate(me,enemy)||is_overlap_pos_rate(food,enemy)){
			enemy=rand_pos_rate();
		}
	}else{
		/*Pass*/
	}
	paint_main(hwnd,food,me,enemy,mark);
	try_exit(hwnd,mark);
	break;
}
case WM_DESTROY:{
	/*UnregisterHotKey(hwnd,idis(1));*/
	PostQuitMessage(0);
	break;
}
default:{
	return DefWindowProc(hwnd,msg,wp,lp);
}
}
return 0;
}
int WINAPI WinMain(HINSTANCE hinstance,HINSTANCE prevhinctance,LPSTR lpcmdline,int ncmdline) {
	WNDCLASS wc;
	HWND hwnd;
	MSG msg;
	memset(&wc,0,sizeof(wc));
	wc.lpszClassName=class_name;
	wc.hInstance=hinstance;
	wc.lpfnWndProc=WndProc;
	RegisterClass(&wc);
	hwnd=CreateWindowEx(0,class_name,title,WS_VISIBLE|WS_OVERLAPPEDWINDOW,
	                    CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
	                    NULL,NULL,hinstance,NULL);
	if(hwnd==NULL) {
		/*PASS*/
	} else {
		while(GetMessage(&msg,NULL,0,0)>0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return 0;
}
