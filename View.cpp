#include <windows.h>
#include <iostream>
#include <conio.h>
using namespace std;

#define BOARD_SIZE 12 //Kích thước ma trận bàn cờ
#define LEFT 3 //Tọa độ trái màn hình bàn cờ
#define TOP 1 //Tọa độ trên màn hình bàn cờ

extern struct _POINT { int x, y, c; }; //x: tọa độ dòng, y: tọa độ cột, c: đánh dấu
extern _POINT _A[BOARD_SIZE][BOARD_SIZE]; //Ma trận bàn cờ
extern bool _TURN; //true là lượt người thứ nhất và false là lượt người thứ hai
extern int _COMMAND; //Biến nhận giá trị phím người dùng nhập
extern int _X, _Y; //Tọa độ hiện hành trên màn hình bàn cờ

/*Hàm cố định màn hình*/
void FixConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

/*Hàm di chuyển con trỏ màn hình tới tọa độ (x,y)*/
void GotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ChangeBackgrColor()
{
	system("color F0");
}

/*0 = Black      8 = Gray
1 = Blue       9 = Light Blue
2 = Green      10 = Light Green
3 = Aqua       11 = Light Aqua
4 = Red        12 = Light Red
5 = Purple     13 = Light Purple
6 = Yellow     14 = Light Yellow
7 = White   15 = Bright White
*/
void SetColor(int backgound_color, int text_color)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	int color_code = backgound_color * 16 + text_color;
	SetConsoleTextAttribute(hStdout, color_code);
}

int ProcessFinish(int pWhoWin)
{
	GotoXY(0, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 2); //Nhảy tới vị trí thích hợp để in chuỗi thắng/thua/hòa
	switch (pWhoWin)
	{
	case -1:
		cout << "Nguoi choi 1 da thang";
		break;
	case 1:
		cout << "Nguoi choi 2 da thang";
		break;
	case 0:
		cout << "Hòa";
		break;
	case 2:
		_TURN = !_TURN; //Đổi lượt nếu không có gì xảy ra
	}
	GotoXY(_X, _Y); //Trả về vị trí hiện hành của con trỏ màn hình bàn cờ
	return pWhoWin;
}

/*Hàm nhận phím quyết định có tiếp tục hay không*/
int AskContinue()
{
	GotoXY(0, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 4);
	cout << "Nhan phim \"y\" de tiep tuc hoac \"N\" de dung tro choi";
	return toupper(_getch());
}

/*Hàm vẽ 1 cái box*/
void DrawBox(int x,int y, int w, int h)
{
	if (w <= 1 || h<=1 || w % 2 != 0 || h % 2 != 0)
		return;
	GotoXY(x, y);
	cout << char(201);
	GotoXY(x, y + h);
	cout << char(200);
	for (int i = 1; i < w; i++)
	{
		GotoXY(x + i, y);
		cout << char(205);
		GotoXY(x + i, y + h);
		cout << char(205);
	}
	GotoXY(x + w, y);
	cout << char(187);
	GotoXY(x + w, y + h);
	cout << char(188);
	for (int j = 1; j < h; j++)
	{
		GotoXY(x, y + j);
		cout << char(186);
		GotoXY(x + w, y + j);
		cout << char(186);
	}
}

/*Hàm thêm chữ vào chính giữa box*/
void TextBox(int x,int y,int w,int h,string s)
{
	int length = s.size();
	GotoXY(x + (w - length) / 2 + 1, y + h / 2 );
	cout << s;
}

/*Tạo một khối Highlight có chiều cao h(hướng xuống từ y), chiều rộng w(hướng sang phải từ x)*/
void HighLight(int x, int y,int w,int h,int color)
{
	SetColor(color, color);
	for(int i=x;i<x+w;i++)
		for (int j = y; j < y + h; j++)
		{
			GotoXY(i, j);
			cout << " ";
		}
}

void DrawStartBox(int x,int y,int w,int h,int b_color,int t_color)
{
	HighLight(x, y, w, h, b_color);
	SetColor(b_color, t_color);
	DrawBox(x, y, w, h);
	TextBox(x, y, w, h, "START");
}

void DrawRuleBox(int x, int y, int w, int h,int b_color,int t_color)
{
	SetColor(b_color, t_color);
	DrawBox(x, y, w, h);
	TextBox(x, y, w, h, "RULE");
}

void DrawMenu(int x,int y,int w,int h)
{
	DrawStartBox(x, y, w, h,14,0);
	DrawRuleBox(x, y+1+h, w, h,15,0);
}

void DrawBoard(int pSize)
{
	for (int i = 0; i <= pSize; i++)
	{
		for (int j = 0; j <= pSize; j++)
		{
			if ((i == 0 && j == 0))
			{
				GotoXY(LEFT + 4 * i, TOP + 2 * j);
				cout << char(218) << char(196) << char(196) << char(196);
				GotoXY(LEFT + 4 * i, TOP + (2 * j) + 1);
				cout << char(179);
			}
			// duong duoi
			else if ((i == pSize && j == 0))
			{
				GotoXY(LEFT + 4 * i, TOP + 2 * j);
				cout << char(191);
				GotoXY(LEFT + 4 * i, TOP + (2 * j) + 1);
				cout << char(179);
			}
			// goc trai duoi
			else if ((i == 0 && j == pSize))
			{
				GotoXY(LEFT + 4 * i, TOP + 2 * j);
				cout << char(192) << char(196) << char(196) << char(196);
			}
			// goc phai duoi
			else if ((i == pSize && j == pSize))
			{
				GotoXY(LEFT + 4 * i, TOP + 2 * j);
				cout << char(217);
			}
			//duong tren
			else if ((i != 0 && j == 0) && (i != pSize && j == 0))
			{
				GotoXY(LEFT + 4 * i, TOP + 2 * j);
				cout << char(194) << char(196) << char(196) << char(196);
				GotoXY(LEFT + 4 * i, TOP + (2 * j) + 1);
				cout << char(179);
			}
			// duong duoi
			else if ((i != pSize && j == pSize) && (i != 0 && j == pSize))
			{
				GotoXY(LEFT + 4 * i, TOP + 2 * j);
				cout << char(193) << char(196) << char(196) << char(196);
			}
			// ben trai
			else if (i == 0 && j != pSize)
			{
				GotoXY(LEFT + 4 * i, TOP + 2 * j);
				cout << char(195) << char(196) << char(196) << char(196);
				GotoXY(LEFT + 4 * i, TOP + (2 * j) + 1);
				cout << char(179);
			}
			else if (i == pSize && j != pSize)
			{
				GotoXY(LEFT + 4 * i, TOP + 2 * j);
				cout << char(180);
				GotoXY(LEFT + 4 * i, TOP + (2 * j) + 1);
				cout << char(179);
			}
			else
			{
				GotoXY(LEFT + 4 * i, TOP + 2 * j);
				cout << char(197) << char(196) << char(196) << char(196);
				GotoXY(LEFT + 4 * i, TOP + (2 * j) + 1);
				cout << char(179);
			}
		}
	}
	GotoXY(_X + 0, _Y + 0);
	HighLight(_X - 1, _Y, 3, 1, 14);
	GotoXY(_X + 0, _Y + 0);
}
