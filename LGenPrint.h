#include <cassert>
#include <iostream>
#include <string>
#include <WINDOWS.H>
#include <CONIO.H>
using namespace std;

/*************** cursor settings ***************/

void getwinxy(int& row, int& col) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	col = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	row = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
void getxy(int& x,int& y) {
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bInfo);
	y = bInfo.dwCursorPosition.X;
	x = bInfo.dwCursorPosition.Y;
}
void gotoxy(int x,int y) {
	COORD pos= {y,x};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
void HideCursor() {
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle,&CursorInfo);
	CursorInfo.bVisible=false;
	SetConsoleCursorInfo(handle,&CursorInfo);
}
void ShowCursor() {
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle,&CursorInfo);
	CursorInfo.bVisible=true;
	SetConsoleCursorInfo(handle,&CursorInfo);
}

/*************** color settings ***************/

void setcolor(string col) {
	if(col=="red") cout<<"\033[1;31m";
	else if(col=="green") cout<<"\033[1;32m";
	else if(col=="blue") cout<<"\033[34m";
	else if(col=="yellow") cout<<"\033[1;33m";
	else if(col=="purple") cout<<"\033[1;35m";
	else if(col=="cyan") cout<<"\033[1;36m";
	else if(col=="white") cout<<"\033[1m";
	else if(col=="grey") cout<<"\033[1;30m";
	else if(col=="brown") cout<<"\033[33m";
	else if(col=="lblue") cout<<"\033[1;34m";
	else cout<<"\033[0m";
}
void SETCOLOR(string col) {
	if(col=="red") cout<<"\033[0m\033[1;31;41m";
	else if(col=="green") cout<<"\033[0m\033[1;32;41m";
	else if(col=="blue") cout<<"\033[0m\033[34;41m";
	else if(col=="yellow") cout<<"\033[0m\033[1;33;41m";
	else if(col=="purple") cout<<"\033[0m\033[1;35;41m";
	else if(col=="cyan") cout<<"\033[0m\033[1;36;41m";
	else if(col=="white") cout<<"\033[0m\033[1;41m";
	else if(col=="grey") cout<<"\033[0m\033[1;30;41m";
	else if(col=="brown") cout<<"\033[0m\033[33;41m";
	else if(col=="lblue") cout<<"\033[0m\033[1;34;41m";
	else cout<<"\033[0m\033[;;41m";
}
void resetcolor() {cout<<"\033[0m";}

/*************** actual printing ***************/

enum screenPlace {sLeft,sCenter,sRight}; 

void prTxtFrom(int stx,int sty,string pText) {
	gotoxy(stx,sty);
	cout<<pText<<flush;
	return ;
}

inline void toNxtLine() {int x,y; getxy(x,y); gotoxy(x+1,y);}
inline void toPreLine() {int x,y; getxy(x,y); gotoxy(x-1,y);}
inline void toSpeLine(int nx) {int x,y; getxy(x,y); gotoxy(nx,y);}
inline void printText(screenPlace sPlace,string pText,int pos=0) {
	int x,y; getxy(x,y);
	int wx,wy; getwinxy(wx,wy);
	switch(sPlace) {
		case sLeft: assert(pos>=0); prTxtFrom(x,pos,pText); break;
		case sRight: assert(pos>=0); prTxtFrom(x,wy-pText.length()-pos,pText); gotoxy(x,y); break;
		case sCenter: {
			prTxtFrom(x,(wy>>1)-(pText.length()>>1)+pos,pText);
			break;
		}
	}
}

