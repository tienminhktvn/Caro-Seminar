#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <string>
using namespace std;

#define BOARD_SIZE 12 //Kích thước ma trận bàn cờ
#define LEFT 3 //Tọa độ trái màn hình bàn cờ
#define TOP 1 //Tọa độ trên màn hình bàn cờ
#define OPTION_HIGH 2
#define OPTION_WIDTH  20

//Khai báo kiểu dữ liệu
struct _POINT { int x, y, c; }; //x: tọa độ dòng, y: tọa độ cột, c: đánh dấu
_POINT _A[BOARD_SIZE][BOARD_SIZE]; //Ma trận bàn cờ
bool _TURN; //true là lượt người thứ nhất và false là lượt người thứ hai
int _COMMAND; //Biến nhận giá trị phím người dùng nhập
int _X, _Y; //Tọa độ hiện hành trên màn hình bàn cờ
struct MENU
{
	string opt1;
	string opt2;
	string opt3;
	string opt4;
};
MENU menu = { "NEW GAME","LOAD GAME","ABOUT","EXIT" };
int _OPTION; //Thứ tự hộp menu
int Score1;
int Score2;
string Player1_name;
string Player2_name;

//Hàm View
void FixConsoleWindow();
int ProcessFinish(int pWhoWin);
void AskContinue();
void GotoXY(int x, int y);
void SetColor(int backgound_color, int text_color);
void HighLight(int x, int y, int w, int h, int color);
void DrawOption(int x, int y, int w, int h, int b_color, int t_color, string s);
void DrawMenu(int x, int y, int w, int h, MENU m);
void Draw_newgame_opt(int x, int y, int w, int h);
void ChangeBackgrColor();
void Hightlight_Play_turn(int x, int y, int w, int h, int color, int player);
//void DrawRule(int x, int y, int w, int h);
//Hàm Control
void StartGame();
void ExitGame();
void MoveRight();
void MoveLeft();
void MoveUp();
void MoveDown();
void MenuUp();
void MenuDown();
//Hàm Model
int CheckTick(int pX, int pY);
int CheckBoard(int pX, int pY);
int TestBoard();
void ResetData();
void Menu();

