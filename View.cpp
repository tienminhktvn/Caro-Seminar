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

void DrawBoard(int pSize)
{
	for (int i = 0; i <= pSize; i++)
	{
		for (int j = 0; j <= pSize; j++)
		{
			GotoXY(LEFT + 4 * i, TOP + 2 * j);
			cout << ".";
		}
	}
	GotoXY(LEFT+2, TOP+1);
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