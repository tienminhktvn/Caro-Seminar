	#include <stdlib.h>
	#include <string>
	using namespace std;

	#define BOARD_SIZE 12 //Kích thước ma trận bàn cờ
	#define LEFT 3 //Tọa độ trái màn hình bàn cờ
	#define TOP 1 //Tọa độ trên màn hình bàn cờ
	#define OPTION_HIGH 2
	#define OPTION_WIDTH  20


	extern struct _POINT { int x, y, c; }; //x: tọa độ dòng, y: tọa độ cột, c: đánh dấu
	extern _POINT _A[BOARD_SIZE][BOARD_SIZE]; //Ma trận bàn cờ
	extern bool _TURN; //true là lượt người thứ nhất và false là lượt người thứ hai
	extern int _COMMAND; //Biến nhận giá trị phím người dùng nhập
	extern int _X, _Y; //Tọa độ hiện hành trên màn hình bàn cờ
	extern struct MENU
	{
		string opt1;
		string opt2;
		string opt3;
		string opt4;
	};
	extern MENU menu;
	extern int _OPTION;
	extern int Total_game;
	extern int Score1;
	extern int Score2;
	extern string Player1_name;
	extern string Player2_name;

	void ResetGame();
	void DrawBoard(int pSize);
	void GabageCollect();
	void GotoXY(int x, int y);
	void ChangeBackgrColor();
	void DrawMenu(int x,int y,int w,int h);
	void DrawBox(int x, int y, int w, int h);
	void DrawTurn(int x, int y, int w, int h);


	/*Hàm dọn dẹp tài nguyên*/
	void StartGame()
	{
		system("cls");
		ResetGame();
		DrawBox(55, 19, 60, 8);
		DrawTurn(55, _A[0][BOARD_SIZE-1].y, 60, 12);
		DrawBoard(BOARD_SIZE);
	}

	/*Hàm thoát game*/
	void ExitGame()
	{
		system("cls");
		GabageCollect();
	}

	/*Hàm di chuyển sang phải*/
	void MoveRight()
	{
		if (_X < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].x)
		{
			_X += 4;
			GotoXY(_X, _Y);
		}
	}

	/*Hàm di chuyển sang trái*/
	void MoveLeft()
	{
		if (_X > _A[0][0].x)
		{
			_X -= 4;
			GotoXY(_X, _Y);
		}
	}

	/*Hàm di chuyển xuống*/
	void MoveDown()
	{
		if (_Y< _A[BOARD_SIZE-1][BOARD_SIZE-1].y)
		{
			_Y += 2;
			GotoXY(_X, _Y);
		}
	}

	/*Hàm di chuyển lên*/
	void MoveUp()
	{
		if (_Y > _A[0][0].y)
		{
			_Y -= 2;
			GotoXY(_X, _Y);
		}
	}

	/*Hàm di chuyển lên trong menu*/
	void MenuUp(int& o)
	{
		if (o != 1)
		{
			_Y -= (OPTION_HIGH + 1);
			GotoXY(_X, _Y);
			o--;
		}
	}

	/*Hàm di chuyển xuống trong menu*/
	void MenuDown(int& o,int n)
	{
		if (o != n)
		{
			_Y += (OPTION_HIGH + 1);
			GotoXY(_X, _Y);
			o++;
		}
	}
