#include "Field.h"

int Field::map[gridY][gridX] = {};

Field::Field()
{
}

Field::~Field()
{
}

void Field::Initialize()
{
	//マップの生成(csv対応予定)
	// -1 壁
	// 00 空間
	// 1桁目　0 = 動かせる発電機(2桁目1~9まで)	
	// 1桁目　1 = 動かせない発電機(2桁目1~9まで)
	// 1桁目　2 = 初期の配線(2桁目 0 = 縦配線　　1 = 横配線)

	// 初期配線は設定しなくても良いがその場合 "縦" が優先される
	// 初期でクロスしている配線は縦が優先されるが縦部分がショートしているとバグる

	int tempMap[gridY][gridX] = {
		{01,00,00,00,11},
		{00,01,00,01,00},
		{00,00,-1,00,00},
		{00,01,00,01,00},
		{11,00,-1,00,01}
	};

	//マップに情報を入れ込む
	for (int i = 0; i < gridY; i++) {
		for (int j = 0; j < gridX; j++) {
			map[i][j] = tempMap[i][j];
		}
	}

	for (int i = ANDO_MAP_CONST - 1; i >= 0; i--) {
		for (int j = 0; j < gridY; j++) {
			for (int k = 0; k < gridY; k++) {
				andoMap[i][j][k] = 0;
				andoMapActive[i] = false;
			}
		}
	}
}

void Field::Update()
{
	//右クリックで1手戻る
	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {
		if (isAndo == false) {
			//1番新しい情報を探す
			for (int i = ANDO_MAP_CONST - 1; i >= 0; i--) {
				if (andoMapActive[i] == true) {
					for (int j = 0; j < gridY; j++) {
						for (int k = 0; k < gridX; k++) {
							map[j][k] = andoMap[i][j][k];
							andoMapActive[i] = false;
						}
					}
					break;
				}
			}
			isAndo = true;
		}
	}
	else {
		isAndo = false;
	}
}

void Field::Draw()
{
	//縦軸グリッド
	for (int i = 1; i < gridY; i++) {
		DrawLine(gridLength * i, 0, gridLength * i, gridLength * gridY, GetColor(255, 255, 255));
	}
	//横軸グリッド
	for (int i = 1; i < gridX; i++) {
		DrawLine(0, gridLength * i, gridLength * gridX, gridLength * i, GetColor(255, 255, 255));
	}

	for (int i = 0; i < gridY; i++) {
		for (int j = 0; j < gridX; j++) {
			//壁
			if (map[i][j] == -1) {
				DrawBox(j * gridLength, i * gridLength, (j + 1) * gridLength, (i + 1) * gridLength, GetColor(255, 255, 255), true);
			}
			else if (map[i][j] > 0 && map[i][j] < 20) {
				///つながり
				//つながりカウント
				int count = 0;

				//右へのつながり
				for (int k = j + 1; k < gridX; k++) {
					if (map[i][k] == -1) {
						break;
					}
					else if (map[i][k] > 0 && map[i][k] < 20) {
						count++;
						break;
					}
				}
				//下へのつながり
				for (int k = i + 1; k < gridY; k++) {
					if (map[k][j] == -1) {
						break;
					}
					if (map[k][j] > 0 && map[k][j] < 20) {
						count++;
						break;
					}
				}

				//左へのつながりと配線
				for (int k = j - 1; k >= 0; k--) {
					if (map[i][k] == -1) {
						break;
					}
					if (map[i][k] > 0 && map[i][k] < 20) {
						count++;
						break;
					}
				}
				//上へのつながり
				for (int k = i - 1; k >= 0; k--) {
					if (map[k][j] == -1) {
						break;
					}
					if (map[k][j] > 0 && map[k][j] < 20) {
						count++;
						break;
					}
				}

				//動かせる発電機
				if (map[i][j] < 10) {
					//発電機
					if (count >= map[i][j]) {
						DrawCircle(j * gridLength + gridLength / 2, i * gridLength + gridLength / 2, gridLength / 2, GetColor(200, 200, 0));
					}
					else if (count < map[i][j]) {
						DrawCircle(j * gridLength + gridLength / 2, i * gridLength + gridLength / 2, gridLength / 2, GetColor(0, 0, 200));
					}
				}
				//動かせない発電機
				else if (map[i][j] < 20) {
					//発電機
					if (count >= map[i][j] - 10) {
						DrawBox(j * gridLength, i * gridLength, (j + 1) * gridLength, (i + 1) * gridLength, GetColor(200, 200, 0), true);
					}
					else if (count < map[i][j] - 10) {
						DrawBox(j * gridLength, i * gridLength, (j + 1) * gridLength, (i + 1) * gridLength, GetColor(0, 0, 200), true);
					}
				}
				else {
					if (map[i][j] == 20) {
						DrawBox(j * gridLength + 40, i * gridLength, (j + 1) * gridLength - 40, (i + 1) * gridLength, GetColor(200, 200, 0), true);
					}
					else if (map[i][j] == 21) {
						DrawBox(j * gridLength, i * gridLength + 40, (j + 1) * gridLength, (i + 1) * gridLength - 40, GetColor(200, 200, 0), true);
					}
				}
			}
			//縦の配線
			else if (map[i][j] == 20) {
				DrawBox(j * gridLength + 40, i * gridLength, (j + 1) * gridLength - 40, (i + 1) * gridLength, GetColor(200, 200, 0), true);
			}
			//横の配線
			else if (map[i][j] == 21) {
				DrawBox(j * gridLength, i * gridLength + 40, (j + 1) * gridLength, (i + 1) * gridLength - 40, GetColor(200, 200, 0), true);
			}
			//十字の配線
			else if (map[i][j] == 22) {
				DrawBox(j * gridLength + 40, i * gridLength, (j + 1) * gridLength - 40, (i + 1) * gridLength, GetColor(200, 200, 0), true);
				DrawBox(j * gridLength, i * gridLength + 40, (j + 1) * gridLength, (i + 1) * gridLength - 40, GetColor(200, 200, 0), true);
			}
		}
	}
}

