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
	// -1 ��
	// 00 ���
	// 1���ځ@0 = �������锭�d�@(2����1~9�܂�)	
	// 1���ځ@1 = �������Ȃ����d�@(2����1~9�܂�)
	// 1���ځ@2 = �����̔z��(2���� 0 = �c�z���@�@1 = ���z��)

	// �����z���͐ݒ肵�Ȃ��Ă��ǂ������̏ꍇ "�c" ���D�悳���
	// �����ŃN���X���Ă���z���͏c���D�悳��邪�c�������V���[�g���Ă���ƃo�O��

	int tempMap[gridY][gridX] = {
		{01,00,00,00,11},
		{00,01,00,01,00},
		{00,00,-1,00,00},
		{00,01,00,01,00},
		{11,00,-1,00,01}
	};

	//�}�b�v�ɏ�����ꍞ��
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
	//�E�N���b�N��1��߂�
	if((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)
	{
		if(isAndo == false)
		{
			//1�ԐV��������T��
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

	//�c���O���b�h
	for (int i = 0; i < gridY; i++) {
		DrawLine(60 * i + (wide * 300), 0, 60 * i + (wide * 300), 60 * gridY + (height * 300), GetColor(255, 255, 255));
	}
	//�����O���b�h
	for (int i = 0; i < gridX; i++) {
		DrawLine(0, 60 * i + (height * 300), 60 * gridX + (wide * 300), 60 * i + (height * 300), GetColor(255, 255, 255));
	}

	for (int i = 0; i < gridY; i++) {
		for (int j = 0; j < gridX; j++) {
			//��
			if (map[i][j] == -1) {
				DrawBox(j * 60 + (height * 300), i * 60 + (wide * 300), (j + 1) * 60 + (height * 300), (i + 1) * 60 + (wide * 300), GetColor(255, 255, 255), true);
			}
			else if (map[i][j] > 0 && map[i][j] < 20) {

				///�Ȃ���
				//�Ȃ���J�E���g
				int count = 0;

				//�E�ւ̂Ȃ���
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
				//���ւ̂Ȃ���
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

				//���ւ̂Ȃ���
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
				//��ւ̂Ȃ���
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

				//�������锭�d�@
				if (map[i][j] < 10) {
					//���d�@
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
				//�������Ȃ����d�@
				else if (map[i][j] < 20) {
					//���d�@
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
