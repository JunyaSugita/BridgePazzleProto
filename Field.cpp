#include "Field.h"



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

	for(int i = ANDO_MAP_CONST - 1; i >= 0; i--)
	{
		for(int j = 0; j < gridY; j++)
		{
			for(int k = 0; k < gridY; k++)
			{
				andoMap[i][j][k] = 0;
				andoMapActive[i] = false;
			}
		}
	}
}

void Field::Update()
{
	//右クリックで1手戻る
	if((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)
	{
		if(isAndo == false)
		{
			//1番新しい情報を探す
			for(int i = ANDO_MAP_CONST - 1; i >= 0; i--)
			{
				if(andoMapActive[i] == true)
				{
					for(int j = 0; j < gridY; j++)
					{
						for(int k = 0; k < gridX; k++)
						{
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
	else
	{
		isAndo = false;
	}
}

void Field::Draw(int height, int wide)
//void Field::Draw()
{
	for (int i = 0; i < gridY; i++) {
		for (int j = 0; j < gridX; j++) {
			shortMap[i][j] = false;
		}
	}

	//縦軸グリッド
	for (int i = 0; i < gridY; i++) {
		DrawLine(60 * i + (wide * 300), 0, 60 * i + (wide * 300), 60 * gridY + (height * 300), GetColor(255, 255, 255));
	}
	//横軸グリッド
	for (int i = 0; i < gridX; i++) {
		DrawLine(0, 60 * i + (height * 300), 60 * gridX + (wide * 300), 60 * i + (height * 300), GetColor(255, 255, 255));
	}

	for (int i = 0; i < gridY; i++) {
		for (int j = 0; j < gridX; j++) {
			//壁
			if (map[i][j] == -1) {
				DrawBox(j * 60 + (height * 300), i * 60 + (wide * 300), (j + 1) * 60 + (height * 300), (i + 1) * 60 + (wide * 300), GetColor(255, 255, 255), true);
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
					if (map[i][k] == 20) {
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
					if (map[k][j] == 21) {
						break;
					}
					if (map[k][j] > 0 && map[k][j] < 20) {
						count++;
						break;
					}
				}

				//左へのつながり
				for (int k = j - 1; k >= 0; k--) {
					if (map[i][k] == -1) {
						break;
					}
					if (map[i][k] == 20) {
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
					if (map[k][j] == 21) {
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
					if (count == map[i][j]) {
						DrawCircle(j * 60 + 30 + (height * 300), i * 60 + 30 + (wide * 300), 30, GetColor(200, 200, 0));
						DrawFormatString(j * 60 + 40 + (height * 300), i * 60 + 40 + (wide * 300), GetColor(255, 255, 255), "%d", map[i][j]);
					}
					else if (count > map[i][j]) {
						DrawCircle(j * 60 + 30 + (height * 300), i * 60 + 30 + (wide * 300), 30, GetColor(200, 0, 0));
						DrawFormatString(j * 60 + 40 + (height * 300), i * 60 + 40 + (wide * 300), GetColor(255, 255, 255), "%d", map[i][j]);
						shortMap[i][j] = true;
					}
					else if (count < map[i][j]) {
						DrawCircle(j * 60 + 30 + (height * 300), i * 60 + 30 + (wide * 300), 30, GetColor(0, 0, 200));
						DrawFormatString(j * 60 + 40 + (height * 300), i * 60 + 40 + (wide * 300), GetColor(255, 255, 255), "%d", map[i][j]);
					}
				}
				//動かせない発電機
				else if (map[i][j] < 20) {
					//発電機
					if (count == map[i][j] - 10) {
						DrawBox(j * 60 + (height * 300), i * 60 + (wide * 300), (j + 1) * 60 + (height * 300), (i + 1) * 60 + (wide * 300), GetColor(200, 200, 0), true);
						DrawFormatString(j * 60 + 40, i * 60 + 40, GetColor(255, 255, 255), "%d", map[i][j] - 10);
					}
					else if (count > map[i][j] - 10) {
						DrawBox(j * 60 + (height * 300), i * 60 + (wide * 300), (j + 1) * 60 + (height * 300), (i + 1) * 60 + (wide * 300), GetColor(200, 0, 0), true);
						DrawFormatString(j * 60 + 40, i * 60 + 40, GetColor(255, 255, 255), "%d", map[i][j] - 10);
						shortMap[i][j] = true;
					}
					else if (count < map[i][j] - 10) {
						DrawBox(j * 60 + (height * 300), i * 60 + (wide * 300), (j + 1) * 60 + (height * 300), (i + 1) * 60 + (wide * 300), GetColor(0, 0, 200), true);
						DrawFormatString(j * 60 + 40 + (height * 300), i * 60 + 40, GetColor(255, 255, 255), "%d", map[i][j] - 10);
					}
				}
			}
			else if (map[i][j] == 20) {
				DrawBox(j * 60 + 40 + (height * 300), i * 60 + (wide * 300), (j + 1) * 60 - 40 + (height * 300), (i + 1) * 60 + (wide * 300), GetColor(200, 200, 0), true);
			}
			else if (map[i][j] == 21) {
				DrawBox(j * 60 + (height * 300), i * 60 + 40 + (wide * 300), (j + 1) * 60 + (height * 300), (i + 1) * 60 - 40 + (wide * 300), GetColor(200, 200, 0), true);
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

void Field::SetPos(int x, int y)
{
	pos.x = x * 300;
	pos.y = y * 300;
}
