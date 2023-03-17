#include "Field.h"

Field::Field()
{
}

Field::~Field()
{
}

void Field::Initialize()
{
	int tempMap[gridY][gridX] = {
		{1,0,0,0,0,0,1},
		{0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0}
	};

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
	for (int i = 1; i < gridY; i++) {
		DrawLine(100 * i, 0, 100 * i, 100 * gridY, GetColor(255, 255, 255));
	}
	for (int i = 1; i < gridX; i++) {
		DrawLine(0, 100 * i, 100 * gridX, 100 * i, GetColor(255, 255, 255));
	}

	for (int i = 0; i < gridY; i++) {
		for (int j = 0; j < gridX; j++) {
			if (map[i][j] != 0) {
				if (map[i][j] == -1) {
					break;
				}

				int count = 0;
				//‚Â‚È‚ª‚è
				//‰E
				for (int k = j + 1; k < gridX; k++) {
					if (map[i][k] != 0) {
						count++;
					}
				}
				//‰º
				for (int k = i + 1; k < gridY; k++) {
					if (map[k][j] != 0) {
						count++;
					}
				}
				
				//¶
				for (int k = j - 1; k >= 0; k--) {
					if (map[i][k] != 0) {
						DrawLine(j * 100 + 50, i * 100 + 50, k * 100 + 50, i * 100 + 50, GetColor(255, 255, 0),5);
						count++;
					}
				}
				//ã
				for (int k = i - 1; k >= 0; k--) {
					if (map[k][j] != 0) {
						DrawLine(j * 100 + 50, i * 100 + 50, j * 100 + 50, k * 100 + 50, GetColor(255, 255, 0),5);
						count++;
					}
				}
				//”­“d‹@
				if (count == map[i][j]) {
					DrawCircle(j * 100 + 50, i * 100 + 50, 50, GetColor(200, 200, 0));
					DrawFormatString(j * 100 + 40, i * 100 + 40, GetColor(255, 255, 255), "%d", map[i][j]);
				}
				else if (count > map[i][j]) {
					DrawCircle(j * 100 + 50, i * 100 + 50, 50, GetColor(200, 0, 0));
					DrawFormatString(j * 100 + 40, i * 100 + 40, GetColor(255, 255, 255), "%d", map[i][j]);
				}
				else if (count < map[i][j]) {
					DrawCircle(j * 100 + 50, i * 100 + 50, 50, GetColor(0, 0, 200));
					DrawFormatString(j * 100 + 40, i * 100 + 40, GetColor(255, 255, 255), "%d", map[i][j]);
				}

			}
		}
	}


}

int Field::GetMapNum(int x, int y)
{
	int temp = map[y / 100][x / 100];
	map[y / 100][x / 100] = 0;
	return temp;
}

void Field::SetMapNum(int x, int y, int num)
{
	if (num == 0) {
		return;
	}
	map[y / 100][x / 100] = num;
}
