#include "Field.h"

Field::Field()
{
}

Field::~Field()
{
}

void Field::Initialize()
{
	//�}�b�v�̐���(csv�Ή��\��)
	int tempMap[gridY][gridX] = {
		{-1,2,2,2,0},
		{-1,11,0,0,0},
		{11,0,0,0,2},
		{-1,0,0,0,0},
		{-1,2,2,2,0}
	};

	//�}�b�v�ɏ�����ꍞ��
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
	//�c���O���b�h
	for (int i = 1; i < gridY; i++) {
		DrawLine(100 * i, 0, 100 * i, 100 * gridY, GetColor(255, 255, 255));
	}
	//�����O���b�h
	for (int i = 1; i < gridX; i++) {
		DrawLine(0, 100 * i, 100 * gridX, 100 * i, GetColor(255, 255, 255));
	}

	for (int i = 0; i < gridY; i++) {
		for (int j = 0; j < gridX; j++) {
			if (map[i][j] != 0) {
				//��
				if (map[i][j] == -1) {
					DrawBox(j * 100,i * 100,(j + 1) * 100,(i + 1) * 100,GetColor(255,255,255),true);
					continue;
				}
				///�Ȃ���
				//�Ȃ���J�E���g
				int count = 0;

				//�E�ւ̂Ȃ���
				for (int k = j + 1; k < gridX; k++) {
					if (map[i][k] != 0 && map[i][k] != -1) {
						count++;
						break;
					}
				}
				//���ւ̂Ȃ���
				for (int k = i + 1; k < gridY; k++) {
					if (map[k][j] != 0 && map[k][j] != -1) {
						count++;
						break;
					}
				}
				
				//���ւ̂Ȃ���Ɣz��
				for (int k = j - 1; k >= 0; k--) {
					if (map[i][k] != 0 && map[i][k] != -1) {
						DrawLine(j * 100 + 50, i * 100 + 50, k * 100 + 50, i * 100 + 50, GetColor(255, 255, 0),5);
						count++;
						break;
					}
				}
				//��ւ̂Ȃ���Ɣz��
				for (int k = i - 1; k >= 0; k--) {
					if (map[k][j] != 0 && map[k][j] != -1) {
						DrawLine(j * 100 + 50, i * 100 + 50, j * 100 + 50, k * 100 + 50, GetColor(255, 255, 0),5);
						count++;
						break;
					}
				}

				//�������锭�d�@
				if (map[i][j] < 10) {
					//���d�@
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
				//�������Ȃ����d�@
				else {
					//���d�@
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
