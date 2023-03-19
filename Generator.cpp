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
	haveNum_ = 0;
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

	//�V���[�g���Ă���ꏊ�̐�������
	for (int i = 0; i < gridY; i++) {
		for (int j = 0; j < gridX; j++) {
			if (field_->shortMap[i][j] == true) {
				//�q���茟��
				//��
				for (int k = i - 1; k >= 0; k--) {
					if (field_->GetMapNum(j, k) == 20) {
						field_->SetMapNum(j, k, 0);
					}
					else {
						break;
					}
				}
				//��
				for (int k = i + 1; k < gridY; k++) {
					if (field_->GetMapNum(j, k) == 20) {
						field_->SetMapNum(j, k, 0);
					}
					else {
						break;
					}
				}
				//��
				for (int k = j - 1; k >= 0; k--) {
					if (field_->GetMapNum(k, i) == 21) {
						field_->SetMapNum(k, i, 0);
					}
					else {
						break;
					}
				}
				//��
				for (int k = j + 1; k < gridY; k++) {
					if (field_->GetMapNum(k, i) == 21) {
						field_->SetMapNum(k, i, 0);
					}
					else {
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
					else {
						break;
					}
				}
				//��
				for (int i = mouseMapPointY + 1; i < gridY; i++) {
					if (field_->GetMapNum(mouseMapPointX, i) == 20) {
						field_->SetMapNum(mouseMapPointX, i, 0);
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
					else {
						break;
					}
				}
				//��
				for (int i = mouseMapPointX + 1; i < gridY; i++) {
					if (field_->GetMapNum(i, mouseMapPointY) == 21) {
						field_->SetMapNum(i, mouseMapPointY, 0);
					}
					else {
						break;
					}
				}
					
				//���łɂ������Ȃ�
				for (int i = 0; i < gridY; i++) {
					for (int j = 0; j < gridX; j++) {
						if (field_->map[i][j] > 0 && field_->map[i][j] < 20) {
							//�q���茟��
							//��
							for (int k = i - 1; k >= 0; k--) {
								if (field->map[k][j] < 20 && field->map[k][j] >= 1) {
									for (int l = k + 1; l < i; l++) {
										field_->SetMapNum(j, l, 20);
									}
									break;
								}
								else if (field->map[k][j] != 0) {
									break;
								}
							}
							//��
							for (int k = i + 1; k < gridY; k++) {
								if (field->map[k][j] < 20 && field->map[k][j] >= 1) {
									for (int l = k - 1; l > i; l--) {
										field_->SetMapNum(j, l, 20);
									}
									break;
								}
								else if (field->map[k][j] != 0) {
									break;
								}
							}

							//��
							for (int k = j - 1; k >= 0; k--) {
								if (field->map[i][k] < 20 && field->map[i][k] >= 1) {
									for (int l = k + 1; l < j; l++) {
										field_->SetMapNum(l, i, 21);
									}
									break;
								}
								else if (field->map[i][k] != 0) {
									break;
								}
							}
							//�E
							for (int k = j + 1; k < gridX; k++) {
								if (field->map[i][k] < 20 && field->map[i][k] >= 1) {
									for (int l = k - 1; l > j; l--) {
										field_->SetMapNum(l, i, 21);
									}
									break;
								}
								else if (field->map[i][k] != 0) {
									break;
								}
							}
						}
					}
				}

			}
		}
	}
	else if(have_ == true){
		if (field_->GetMapNum(mouseMapPointX, mouseMapPointY) != 0) {
			field_->SetMapNum(oldHavePosX_, oldHavePosY_, haveNum_);
			haveNum_ = 0;
			have_ = false;

			//�q���茟��
			//��
			for (int i = oldHavePosY_ - 1; i >= 0; i--) {
				if (field->map[i][oldHavePosX_] < 20 && field->map[i][oldHavePosX_] >= 1) {
					for (int j = i + 1; j < oldHavePosY_; j++) {
						field_->SetMapNum(oldHavePosX_, j, 20);
					}
					break;
				}
				else if (field->map[i][oldHavePosX_] != 0) {
					break;
				}
			}
			//��
			for (int i = oldHavePosY_ + 1; i < gridY; i++) {
				if (field->map[i][oldHavePosX_] < 20 && field->map[i][oldHavePosX_] >= 1) {
					for (int j = i - 1; j > oldHavePosY_; j--) {
						field_->SetMapNum(oldHavePosX_, j, 20);
					}
					break;
				}
				else if (field->map[i][oldHavePosX_] != 0) {
					break;
				}
			}

			//��
			for (int i = oldHavePosX_ - 1; i >= 0; i--) {
				if (field->map[oldHavePosY_][i] < 20 && field->map[oldHavePosY_][i] >= 1) {
					for (int j = i + 1; j < oldHavePosX_; j++) {
						field_->SetMapNum(j, oldHavePosY_, 21);
					}
					break;
				}
				else if (field->map[oldHavePosY_][i] != 0) {
					break;
				}
			}
			//�E
			for (int i = oldHavePosX_ + 1; i < gridX; i++) {
				if (field->map[oldHavePosY_][i] < 20 && field->map[oldHavePosY_][i] >= 1) {
					for (int j = i - 1; j > oldHavePosX_; j--) {
						field_->SetMapNum(j, oldHavePosY_, 21);
					}
					break;
				}
				else if (field->map[oldHavePosY_][i] != 0) {
					break;
				}
			}
		}
		else {
			field_->SetMapNum(mouseMapPointX, mouseMapPointY, haveNum_);
			haveNum_ = 0;
			have_ = false;

			//�q���茟��
			//��
			for (int i = mouseMapPointY - 1; i >= 0; i--) {
				if (field->map[i][mouseMapPointX] < 20 && field->map[i][mouseMapPointX] >= 1) {
					for (int j = i + 1; j < mouseMapPointY; j++) {
						field_->SetMapNum(mouseMapPointX, j, 20);
					}
					break;
				}
				else if (field->map[i][mouseMapPointX] != 0) {
					break;
				}
			}
			//��
			for (int i = mouseMapPointY + 1; i < gridY; i++) {
				if (field->map[i][mouseMapPointX] < 20 && field->map[i][mouseMapPointX] >= 1) {
					for (int j = i - 1; j > mouseMapPointY; j--) {
						field_->SetMapNum(mouseMapPointX, j, 20);
					}
					break;
				}
				else if (field->map[i][mouseMapPointX] != 0) {
					break;
				}
			}

			//��
			for (int i = mouseMapPointX - 1; i >= 0; i--) {
				if (field->map[mouseMapPointY][i] < 20 && field->map[mouseMapPointY][i] >= 1) {
					for (int j = i + 1; j < mouseMapPointX; j++) {
						field_->SetMapNum(j, mouseMapPointY, 21);
					}
					break;
				}
				else if (field->map[mouseMapPointY][i] != 0) {
					break;
				}
			}
			//�E
			for (int i = mouseMapPointX + 1; i < gridX; i++) {
				if (field->map[mouseMapPointY][i] < 20 && field->map[mouseMapPointY][i] >= 1) {
					for (int j = i - 1; j > mouseMapPointX; j--) {
						field_->SetMapNum(j, mouseMapPointY, 21);
					}
					break;
				}
				else if (field->map[mouseMapPointY][i] != 0) {
					break;
				}
			}
		}
	}
}

void Generator::Draw()
{
	if (have_ == true) {
		DrawCircle(mouseX ,mouseY, 50, GetColor(255, 255, 255));
		DrawFormatString(mouseX, mouseY, GetColor(0, 0, 0), "%d", haveNum_);
	}
}
