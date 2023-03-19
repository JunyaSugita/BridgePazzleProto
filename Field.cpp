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
	int tempMap[gridY][gridX] = {
		{02,00,00,00,00},
		{00,01,00,00,00},
		{00,20,-1,00,00},
		{00,01,21,01,00},
		{00,00,00,00,00}
	};

	//マップに情報を入れ込む
	for (int i = 0; i < gridY; i++) {
		for (int j = 0; j < gridX; j++) {
			map[i][j] = tempMap[i][j];
		}
	}
}

void Field::Update()
{

}

void Field::Draw()
{
	for (int i = 0; i < gridY; i++) {
		for (int j = 0; j < gridX; j++) {
			shortMap[i][j] = false;
		}
	}

	//縦軸グリッド
	for (int i = 1; i < gridY; i++) {
		DrawLine(100 * i, 0, 100 * i, 100 * gridY, GetColor(255, 255, 255));
	}
	//横軸グリッド
	for (int i = 1; i < gridX; i++) {
		DrawLine(0, 100 * i, 100 * gridX, 100 * i, GetColor(255, 255, 255));
	}

	for (int i = 0; i < gridY; i++) {
		for (int j = 0; j < gridX; j++) {
			if (map[i][j] != 0) {
				//壁
				if (map[i][j] == -1) {
					DrawBox(j * 100,i * 100,(j + 1) * 100,(i + 1) * 100,GetColor(255,255,255),true);
					continue;
				}
				///つながり
				//つながりカウント
				int count = 0;

				//右へのつながり
				for (int k = j + 1; k < gridX; k++) {
					if (map[i][k] == -1) {
						break;
					}
					if (map[i][k] > 0 && map[i][j] < 20) {
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
				//上へのつながりと配線
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
					if (count == map[i][j]) {
						DrawCircle(j * 100 + 50, i * 100 + 50, 50, GetColor(200, 200, 0));
						DrawFormatString(j * 100 + 40, i * 100 + 40, GetColor(255, 255, 255), "%d", map[i][j]);
					}
					else if (count > map[i][j]) {
						DrawCircle(j * 100 + 50, i * 100 + 50, 50, GetColor(200, 0, 0));
						DrawFormatString(j * 100 + 40, i * 100 + 40, GetColor(255, 255, 255), "%d", map[i][j]);
						shortMap[i][j] = true;
					}
					else if (count < map[i][j]) {
						DrawCircle(j * 100 + 50, i * 100 + 50, 50, GetColor(0, 0, 200));
						DrawFormatString(j * 100 + 40, i * 100 + 40, GetColor(255, 255, 255), "%d", map[i][j]);
					}
				}
				//動かせない発電機
				else if(map[i][j] < 20){
					//発電機
					if (count == map[i][j] - 10) {
						DrawBox(j * 100, i * 100, (j + 1) * 100, (i + 1) * 100, GetColor(200, 200, 0), true);
						DrawFormatString(j * 100 + 40, i * 100 + 40, GetColor(255, 255, 255), "%d", map[i][j] - 10);
					}
					else if (count > map[i][j] - 10) {
						DrawBox(j * 100, i * 100, (j + 1) * 100, (i + 1) * 100, GetColor(200, 0, 0), true);
						DrawFormatString(j * 100 + 40, i * 100 + 40, GetColor(255, 255, 255), "%d", map[i][j] - 10);
					}
					else if (count < map[i][j] - 10) {
						DrawBox(j * 100, i * 100, (j + 1) * 100, (i + 1) * 100, GetColor(0, 0, 200), true);
						DrawFormatString(j * 100 + 40, i * 100 + 40, GetColor(255, 255, 255), "%d", map[i][j] - 10);
					}
				}
				else {
					if (map[i][j] == 20) {
						DrawBox(j * 100 + 40, i * 100, (j + 1) * 100 - 40, (i + 1) * 100, GetColor(200, 200, 0), true);
					}
					else if (map[i][j] == 21) {
						DrawBox(j * 100, i * 100 + 40, (j + 1) * 100, (i + 1) * 100 - 40, GetColor(200, 200, 0), true);
					}
				}
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
