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
void Play();
//Hàm Model
int CheckTick(int pX, int pY);
int CheckBoard(int pX, int pY);
int TestBoard();
void ResetData();
void Menu();

void main()
{
	FixConsoleWindow();
	system("color F0");
	Play();
}
