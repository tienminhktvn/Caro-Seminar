#define BOARD_SIZE 12 //Kích thước ma trận bàn cờ
#define LEFT 3 //Tọa độ trái màn hình bàn cờ
#define TOP 1 //Tọa độ trên màn hình bàn cờ

//Khai báo kiểu dữ liệu
extern struct _POINT {int x, y, c; }; //x: tọa độ dòng, y: tọa độ cột, c: đánh dấu
extern _POINT _A[BOARD_SIZE][BOARD_SIZE]; //Ma trận bàn cờ
extern bool _TURN; //true là lượt người thứ nhất và false là lượt người thứ hai
extern int _COMMAND; //Biến nhận giá trị phím người dùng nhập
extern int _X, _Y; //Tọa độ hiện hành trên màn hình bàn cờ

/*Hàm khởi tạo dữ liệu mặc định ban đầu cho ma trận bàn cờ*/
void ResetData()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			_A[i][j].x = 4 * j + LEFT + 2; //Trùng với hoành độ màn hình bàn cờ
			_A[i][j].y = 2 * i + TOP + 1; //Trùng với tung độ màn hình bàn cờ
			_A[i][j].c = 0; //0: chưa đánh dấu, -1: true đánh, 1: fasle đánh
		}
	}
	_TURN = true; _COMMAND = -1; //Gán lượt và phím mặt định
	_X = _A[0][0].x; _Y = _A[0][0].y; //Thiết lập lại tọa đồ hiện hành ban đầu
}

/*Hàm dọn dẹp tài nguyên*/
void GabageCollect()
{
	//Dọn dẹp tài nguyên nếu khai báo con trỏ
}

/*Hàm kiểm ta xem có người thắng/thua/hòa*/
int TestBoard()
{
	return 2;
}

/*Hàm kiểm tra ô đã được đánh chưa*/
int CheckBoard(int pX, int pY)
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (_A[i][j].x == pX && _A[i][j].y == pY && _A[i][j].c == 0)
			{
				if (_TURN == true) //Lượt của người 1
					_A[i][j].c = -1; //c= -1 tức là người 1 đánh dấu
				else _A[i][j].c = 1; //c=1 tức là người chơi 2 đánh dấu
				return _A[i][j].c;
			}
		}
	}
	return 0;
}