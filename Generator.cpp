#include "Generator.h"

Generator::Generator()
{
	//test
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
}

void Generator::Update(Field* field,int mouseX, int mouseY, int mouseMapPointX, int mouseMapPointY,int i,int j)
{
	//�t�B�[���h���擾
	field_ = field;
	

	//�}�E�X�������̎����Ă���t�B�[���h���ɂ��邩�ǂ���
	if(mouseX > field_->pos.x && mouseX < field_->pos.x + 300 && mouseY > field_->pos.y && mouseY  < field_->pos.y + 300)
	{
		isUpdate = true;	
	}
	else
	{
		isUpdate = false;
	}

	//���łɂ������Ȃ�
	ConnectGenerator();

	//�N���b�N���Ă��鎞
	if((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		//�N���b�N�����u��
		if(have_ == false)
		{
			//���񂾏ꏊ���L�^
			oldHavePosX_ = mouseMapPointX;
			oldHavePosY_ = mouseMapPointY;

			//�����Ă��鐔�����L�^
			haveNum_ = field_->GetMapNum(mouseMapPointX, mouseMapPointY);

			//�������镨�Ȃ�
			if(haveNum_ > 0 && haveNum_ <= 9)
			{
				for(int i = 0; i < field_->ANDO_MAP_CONST; i++)
				{
					if(field_->andoMapActive[i] == false)
					{
						for(int j = 0; j < gridY; j++)
						{
							for(int k = 0; k < gridY; k++)
							{
								field_->andoMap[i][j][k] = field_->map[j][k];
								field_->andoMapActive[i] = true;
							}
						}
						break;
					}
				}
				//�����Ă���t���O�𗧂Ă�
				have_ = true;
				//�}�b�v��񂩂玝���グ�������폜
				field_->SetMapNum(mouseMapPointX, mouseMapPointY, 0);

				Disconnectgenerator(mouseMapPointX,mouseMapPointY);

			}
		}
	}
	//�N���b�N���Ă��Ȃ��Ď����Ă���t���O��true�̎�
	//(���d�@��u���Ƃ�)
	else if(have_ == true)
	{
		//���d�@��u���ꏊ���󔒂̏ꏊ�ł͖�����
		if(field_->GetMapNum(mouseMapPointX, mouseMapPointY) != 0)
		{
			for(int i = field_->ANDO_MAP_CONST - 1; i >= 0; i--)
			{
				if(field_->andoMapActive[i] == true)
				{
					field_->andoMapActive[i] = false;
					break;
				}
			}
			//���d�@�����̈ʒu�ɖ߂�
			field_->SetMapNum(oldHavePosX_, oldHavePosY_, haveNum_);
			//���������ĂȂ����Ƃɂ���
			haveNum_ = 0;
			//�����Ă���t���O��false��
			have_ = false;
		}
		//���d�@��u���ꏊ���󔒂̎�
		else
		{

			//�N���b�N����߂��ꏊ�ɔ��d�@��ݒu
			field_->SetMapNum(mouseMapPointX, mouseMapPointY, haveNum_);
			//���������ĂȂ����Ƃɂ���
			haveNum_ = 0;
			//�����Ă���t���O��false��
			have_ = false;
		}
	}
}

void Generator::Draw(int mouseX, int mouseY)
{
	/*if (have_ == true) {
		DrawCircle(mouseX ,mouseY, 30, GetColor(255, 255, 255));
		DrawFormatString(mouseX, mouseY, GetColor(0, 0, 0), "%d", haveNum_);
	}
	else
	{
		DrawFormatString(100, 0, GetColor(255, 255, 255), "RIGHT_CLICK : ANDO");
	}*/
}

void Generator::ConnectGenerator()
{
	for(int i = 0; i < gridY; i++)
	{
		for(int j = 0; j < gridX; j++)
		{
			if(field_->map[i][j] > 0 && field_->map[i][j] < 20)
			{
				//�q���茟��
				//��
				for(int k = i - 1; k >= 0; k--)
				{
					//���d�@��T��
					if(field_->map[k][j] < 20 && field_->map[k][j] >= 1)
					{
						//����΂����܂Ő�������
						for(int l = k + 1; l < i; l++)
						{
							//���̏ꏊ���󔒂Ȃ�c��������
							if(field_->map[l][j] == 0)
							{
								field_->SetMapNum(j, l, 20);
							}
							//���łɉ���������Ώ\���ɂ���
							else if(field_->map[l][j] == 21)
							{
								field_->SetMapNum(j, l, 22);
							}
						}
						break;
					}
					//�ǂȂ�I��
					else if(field_->map[k][j] == -1)
					{
						break;
					}
				}
				//��
				for(int k = i + 1; k < gridY; k++)
				{
					//���d�@��T��
					if(field_->map[k][j] < 20 && field_->map[k][j] >= 1)
					{
						//����΂����܂Ő�������
						for(int l = k - 1; l > i; l--)
						{
							//���̏ꏊ���󔒂Ȃ�c��������
							if(field_->map[l][j] == 0)
							{
								field_->SetMapNum(j, l, 20);
							}
							//���łɉ���������Ώ\���ɂ���
							else if(field_->map[l][j] == 21)
							{
								field_->SetMapNum(j, l, 22);
							}
						}
						break;
					}
					//�ǂȂ�I��
					else if(field_->map[k][j] == -1)
					{
						break;
					}
				}

				//��
				for(int k = j - 1; k >= 0; k--)
				{
					//���d�@��T��
					if(field_->map[i][k] < 20 && field_->map[i][k] >= 1)
					{
						//����΂����܂Ő�������
						for(int l = k + 1; l < j; l++)
						{
							//���̏ꏊ���󔒂Ȃ牡��������
							if(field_->map[i][l] == 0)
							{
								field_->SetMapNum(l, i, 21);
							}
							//���łɏc��������Ώ\���ɂ���
							else if(field_->map[i][l] == 20)
							{
								field_->SetMapNum(l, i, 22);
							}
						}
						break;
					}
					//�ǂȂ�I��
					else if(field_->map[i][k] == -1)
					{
						break;
					}
				}
				//�E
				for(int k = j + 1; k < gridX; k++)
				{
					//���d�@��T��
					if(field_->map[i][k] < 20 && field_->map[i][k] >= 1)
					{
						//����΂����܂Ő�������
						for(int l = k - 1; l > j; l--)
						{
							//���̏ꏊ���󔒂Ȃ牡��������
							if(field_->map[i][l] == 0)
							{
								field_->SetMapNum(l, i, 21);
							}
							//���łɏc��������Ώ\���ɂ���
							else if(field_->map[i][l] == 20)
							{
								field_->SetMapNum(l, i, 22);
							}
						}
						break;
					}
					//�ǂȂ�I��
					else if(field_->map[i][k] == -1)
					{
						break;
					}
				}
			}
		}
	}
}

void Generator::Disconnectgenerator(int mouseMapPointX,int mouseMapPointY)
{
	//�q���茟��
	//��
	for(int i = mouseMapPointY - 1; i >= 0; i--)
	{
		//�c��������
		if(field_->GetMapNum(mouseMapPointX, i) == 20)
		{
			field_->SetMapNum(mouseMapPointX, i, 0);
		}
		//�\���Ȃ牡���ɂ���
		else if(field_->GetMapNum(mouseMapPointX, i) == 22)
		{
			field_->SetMapNum(mouseMapPointX, i, 21);
		}
		//���łȂ���ΏI��
		else
		{
			break;
		}
	}
	//��
	for(int i = mouseMapPointY + 1; i < gridY; i++)
	{
		//�c��������
		if(field_->GetMapNum(mouseMapPointX, i) == 20)
		{
			field_->SetMapNum(mouseMapPointX, i, 0);
		}
		//�\���Ȃ牡���ɂ���
		else if(field_->GetMapNum(mouseMapPointX, i) == 22)
		{
			field_->SetMapNum(mouseMapPointX, i, 21);
		}
		//���łȂ���ΏI��
		else
		{
			break;
		}
	}
	//��
	for(int i = mouseMapPointX - 1; i >= 0; i--)
	{
		//����������
		if(field_->GetMapNum(i, mouseMapPointY) == 21)
		{
			field_->SetMapNum(i, mouseMapPointY, 0);
		}
		//�\���Ȃ�c���ɂ���
		else if(field_->GetMapNum(i, mouseMapPointY) == 22)
		{
			field_->SetMapNum(i, mouseMapPointY, 20);
		}
		//���łȂ���ΏI��
		else
		{
			break;
		}
	}
	//��
	for(int i = mouseMapPointX + 1; i < gridY; i++)
	{
		//����������
		if(field_->GetMapNum(i, mouseMapPointY) == 21)
		{
			field_->SetMapNum(i, mouseMapPointY, 0);
		}
		//�\���Ȃ�c���ɂ���
		else if(field_->GetMapNum(i, mouseMapPointY) == 22)
		{
			field_->SetMapNum(i, mouseMapPointY, 20);
		}
		//���łȂ���ΏI��
		else
		{
			break;
		}
	}
}
