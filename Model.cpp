#include <cstdlib>
#include <ctime>

#define BOARD_SIZE 12 //Kích thước ma trận bàn cờ
#define LEFT 3 //Tọa độ trái màn hình bàn cờ
#define TOP 1 //Tọa độ trên màn hình bàn cờ
#define OPTION_HIGH 4
#define OPTION_WIDTH  10

//Khai báo kiểu dữ liệu
extern struct _POINT { int x, y, c; }; //x: tọa độ dòng, y: tọa độ cột, c: đánh dấu
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

//Kiểm tra đã đủ 80% quân cờ trên bàn cờ chưa
bool isfull()
{
	int dem = 0;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (_A[i][j].c != 0)
				dem++;
		}
	}
	float phan_tram = (1.0 * dem) / (BOARD_SIZE * BOARD_SIZE);
	if (phan_tram >= 0.8)
		return true;
	return false;
}

//Các hàm kiểm tra có win không
bool xet_dong() {
	int demX = 0, demO = 0;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		demX = 0;
		demO = 0;
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (_A[i][j].c == 1) //O
				demO++;
			else
			{
				if (_A[i][j].c == -1) //X
				{
					if (demO >= 5 && _A[i][j - (demO + 1)].c != -1)
						demO = 5;
					else
						demO = 0;
				}
				if (_A[i][j].c == 0) // Chưa đánh dấu
				{
					if (demO >= 5)
						demO = 5;
					else
						demO = 0;
				}
			}

			if (_A[i][j].c == -1) //X
				demX++;
			else
			{
				if (_A[i][j].c == 1) //O
				{
					if (demX >= 5 && _A[i][j - (demX + 1)].c != 1)
						demX = 5;
					else
						demX = 0;
				}
				if (_A[i][j].c == 0)
				{
					if (demX >= 5)
						demX = 5;
					else
						demX = 0;
				}
			}

			if (demO >= 5 || demX >= 5)
				return true;
		}
	}
}

bool xet_cot()
{
	int demO = 0, demX = 0;
	for (int j = 0; j < BOARD_SIZE; j++)
	{
		demO = 0;
		demX = 0;
		for (int i = 0; i < BOARD_SIZE; i++)

		{
			if (_A[i][j].c == 1) //O
				demO++;
			else
			{
				if (_A[i][j].c == -1) //X
				{
					if (demO >= 5 && _A[i - (demO + 1)][j].c != -1) //X
						demO = 5;
					else
						demO = 0;
				}
				if (_A[i][j].c == 0)
					if (demO >= 5)
						demO = 5;
					else
						demO = 0;
			}

			if (_A[i][j].c == -1) //X
				demX++;
			else
			{
				if (_A[i][j].c == 1) //O
				{
					if (demX >= 5 && _A[i - demX + 1][j].c != 1) //O
						demX = 5;
					else
						demX = 0;

				}
				if (_A[i][j].c == 0)
					if (demX >= 5)
						demX = 5;
					else
						demX = 0;
			}
		}

		if (demO >= 5 || demX >= 5)
			return true;
	}
}


bool xet_cheo_duoi_phu()
{
	int demO = 0, demX = 0;
	int j = 0, k = 0;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		demO = 0;
		demX = 0;

		k = i;
		j = BOARD_SIZE - 1;
		while (k < BOARD_SIZE && j >= 0)
		{

			if (_A[k][j].c == 1) //O
				demO++;
			else
			{
				if (_A[k][j].c == -1) //X
				{
					if (demO >= 5 && (k - demO >= 0 && j + demO < BOARD_SIZE && _A[k - demO][j + demO].c != -1))
						demO = 5;
					else
						demO = 0;
				}
				if (_A[k][j].c == 0)
					if (demO >= 5)
						demO = 5;
					else
						demO = 0;
			}
			if (_A[k][j].c == -1) //X
				demX++;
			else
			{
				if (_A[k][j].c == 1) //O
				{
					if (demX >= 5 && (k - demX >= 0 && j + demX < BOARD_SIZE && _A[k - demX][j + demX].c == 1))
						demX = 5;
					else
						demX = 0;
				}
				if (_A[k][j].c == 0)
					if (demX >= 5)
						demX = 5;
					else
						demX = 0;
			}
			k++;
			j--;

			if (demO >= 5 || demX >= 5)
				return true;
		}
	}
	return false;
}


bool xet_cheo_tren_phu()
{
	int demO = 0, demX = 0;
	int i = 0, k = 0;
	for (int j = 1; j < BOARD_SIZE; j++)
	{
		demO = 0;
		demX = 0;

		k = j;
		i = 0;
		while (k > 0)
		{
			if (_A[i][k].c == 1) //O
				demO++;
			else
			{
				if (_A[i][k].c == -1) //X
				{
					if (demO >= 5 && _A[i - demO + 1][k + demO + 1].c != -1) //X
						demO = 5;
					else
						demO = 0;
				}
				if (_A[i][k].c == 0)
					if (demO >= 5)
						demO = 5;
					else
						demO = 0;
			}
			if (_A[i][k].c == -1) //X
				demX++;
			else
			{
				if (_A[i][k].c == 1) //O
				{
					if (demX >= 5 && _A[i - demX + 1][k + demX + 1].c != 1)
						demX = 5;
					else
						demX = 0;
				}
				if (_A[i][k].c == 0)
					if (demX >= 5)
						demX = 5;
					else
						demX = 0;
			}
			k--;
			i++;
		}

		if (demO >= 5 || demX >= 5)
			return true;
	}
}

