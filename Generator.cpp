#include "Generator.h"

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
	for (int i = 0; i < gridY; i++) {
		for (int j = 0; j < gridX; j++) {
			if (field_->map[i][j] > 0 && field_->map[i][j] < 20) {
				//�q���茟��
				//��
				for (int k = i - 1; k >= 0; k--) {
					//���d�@��T��
					if (field->map[k][j] < 20 && field->map[k][j] >= 1) {
						//����΂����܂Ő�������
						for (int l = k + 1; l < i; l++) {
							//���̏ꏊ���󔒂Ȃ�c��������
							if (field->map[l][j] == 0) {
								field_->SetMapNum(j, l, 20);
							}
							//���łɉ���������Ώ\���ɂ���
							else if (field->map[l][j] == 21) {
								field_->SetMapNum(j, l, 22);
							}
						}
						break;
					}
					//�ǂȂ�I��
					else if (field->map[k][j] == -1) {
						break;
					}
				}
				//��
				for (int k = i + 1; k < gridY; k++) {
					//���d�@��T��
					if (field->map[k][j] < 20 && field->map[k][j] >= 1) {
						//����΂����܂Ő�������
						for (int l = k - 1; l > i; l--) {
							//���̏ꏊ���󔒂Ȃ�c��������
							if (field->map[l][j] == 0) {
								field_->SetMapNum(j, l, 20);
							}
							//���łɉ���������Ώ\���ɂ���
							else if (field->map[l][j] == 21) {
								field_->SetMapNum(j, l, 22);
							}
						}
						break;
					}
					//�ǂȂ�I��
					else if (field->map[k][j] == -1) {
						break;
					}
				}

				//��
				for (int k = j - 1; k >= 0; k--) {
					//���d�@��T��
					if (field->map[i][k] < 20 && field->map[i][k] >= 1) {
						//����΂����܂Ő�������
						for (int l = k + 1; l < j; l++) {
							//���̏ꏊ���󔒂Ȃ牡��������
							if (field->map[i][l] == 0) {
								field_->SetMapNum(l, i, 21);
							}
							//���łɏc��������Ώ\���ɂ���
							else if (field->map[i][l] == 20) {
								field_->SetMapNum(l, i, 22);
							}
						}
						break;
					}
					//�ǂȂ�I��
					else if (field->map[i][k] == -1) {
						break;
					}
				}
				//�E
				for (int k = j + 1; k < gridX; k++) {
					//���d�@��T��
					if (field->map[i][k] < 20 && field->map[i][k] >= 1) {
						//����΂����܂Ő�������
						for (int l = k - 1; l > j; l--) {
							//���̏ꏊ���󔒂Ȃ牡��������
							if (field->map[i][l] == 0) {
								field_->SetMapNum(l, i, 21);
							}
							//���łɏc��������Ώ\���ɂ���
							else if (field->map[i][l] == 20) {
								field_->SetMapNum(l, i, 22);
							}
						}
						break;
					}
					//�ǂȂ�I��
					else if (field->map[i][k] == -1) {
						break;
					}
				}
			}
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
	mouseMapPointX = mouseX / 100;
	mouseMapPointY = mouseY / 100;

	//���łɂ������Ȃ�
	for (int i = 0; i < gridY; i++) {
		for (int j = 0; j < gridX; j++) {
			if (field_->map[i][j] > 0 && field_->map[i][j] < 20) {
				//�q���茟��
				//��
				for (int k = i - 1; k >= 0; k--) {
					//���d�@��T��
					if (field->map[k][j] < 20 && field->map[k][j] >= 1) {
						//����΂����܂Ő�������
						for (int l = k + 1; l < i; l++) {
							//���̏ꏊ���󔒂Ȃ�c��������
							if (field->map[l][j] == 0) {
								field_->SetMapNum(j, l, 20);
							}
							//���łɉ���������Ώ\���ɂ���
							else if (field->map[l][j] == 21) {
								field_->SetMapNum(j, l, 22);
							}
						}
						break;
					}
					//�ǂȂ�I��
					else if (field->map[k][j] == -1) {
						break;
					}
				}
				//��
				for (int k = i + 1; k < gridY; k++) {
					//���d�@��T��
					if (field->map[k][j] < 20 && field->map[k][j] >= 1) {
						//����΂����܂Ő�������
						for (int l = k - 1; l > i; l--) {
							//���̏ꏊ���󔒂Ȃ�c��������
							if (field->map[l][j] == 0) {
								field_->SetMapNum(j, l, 20);
							}
							//���łɉ���������Ώ\���ɂ���
							else if (field->map[l][j] == 21) {
								field_->SetMapNum(j, l, 22);
							}
						}
						break;
					}
					//�ǂȂ�I��
					else if (field->map[k][j] == -1) {
						break;
					}
				}

				//��
				for (int k = j - 1; k >= 0; k--) {
					//���d�@��T��
					if (field->map[i][k] < 20 && field->map[i][k] >= 1) {
						//����΂����܂Ő�������
						for (int l = k + 1; l < j; l++) {
							//���̏ꏊ���󔒂Ȃ牡��������
							if (field->map[i][l] == 0) {
								field_->SetMapNum(l, i, 21);
							}
							//���łɏc��������Ώ\���ɂ���
							else if (field->map[i][l] == 20) {
								field_->SetMapNum(l, i, 22);
							}
						}
						break;
					}
					//�ǂȂ�I��
					else if (field->map[i][k] == -1) {
						break;
					}
				}
				//�E
				for (int k = j + 1; k < gridX; k++) {
					//���d�@��T��
					if (field->map[i][k] < 20 && field->map[i][k] >= 1) {
						//����΂����܂Ő�������
						for (int l = k - 1; l > j; l--) {
							//���̏ꏊ���󔒂Ȃ牡��������
							if (field->map[i][l] == 0) {
								field_->SetMapNum(l, i, 21);
							}
							//���łɏc��������Ώ\���ɂ���
							else if (field->map[i][l] == 20) {
								field_->SetMapNum(l, i, 22);
							}
						}
						break;
					}
					//�ǂȂ�I��
					else if (field->map[i][k] == -1) {
						break;
					}
				}
			}
		}
	}

	//�N���b�N���Ă��鎞
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		//�N���b�N�����u��
		if (have_ == false) {
			//���񂾏ꏊ���L�^
			oldHavePosX_ = mouseMapPointX;
			oldHavePosY_ = mouseMapPointY;

			//�����Ă��鐔�����L�^
			haveNum_ = field_->GetMapNum(mouseMapPointX, mouseMapPointY);
			
			//�������镨�Ȃ�
			if (haveNum_ > 0 && haveNum_ <= 9) {
				//�����Ă���t���O�𗧂Ă�
				have_ = true;
				//�}�b�v��񂩂玝���グ�������폜
				field_->SetMapNum(mouseMapPointX, mouseMapPointY, 0);

				//�q���茟��
				//��
				for (int i = mouseMapPointY - 1; i >= 0; i--) {
					if (field_->GetMapNum(mouseMapPointX, i) == 20) {
						field_->SetMapNum(mouseMapPointX, i,0);
					}
					else if (field_->GetMapNum(mouseMapPointX, i) == 22) {
						field_->SetMapNum(mouseMapPointX, i, 21);
					}
					else {
						break;
					}
				}
				//��
				for (int i = mouseMapPointY + 1; i < gridY; i++) {
					if (field_->GetMapNum(mouseMapPointX, i) == 20) {
						field_->SetMapNum(mouseMapPointX, i, 0);
					}
					else if (field_->GetMapNum(mouseMapPointX, i) == 22) {
						field_->SetMapNum(mouseMapPointX, i, 21);
					}
					else {
						break;
					}
				}
				//��
				for (int i = mouseMapPointX - 1; i >= 0; i--) {
					if (field_->GetMapNum(i, mouseMapPointY) == 21) {
						field_->SetMapNum(i, mouseMapPointY, 0);
					}
					else if (field_->GetMapNum(i, mouseMapPointY) == 22) {
						field_->SetMapNum(i, mouseMapPointY, 20);
					}
					else {
						break;
					}
				}
				//��
				for (int i = mouseMapPointX + 1; i < gridY; i++) {
					if (field_->GetMapNum(i, mouseMapPointY) == 21) {
						field_->SetMapNum(i, mouseMapPointY, 0);
					}
					else if (field_->GetMapNum(i, mouseMapPointY) == 22) {
						field_->SetMapNum(i, mouseMapPointY, 20);
					}
					else {
						break;
					}
				}
					
				

			}
		}
	}
	//�N���b�N���Ă��Ȃ��Ď����Ă���t���O��true�̎�
	//(���d�@��u���Ƃ�)
	else if(have_ == true){
		//���d�@��u���ꏊ���󔒂̏ꏊ�ł͖�����
		if (field_->GetMapNum(mouseMapPointX, mouseMapPointY) != 0) {
			field_->SetMapNum(oldHavePosX_, oldHavePosY_, haveNum_);
			haveNum_ = 0;
			have_ = false;
		}
		//���d�@��u���ꏊ���󔒂̎�
		else {
			field_->SetMapNum(mouseMapPointX, mouseMapPointY, haveNum_);
			haveNum_ = 0;
			have_ = false;
		}
	}
}

void Generator::Draw()
{
	if (have_ == true) {
		DrawCircle(mouseX ,mouseY, 50, GetColor(255, 255, 255));
	}
}
