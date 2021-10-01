#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;
#ifndef BUTTON_CLASS
#define BUTTON_CLASS
void rgb_init()
{
	HANDLE hIn=GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwInMode,dwOutMode;
	GetConsoleMode(hIn,&dwInMode);
	GetConsoleMode(hOut,&dwOutMode);
	dwInMode|=0x0200;
	dwOutMode|=0x0004;
	SetConsoleMode(hIn,dwInMode);
	SetConsoleMode(hOut,dwOutMode);
}
void rgb_dec()
{
	HANDLE hIn=GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwInMode,dwOutMode;
	GetConsoleMode(hIn,&dwInMode);
	GetConsoleMode(hOut,&dwOutMode);
	dwInMode&=~0x0200;
	dwOutMode&=~0x0004;
	SetConsoleMode(hIn,dwInMode);
	SetConsoleMode(hOut,dwOutMode);
}
void rgb_set(int fr,int fg,int fb,int br,int bg,int bb)
{
	rgb_init();
	printf("\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm",fr,fg,fb,br,bg,bb);
	rgb_dec();
}
void pos(int y,int x)
{
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
struct Colour
{
	int r;
	int g;
	int b;
	string hex;
	/***BASIC FUNCTIONS***/
	char GETBASEDIGIT(int x)
	{
		if(x>=0&&x<=9) return char(x+'0');
		else return (x-10+'A'); 
	}
	int GETDECDIGIT(char x)
	{
		if(x>='0'&&x<='9') return x-'0';
		else return x-'A'+10; 
	}
	string toHEX(int R,int G,int B)
	{
		string s;
		while(R)
		{
			s=GETBASEDIGIT(R%16)+s;
			R/=16;
		}
		while(G)
		{
			s=GETBASEDIGIT(G%16)+s;
			G/=16;
		}
		while(B)
		{
			s=GETBASEDIGIT(B%16)+s;
			B/=16;
		}
		return s;
	}
	string loadHEX()
	{
		hex=toHEX(r,g,b);
	}
	string getHEX()
	{
		loadHEX();
		return hex;
	}
	/*********************/
};
class BUTTONCLASS
{
	public:
		/***BUTTON ATTRIBUTES***/
		Colour Foreground,Background;
		Colour highlightinfoF,highlightinfoB;
		string text;
		int sx,sy,ex,ey,length,height;
		/***********************/
		/***BUTTON Display***/
		void ShowButton()//Show the button
		{
			rgb_set(Foreground.r,Foreground.g,Foreground.b,Background.r,Background.g,Background.b);
			pos(sx,sy);
			for(int i=sx;i<=ex;i++)
			{
				pos(i,sy);
				for(int j=sy;j<=ey;j++)
				{
					putchar(' ');
				}
			}
			pos(sx,sy);
			cout << text;
			pos(0,0);
			rgb_set(242,242,242,0,0,0);
		}
		void HideButton(int fr,int fg,int fb,int br,int bg,int bb)//Hide the button
		{
			rgb_set(fr,fg,fb,br,bg,bb);
			pos(sx,sy);
			for(int i=sx;i<=ex;i++)
			{
				pos(i,sy);
				for(int j=sy;j<=ey;j++)
				{
					putchar(' ');
				}
			}
			pos(0,0);
			rgb_set(242,242,242,0,0,0);
		}
		void HighLight()//Highlight the button
		{
			int fr=highlightinfoF.r,fg=highlightinfoF.g,fb=highlightinfoF.b,br=highlightinfoB.r,bg=highlightinfoB.g,bb=highlightinfoB.b;
			rgb_set(fr,fg,fb,br,bg,bb);
			pos(sx,sy);
			for(int i=sx;i<=ex;i++)
			{
				pos(i,sy);
				for(int j=sy;j<=ey;j++)
				{
					putchar(' ');
				}
			}
			pos(sx,sy);
			cout << text;
			pos(0,0);
			rgb_set(242,242,242,0,0,0);
		}
		void LowLight()//Lowlight the button
		{
			rgb_set(Foreground.r,Foreground.g,Foreground.b,Background.r,Background.g,Background.b);
			pos(sx,sy);
			for(int i=sx;i<=ex;i++)
			{
				pos(i,sy);
				for(int j=sy;j<=ey;j++)
				{
					putchar(' ');
				}
			}
			pos(sx,sy);
			cout << text;
			pos(0,0);
			rgb_set(242,242,242,0,0,0);
		}
		/*****************/
		/***BUTTON INITIALIZE***/
		void SetBasicButtonINFO(int Sx,int Sy,int Ex,int Ey,int Fr,int Fg,int Fb,int Br,int Bg,int Bb)
		{
			sx=Sx,sy=Sy,ex=Ex,ey=Ey;
			Foreground={Fr,Fg,Fb};
			Background={Br,Bg,Bb};
		}
		void SetBasicButtonINFO(int Sx,int Sy,int Ex,int Ey,Colour F,Colour B)
		{
			sx=Sx,sy=Sy,ex=Ex,ey=Ey;
			Foreground=F;
			Background=B;
		}
		void SetHighlightINFO(Colour F,Colour C)//Set button highlight infomation
		{
			highlightinfoF.r=C.r;
			highlightinfoF.g=C.g;
			highlightinfoF.b=C.b;
			highlightinfoB.r=F.r;
			highlightinfoB.g=F.g;
			highlightinfoB.b=F.b;
		}
		void SetHighlightINFO(int Fr,int Fg,int Fb,int Br,int Bg,int Bb)
		{
			highlightinfoF.r=Fr;
			highlightinfoF.g=Fg;
			highlightinfoF.b=Fb;
			highlightinfoB.r=Br;
			highlightinfoB.g=Bg;
			highlightinfoB.b=Bb;
		}
		/***********************/
		/***HIGLIGHT JUDGEMENTS***/
		bool MouseOver(int x,int y)//Whether the cursor is over the button
		{
			if(x>=sx&&y>=sy&&x<=ex&&y<=ey) return true;
			return false;
		}
		void ConditionalHighlight(bool F)//Used in FOR cycles for conditional highlight
		{
			if(F)
			{
				HighLight();
			}
			else LowLight();
		}
		/*************************/
};
bool TESTTHIS()
{
	INPUT_RECORD inRec;
	DWORD res;
	while(1)
	{
		pos(0,0);
		rgb_set(0,0,255,127,127,127);
		cout << "   ARE YOU OK?   ";
		BUTTONCLASS buttonOK,buttonNO;
		buttonOK.SetBasicButtonINFO(1,0,1,7,0,255,0,242,242,242);
		buttonOK.SetHighlightINFO(0,255,0,100,100,100);
		buttonOK.text="   OK";
		buttonOK.ShowButton();
		buttonNO.SetBasicButtonINFO(1,9,1,16,255,0,0,242,242,242);
		buttonNO.SetHighlightINFO(255,0,0,100,100,100);
		buttonNO.text="   NO";
		buttonNO.ShowButton();
		bool f;
		HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
		while(1)
		{
			ReadConsoleInput(hInput, &inRec, 1, &res);
			if(inRec.EventType == MOUSE_EVENT)
			{
				int x=inRec.Event.MouseEvent.dwMousePosition.Y;
				int y=inRec.Event.MouseEvent.dwMousePosition.X;
				buttonOK.ConditionalHighlight(buttonOK.MouseOver(x,y));
				buttonNO.ConditionalHighlight(buttonNO.MouseOver(x,y));
				if(inRec.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED)
				{
					if(buttonOK.MouseOver(x,y)) f=1;
					else if(buttonNO.MouseOver(x,y)) f=0;
					goto JUDGEMENT;
				}
			}
		}
		JUDGEMENT:;
		if(f)
		{
			pos(3,0);
			cout << "Oh... Erm OK.                   ";
		}
		else
		{
			pos(3,0);
			cout << "Hope that things can get better.";
		}
	}
	return 0;
}
#endif
