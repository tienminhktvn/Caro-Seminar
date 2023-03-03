#include <iostream>
#include <stdlib.h>
#include <conio.h>
using namespace std;

#define BOARD_SIZE 12 //Kích thước ma trận bàn cờ
#define LEFT 3 //Tọa độ trái màn hình bàn cờ
#define TOP 1 //Tọa độ trên màn hình bàn cờ

//Khai báo kiểu dữ liệu
struct _POINT { int x, y, c; }; //x: tọa độ dòng, y: tọa độ cột, c: đánh dấu
_POINT _A[BOARD_SIZE][BOARD_SIZE]; //Ma trận bàn cờ
bool _TURN; //true là lượt người thứ nhất và false là lượt người thứ hai
int _COMMAND; //Biến nhận giá trị phím người dùng nhập
int _X, _Y; //Tọa độ hiện hành trên màn hình bàn cờ

//Hàm View
void FixConsoleWindow();
int ProcessFinish(int pWhoWin);
int AskContinue();
//Hàm Control
void StartGame();
void ExitGame();
void MoveRight();
void MoveLeft();
void MoveUp();
void MoveDown();
//Hàm Model
int CheckBoard(int pX, int pY);
int TestBoard();

void main()
{
	FixConsoleWindow();
	StartGame();
	bool validEnter = true;
	while (1)
	{
		_COMMAND = toupper(_getch());
		if (_COMMAND == 27)
		{
			ExitGame();
			return;
		}
		else
		{
			if (_COMMAND == 'A' || _COMMAND == 75) MoveLeft();
			else if (_COMMAND == 'W') MoveUp();
			else if (_COMMAND == 'S') MoveDown();
			else if (_COMMAND == 'D') MoveRight();
			else if (_COMMAND == 13) //Nhấn Enter
			{
				switch(CheckBoard(_X, _Y))
				{
				case -1:
					cout << "X";
					break;
				case 1:
					cout << "O";
					break;
				case 0:
					validEnter = false; //Khi đánh vào ô đã đánh rồi
				}
				//Kiểm tra và xử lý thắng thua
				if (validEnter == true)
				{
					switch (ProcessFinish(TestBoard()))
					{
					case -1:
					case 1:
					case 0:
						if (AskContinue() != 'Y')
						{
							ExitGame();
							return;
						}
						else
							StartGame();
					}
				}
				validEnter = true; //Mở khóa
			}
		}
	}
}