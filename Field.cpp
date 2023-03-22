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

	//�c���O���b�h
	for (int i = 1; i < gridY; i++) {
		DrawLine(60 * i, 0, 60 * i, 60 * gridY, GetColor(255, 255, 255));
	}
	//�����O���b�h
	for (int i = 1; i < gridX; i++) {
		DrawLine(0, 60 * i, 60 * gridX, 60 * i, GetColor(255, 255, 255));
	}

	for (int i = 0; i < gridY; i++) {
		for (int j = 0; j < gridX; j++) {
			//��
			if (map[i][j] == -1) {
				DrawBox(j * 60, i * 60, (j + 1) * 60, (i + 1) * 60, GetColor(255, 255, 255), true);
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
						DrawCircle(j * 60 + 30, i * 60 + 30, 30, GetColor(200, 200, 0));
						DrawFormatString(j * 60 + 40, i * 60 + 40, GetColor(255, 255, 255), "%d", map[i][j]);
					}
					else if (count > map[i][j]) {
						DrawCircle(j * 60 + 30, i * 60 + 30, 30, GetColor(200, 0, 0));
						DrawFormatString(j * 60 + 40, i * 60 + 40, GetColor(255, 255, 255), "%d", map[i][j]);
						shortMap[i][j] = true;
					}
					else if (count < map[i][j]) {
						DrawCircle(j * 60 + 30, i * 60 + 30, 30, GetColor(0, 0, 200));
						DrawFormatString(j * 60 + 40, i * 60 + 40, GetColor(255, 255, 255), "%d", map[i][j]);
					}
				}
				//�������Ȃ����d�@
				else if (map[i][j] < 20) {
					//���d�@
					if (count == map[i][j] - 10) {
						DrawBox(j * 60, i * 60, (j + 1) * 60, (i + 1) * 60, GetColor(200, 200, 0), true);
						DrawFormatString(j * 60 + 40, i * 60 + 40, GetColor(255, 255, 255), "%d", map[i][j] - 10);
					}
					else if (count > map[i][j] - 10) {
						DrawBox(j * 60, i * 60, (j + 1) * 60, (i + 1) * 60, GetColor(200, 0, 0), true);
						DrawFormatString(j * 60 + 40, i * 60 + 40, GetColor(255, 255, 255), "%d", map[i][j] - 10);
						shortMap[i][j] = true;
					}
					else if (count < map[i][j] - 10) {
						DrawBox(j * 60, i * 60, (j + 1) * 60, (i + 1) * 60, GetColor(0, 0, 200), true);
						DrawFormatString(j * 60 + 40, i * 60 + 40, GetColor(255, 255, 255), "%d", map[i][j] - 10);
					}
				}
			}
			else if (map[i][j] == 20) {
				DrawBox(j * 60 + 40, i * 60, (j + 1) * 60 - 40, (i + 1) * 60, GetColor(200, 200, 0), true);
			}
			else if (map[i][j] == 21) {
				DrawBox(j * 60, i * 60 + 40, (j + 1) * 60, (i + 1) * 60 - 40, GetColor(200, 200, 0), true);
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