bool xet_chinh()
{
	int demO = 0, demX = 0;
	for (int i = 0; i <= BOARD_SIZE - 5; i++) {
		for (int j = 0; j <= BOARD_SIZE - 5; j++) {
			demO = 0;
			demX = 0;
			for (int k = 0; k < 5; k++) {
				if (_A[i + k][j + k].c == 1) { //O
					demO++;
				}
				else {
					if (_A[i + k][j + k].c == -1) { //X
						if (demO >= 5) {
							demO = 5;
						}
						else {
							demO = 0;
						}
					}
					else { // Chưa đánh dấu
						if (demO >= 5) {
							demO = 5;
						}
						else {
							demO = 0;
						}
					}
				}

				if (_A[i + k][j + k].c == -1) { //X
					demX++;
				}
				else {
					if (_A[i + k][j + k].c == 1) { //O
						if (demX >= 5) {
							demX = 5;
						}
						else {
							demX = 0;
						}
					}
					else { // Chưa đánh dấu
						if (demX >= 5) {
							demX = 5;
						}
						else {
							demX = 0;
						}
					}
				}
			}
			if (demO >= 5 || demX >= 5) {
				return true;
			}
		}
	}
	return false;
}

bool xet_phu()
{
	int demO = 0, demX = 0;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		demX = 0;
		demO = 0;
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (i + j == BOARD_SIZE - 1)
			{
				if (_A[i][j].c == 1) //O
					demO++;
				else
				{
					if (_A[i][j].c == -1) //X
					{
						if (demO >= 5 && _A[i - demO + 1][j + demO + 1].c != -1) //X
							demO = 5;
						else
							demO = 0;
					}
					if (_A[i][j].c == 0) 
					{
						if (demO >= 5)
							demO = 5;
						else
							demO = 0;
					}
				}
				if (_A[i][j].c == -1) //X
					demX++;
				else
				{
					if (_A[i][j].c == 1) //O
					{
						if (demX >= 5 && _A[i - demX + 1][j + demX + 1].c != 1) //O
							demX = 5;
						else
							demX = 0;
					}
					if (_A[i][j].c == 0)
						if (demX >= 5)
							demX = 5;
						else
							demX = 0;
				}
			}
		}

		if (demO >= 5 || demX >= 5)
			return true;
	}
}

bool xet_cheo_phu_ben_trai_cung()
{
	int demO = 0, demX = 0;
	int i = 0, k = 0;
	for (int j = 0; j < BOARD_SIZE; j++)
	{
		demO = 0;
		demX = 0;

		k = j;
		i = 0;
		while (k >= 0 && i < BOARD_SIZE)
		{
			if (_A[i][k].c == 1) //O
				demO++;
			else
			{
				if (_A[i][k].c == -1) //X
				{
					if (demO >= 5 && (i - demO < 0 || k + demO >= BOARD_SIZE || _A[i - demO][k + demO].c != -1)) //X
						demO = 5;
					else
						demO = 0;
				}
				if (_A[i][k].c == 0)
					if (demO >= 5)
						demO = 5;
					else
						demO = 0;
			}
			if (_A[i][k].c == -1) //X
				demX++;
			else
			{
				if (_A[i][k].c == 1) //O
				{
					if (demX >= 5 && (i - demX < 0 || k + demX >= BOARD_SIZE || _A[i - demX][k + demX].c != 1))
						demX = 5;
					else
						demX = 0;
				}
				if (_A[i][k].c == 0)
					if (demX >= 5)
						demX = 5;
					else
						demX = 0;
			}
			k--;
			i++;
		}

		if (demO >= 5 || demX >= 5)
			return true;
	}
	return false;
}

//Hàm kiểm tra thắng
bool WinTest()
{
	if (xet_dong() == true)
		return true;
	if (xet_cot() == true)
		return true;
	if (xet_cheo_duoi_phu() == true)
		return true;
	if (xet_cheo_tren_phu() == true)
		return true;
	if (xet_chinh() == true)
		return true;
	if (xet_phu() == true)
		return true;
	if (xet_cheo_phu_ben_trai_cung() == true)
		return true;
	return false;
}

/*Hàm kiểm ta xem có người thắng/thua/hòa*/
int TestBoard()
{
	if (isfull() == true) return 0; //hòa
	else
	{
		if (WinTest() == true)
			return (_TURN == true ? -1 : 1);
		else
			return 2;
	}
}

/*Hàm hổ trợ xem đang lượt của ai khi enter*/
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

/*Hàm kiểm tra ô đã đánh chưa*/
int CheckTick(int pX, int pY)
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (_A[i][j].x == pX && _A[i][j].y == pY)
				return _A[i][j].c;
		}
	}
}

//Hàm tạo bot chơi với người chơi, lượt của bot là người thứ 2 hay _TURN = false
int Bot(int& pX, int& pY)
{
	srand(time(NULL));

	pX = rand() % ((BOARD_SIZE - 1) - 0 + 1) + 0;
	pY = rand() % ((BOARD_SIZE - 1) - 0 + 1) + 0;

	if (_A[pX][pY].c != 0) {
		while (true) {
			pX = rand() % ((BOARD_SIZE - 1) - 0 + 1) + 0;
			pY = rand() % ((BOARD_SIZE - 1) - 0 + 1) + 0;

			if (_A[pX][pY].c == 0)
				break;
		}
	}

	_A[pX][pY].c = 1;

	return 1;
}