int Field::GetMapNum(int x, int y)
{
	int temp = map[y][x];
	return temp;
}

void Field::SetMapNum(int x, int y, int num)
{
	map[y][x] = num;
}

bool Field::PullBlock(int y, int x, int moveDirection)
{
	//進む先が押せるブロックだったら
	if (map[y][x] == 1)
	{
		int Y = 0;
		int X = 0;

		Y = y;
		X = x - 1;
		//一個左に何もなかったら
		if (moveDirection == LEFT && (map[Y][X] == 0 || map[Y][X] == 20 || map[Y][X] == 21)
			&& Y >= 0 && Y <= gridY - 1 && X >= 0 && X <= gridX - 1)
		{
			map[Y][X] = map[y][x];
			map[y][x] = 0;
			return true;
		}

		Y = y - 1;
		X = x;
		//一個上に何もなかったら
		if (moveDirection == UP && (map[Y][X] == 0 || map[Y][X] == 20 || map[Y][X] == 21)
			&& Y >= 0 && Y <= gridY - 1 && X >= 0 && X <= gridX - 1)
		{
			map[Y][X] = map[y][x];
			map[y][x] = 0;
			return true;
		}

		Y = y;
		X = x + 1;
		//一個左に何もなかったら
		if (moveDirection == RIGHT && (map[Y][X] == 0 || map[Y][X] == 20 || map[Y][X] == 21)
			&& Y >= 0 && Y <= gridY - 1 && X >= 0 && X <= gridX - 1)
		{
			map[Y][X] = map[y][x];
			map[y][x] = 0;
			return true;
		}

		Y = y + 1;
		X = x;
		//一個左に何もなかったら
		if (moveDirection == DOWN && (map[Y][X] == 0 || map[Y][X] == 20 || map[Y][X] == 21)
			&& Y >= 0 && Y <= gridY - 1 && X >= 0 && X <= gridX - 1)
		{
			map[Y][X] = map[y][x];
			map[y][x] = 0;
			return true;
		}
	}

	return false;
}

bool Field::GetPullBlock(int y, int x, int moveDirection)
{
	if (map[y][x] == 1)
	{
		int Y = 0;
		int X = 0;

		Y = y;
		X = x - 1;
		//一個左に何もなかったら
		if (moveDirection == LEFT && (map[Y][X] == 0 || map[Y][X] == 20 || map[Y][X] == 21)
			&& Y >= 0 && Y <= gridY - 1 && X >= 0 && X <= gridX - 1)
		{
			return true;
		}

		Y = y - 1;
		X = x;
		//一個上に何もなかったら
		if (moveDirection == UP && (map[Y][X] == 0 || map[Y][X] == 20 || map[Y][X] == 21)
			&& Y >= 0 && Y <= gridY - 1 && X >= 0 && X <= gridX - 1)
		{
			return true;
		}

		Y = y;
		X = x + 1;
		//一個左に何もなかったら
		if (moveDirection == RIGHT && (map[Y][X] == 0 || map[Y][X] == 20 || map[Y][X] == 21)
			&& Y >= 0 && Y <= gridY - 1 && X >= 0 && X <= gridX - 1)
		{
			return true;
		}

		Y = y + 1;
		X = x;
		//一個左に何もなかったら
		if (moveDirection == DOWN && (map[Y][X] == 0 || map[Y][X] == 20 || map[Y][X] == 21)
			&& Y >= 0 && Y <= gridY - 1 && X >= 0 && X <= gridX - 1)
		{
			return true;
		}
	}

	return false;
}

bool Field::CanMoveGrid(int y, int x, int moveDirection)
{
	//ブロックがあっても押せたら
	if (GetPullBlock(y, x, moveDirection))
	{
		return true;
	}
	//押せなかったら
	if (map[y][x] != 1 && map[y][x] != 11 && map[y][x] != -1)
	{
		return true;
	}
	return false;
}