void main()
{
	FixConsoleWindow();
	ChangeBackgrColor();
	Menu();
	bool validEnter = true;
	while (1)
	{
		_COMMAND = toupper(_getch());
		if (_COMMAND == 27)
		{
			SetColor(15, 0);
			ExitGame();
			return;
		}
		else
		{
			if (_COMMAND == 'A')
			{
				HighLight(_X - 1, _Y, 3, 1, 15);
				GotoXY(_X, _Y);
				if (CheckTick(_X, _Y) == -1)
				{
					SetColor(15, 0);
					cout << "X";
				}
				else if (CheckTick(_X, _Y) == 1)
				{
					SetColor(15, 0);
					cout << "O";
				}
				GotoXY(_X, _Y);
				MoveLeft();
				if (CheckTick(_X, _Y) == 0)
				{
					HighLight(_X - 1, _Y, 3, 1, 14);
					GotoXY(_X, _Y);
				}
				else if (CheckTick(_X, _Y) == -1)
				{
					HighLight(_X - 1, _Y, 3, 1, 14);
					GotoXY(_X, _Y);
					SetColor(14, 0);
					cout << "X";
					GotoXY(_X, _Y);
				}
				else
				{
					HighLight(_X - 1, _Y, 3, 1, 14);
					GotoXY(_X, _Y);
					SetColor(14, 0);
					cout << "O";
					GotoXY(_X, _Y);
				}
			}
			else if (_COMMAND == 'W')
			{
				HighLight(_X - 1, _Y, 3, 1, 15);
				GotoXY(_X, _Y);
				if (CheckTick(_X, _Y) == -1)
				{
					SetColor(15, 0);
					cout << "X";
				}
				else if (CheckTick(_X, _Y) == 1)
				{
					SetColor(15, 0);
					cout << "O";
				}
				GotoXY(_X, _Y);
				MoveUp();
				if (CheckTick(_X, _Y) == 0)
				{
					HighLight(_X - 1, _Y, 3, 1, 14);
					GotoXY(_X, _Y);
				}
				else if (CheckTick(_X, _Y) == -1)
				{
					HighLight(_X - 1, _Y, 3, 1, 14);
					GotoXY(_X, _Y);
					SetColor(14, 0);
					cout << "X";
					GotoXY(_X, _Y);
				}
				else
				{
					HighLight(_X - 1, _Y, 3, 1, 14);
					GotoXY(_X, _Y);
					SetColor(14, 0);
					cout << "O";
					GotoXY(_X, _Y);
				}
			}
			else if (_COMMAND == 'S')
			{
				HighLight(_X - 1, _Y, 3, 1, 15);
				GotoXY(_X, _Y);
				if (CheckTick(_X, _Y) == -1)
				{
					SetColor(15, 0);
					cout << "X";
				}
				else if (CheckTick(_X, _Y) == 1)
				{
					SetColor(15, 0);
					cout << "O";
				}
				GotoXY(_X, _Y);
				MoveDown();
				if (CheckTick(_X, _Y) == 0)
				{
					HighLight(_X - 1, _Y, 3, 1, 14);
					GotoXY(_X, _Y);
				}
				else if (CheckTick(_X, _Y) == -1)
				{
					HighLight(_X - 1, _Y, 3, 1, 14);
					GotoXY(_X, _Y);
					SetColor(14, 0);
					cout << "X";
					GotoXY(_X, _Y);
				}
				else
				{
					HighLight(_X - 1, _Y, 3, 1, 14);
					GotoXY(_X, _Y);
					SetColor(14, 0);
					cout << "O";
					GotoXY(_X, _Y);
				}
			}
			else if (_COMMAND == 'D')
			{
				HighLight(_X - 1, _Y, 3, 1, 15);
				GotoXY(_X, _Y);
				if (CheckTick(_X, _Y) == -1)
				{
					SetColor(15, 0);
					cout << "X";
				}
				else if (CheckTick(_X, _Y) == 1)
				{
					SetColor(15, 0);
					cout << "O";
				}
				GotoXY(_X, _Y);
				MoveRight();
				if (CheckTick(_X, _Y) == 0)
				{
					HighLight(_X - 1, _Y, 3, 1, 14);
					GotoXY(_X, _Y);
				}
				else if (CheckTick(_X, _Y) == -1)
				{
					HighLight(_X - 1, _Y, 3, 1, 14);
					GotoXY(_X, _Y);
					SetColor(14, 0);
					cout << "X";
					GotoXY(_X, _Y);
				}
				else
				{
					HighLight(_X - 1, _Y, 3, 1, 14);
					GotoXY(_X, _Y);
					SetColor(14, 0);
					cout << "O";
					GotoXY(_X, _Y);
				}
			}
			else if (_COMMAND == 13) //Nhấn Enter
			{
				switch (CheckBoard(_X, _Y))
				{
				case -1:
					HighLight(_X - 1, _Y, 3, 1, 15);
					GotoXY(_X, _Y);
					SetColor(14, 0);
					cout << "X";
					break;
				case 1:
					HighLight(_X - 1, _Y, 3, 1, 15);
					GotoXY(_X, _Y);
					SetColor(14, 0);
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
					case 2:
					{
						if (_TURN == true)
						{
							Hightlight_Play_turn(55, _A[0][BOARD_SIZE - 1].y, 60, 12, 15, 2);
							Hightlight_Play_turn(55, _A[0][BOARD_SIZE - 1].y, 60, 12, 14, 1);
						}
						else
						{
							Hightlight_Play_turn(55, _A[0][BOARD_SIZE - 1].y, 60, 12, 15, 1);
							Hightlight_Play_turn(55, _A[0][BOARD_SIZE - 1].y, 60, 12, 14, 2);
						}
						break;
					}
					case -1:
					case 1:
					case 0:
						AskContinue();
						while(1)
						{
							int temp = toupper(_getch());
							if (temp == 'N')
							{
								SetColor(15, 0);
								ExitGame();
								return;
							}
							else if (temp == 'Y')
							{
								SetColor(15, 0);
								StartGame();
								break;
							}
						}
					}
				}
				validEnter = true; //Mở khóa
			}
		}
	}
}