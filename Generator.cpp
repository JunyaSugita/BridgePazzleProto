#include "Generator.h"
#include "Player.h"

Generator::Generator()
{
}

Generator::~Generator()
{
}

void Generator::Initialize(Field* field)
{
	field_ = field;
	have_ = false;

	//���łɂ������Ȃ�
	ConnectGenerator();

	//�ŏ��̏����L�^
	field_->andoMapActive[0] = true;
	for (int j = 0; j < gridY * panelY; j++) {
		for (int k = 0; k < gridX * panelX; k++) {
			field_->andoMap[0][j][k] = field_->map[j][k];
			field_->playerPos[0] = Vector2(25, 25);
		}
	}
}

void Generator::Update(Field* field)
{
	//�t�B�[���h���擾
	field_ = field;
	//�}�E�X���擾
	GetMousePoint(&mouseX, &mouseY);
	//�}�E�X�����}�b�v�`�b�v���W��
	mouseMapPointX = mouseX / (gridX * 50);
	mouseMapPointY = mouseY / (gridY * 50);

	//�q���������
	Disconnectgenerator();

	//���łɂ������Ȃ�
	ConnectGenerator();

	//�O�t���[���Ɣ��d�@�̏ꏊ���������ando�p�ɋL�^
	bool dif = false;

	//1�ԐV��������T��
	for (int i = field_->ANDO_MAP_CONST - 1; i >= 0; i--) {
		if (field_->andoMapActive[i] == true) {
			for (int j = 0; j < gridY * panelY; j++) {
				for (int k = 0; k < gridX * panelX; k++) {
					//����Ă��邩����
					if (field_->map[j][k] != field_->andoMap[i][j][k]) {
						dif = true;
					}
				}
			}
			break;
		}
	}
	//�������L�^
	if (dif) {
		for (int i = 0; i < field_->ANDO_MAP_CONST; i++) {
			if (field_->andoMapActive[i] == false) {
				field_->andoMapActive[i] = true;
				for (int j = 0; j < gridY * panelY; j++) {
					for (int k = 0; k < gridX * panelX; k++) {
						field_->andoMap[i][j][k] = field_->map[j][k];
						field_->playerPos[i] = Player::GetInstance().GetEndPos();
					}
				}
				break;
			}
		}
	}

	//�N���b�N���Ă��鎞
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		//�N���b�N�����u��
		if (have_ == false && field_->panelMap[mouseMapPointY][mouseMapPointX] == 1) {
			//���񂾏ꏊ���L�^
			oldHavePosX_ = mouseMapPointX;
			oldHavePosY_ = mouseMapPointY;

			//�����Ă��鐔�����L�^
			for (int i = 0; i < gridX; i++) {
				for (int j = 0; j < gridY; j++) {
					haveNum_[j][i] = field_->GetMapNum(mouseMapPointX * gridX + i, mouseMapPointY * gridY + j);
					field_->SetMapNum(mouseMapPointX * gridX + i, mouseMapPointY * gridY + j, -2);
				}
			}

			//�����Ă���t���O�𗧂Ă�
			have_ = true;
			//�p�l������
			field_->panelMap[mouseMapPointY][mouseMapPointX] = 0;
		}
	}
	//�N���b�N���Ă��Ȃ��Ď����Ă���t���O��true�̎�
	//(���d�@��u���Ƃ�)
	else if (have_ == true) {
		//���d�@��u���ꏊ���󔒂̏ꏊ�ł͖�����
		if (field_->panelMap[mouseMapPointY][mouseMapPointX] != 0) {
			//���d�@�����̈ʒu�ɖ߂�
			//���������ĂȂ����Ƃɂ���

			for (int i = 0; i < gridX; i++) {
				for (int j = 0; j < gridY; j++) {
					field_->SetMapNum(oldHavePosX_ * gridX + i, oldHavePosY_ * gridY + j, haveNum_[j][i]);
					haveNum_[j][i] = 0;
				}
			}

			//�����Ă���t���O��false��
			have_ = false;
			//�p�l������
			field_->panelMap[oldHavePosY_][oldHavePosX_] = 1;
		}
		//���d�@��u���ꏊ���󔒂̎�
		else {
			//���d�@��u��
			//���������ĂȂ����Ƃɂ���
			for (int i = 0; i < gridX; i++) {
				for (int j = 0; j < gridY; j++) {
					field_->SetMapNum(mouseMapPointX * gridX + i, mouseMapPointY * gridY + j, haveNum_[j][i]);
					haveNum_[j][i] = 0;
				}
			}

			//�����Ă���t���O��false��
			have_ = false;
			//�p�l������
			field_->panelMap[mouseMapPointY][mouseMapPointX] = 1;
		}
	}
}

