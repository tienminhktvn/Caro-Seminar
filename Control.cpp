#include <stdlib.h>

#define BOARD_SIZE 12 //Kích thước ma trận bàn cờ
#define LEFT 3 //Tọa độ trái màn hình bàn cờ
#define TOP 1 //Tọa độ trên màn hình bàn cờ

extern struct _POINT { int x, y, c; }; //x: tọa độ dòng, y: tọa độ cột, c: đánh dấu
extern _POINT _A[BOARD_SIZE][BOARD_SIZE]; //Ma trận bàn cờ
extern bool _TURN; //true là lượt người thứ nhất và false là lượt người thứ hai
extern int _COMMAND; //Biến nhận giá trị phím người dùng nhập
extern int _X, _Y; //Tọa độ hiện hành trên màn hình bàn cờ

void ResetData();
void DrawBoard(int pSize);
void GabageCollect();
void GotoXY(int x, int y);
void ChangeBackgrColor();
void DrawMenu(int x,int y,int w,int h);


/*Hàm dọn dẹp tài nguyên*/
void StartGame()
{
	system("cls"); //xóa màn hình
	ResetData();
	ChangeBackgrColor(); //đổi màu nền
	DrawBoard(BOARD_SIZE); //vẽ bảng caro
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