void Generator::Draw()
{
	if (have_ == true) {
		//DrawCircle(mouseX, mouseY, field_->gridLength / 2, GetColor(255, 255, 255));
	}
	else {
		DrawFormatString(100, 0, GetColor(255, 255, 255), "RIGHT_CLICK : ANDO");
	}
}

void Generator::ConnectGenerator()
{
	for (int i = 0; i < gridY * panelY; i++) {
		for (int j = 0; j < gridX * panelX; j++) {
			if (field_->map[i][j] > 0 && field_->map[i][j] < 20) {
				//�q���茟��
				//��
				for (int k = i - 1; k >= 0; k--) {
					//���d�@��T��
					if (field_->map[k][j] < 20 && field_->map[k][j] >= 1) {
						//����΂����܂Ő�������
						for (int l = k + 1; l < i; l++) {
							//���̏ꏊ���󔒂Ȃ�c��������
							if (field_->map[l][j] == 0) {
								field_->SetMapNum(j, l, 20);
							}
							//���łɉ���������Ώ\���ɂ���
							else if (field_->map[l][j] == 21) {
								field_->SetMapNum(j, l, 22);
							}
						}
						break;
					}
					//�ǂȂ�I��
					else if (field_->map[k][j] == -1) {
						break;
					}
				}
				//��
				for (int k = i + 1; k < gridY * panelY; k++) {
					//���d�@��T��
					if (field_->map[k][j] < 20 && field_->map[k][j] >= 1) {
						//����΂����܂Ő�������
						for (int l = k - 1; l > i; l--) {
							//���̏ꏊ���󔒂Ȃ�c��������
							if (field_->map[l][j] == 0) {
								field_->SetMapNum(j, l, 20);
							}
							//���łɉ���������Ώ\���ɂ���
							else if (field_->map[l][j] == 21) {
								field_->SetMapNum(j, l, 22);
							}
						}
						break;
					}
					//�ǂȂ�I��
					else if (field_->map[k][j] == -1) {
						break;
					}
				}

				//��
				for (int k = j - 1; k >= 0; k--) {
					//���d�@��T��
					if (field_->map[i][k] < 20 && field_->map[i][k] >= 1) {
						//����΂����܂Ő�������
						for (int l = k + 1; l < j; l++) {
							//���̏ꏊ���󔒂Ȃ牡��������
							if (field_->map[i][l] == 0) {
								field_->SetMapNum(l, i, 21);
							}
							//���łɏc��������Ώ\���ɂ���
							else if (field_->map[i][l] == 20) {
								field_->SetMapNum(l, i, 22);
							}
						}
						break;
					}
					//�ǂȂ�I��
					else if (field_->map[i][k] == -1) {
						break;
					}
				}
				//�E
				for (int k = j + 1; k < gridX * panelX; k++) {
					//���d�@��T��
					if (field_->map[i][k] < 20 && field_->map[i][k] >= 1) {
						//����΂����܂Ő�������
						for (int l = k - 1; l > j; l--) {
							//���̏ꏊ���󔒂Ȃ牡��������
							if (field_->map[i][l] == 0) {
								field_->SetMapNum(l, i, 21);
							}
							//���łɏc��������Ώ\���ɂ���
							else if (field_->map[i][l] == 20) {
								field_->SetMapNum(l, i, 22);
							}
						}
						break;
					}
					//�ǂȂ�I��
					else if (field_->map[i][k] == -1) {
						break;
					}
				}
			}
		}
	}
}

void Generator::Disconnectgenerator()
{
	for (int i = 0; i < gridY * panelY; i++) {
		for (int j = 0; j < gridX * panelX; j++) {
			if (field_->GetMapNum(j, i) == 20) {
				field_->SetMapNum(j, i, 0);
			}
			if (field_->GetMapNum(j, i) == 21) {
				field_->SetMapNum(j, i, 0);
			}
			if (field_->GetMapNum(j, i) == 22) {
				field_->SetMapNum(j, i, 0);
			}
		}
	}
}
