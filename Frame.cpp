#include "Frame.h"

Frame::~Frame()
{
	delete generator_;
}

void Frame::Initialize()
{
	//�������
	for(int i = 0; i < this->GetFieldFrameHeight(); i++)
	{
		for(int j = 0; j < this->GetFieldFrameWidth(); j++)
		{
			this->fieldInTheFrame[i][j].clear();

			if(fields_.size())
			{
				fields_[i].clear();
			}
		}
	}

	//�t�B�[���h�̏�����
	for(int i = 0; i < MaxFrameX; i++)
	{
		//�t�B�[���h�^�����Ă��̃x�N�^��ǉ�(�s��ł���i��)
		fields_.push_back(std::vector<std::unique_ptr <Field>>());

		for(int j = 0; j < MaxFrameY; j++)
		{
			std::unique_ptr <Field> field_;
			field_ = std::make_unique<Field>();
			field_->Initialize();
			//���C���[�̗v�f��ǉ�
			fields_[i].push_back(std::move(field_));
		}
	}

	//�t�B�[���h�̍��W��ݒ�
	for(int i = 0; i < MaxFrameX; i++)
	{
		for(int j = 0; j < MaxFrameY; j++)
		{
			fields_[i][j]->SetPos(i,j);
		}
	}

	//���d�̏�����
	for(int i = 0; i < MaxFrameX; i++)
	{
		//�t�B�[���h�^�����Ă��̃x�N�^��ǉ�(�s��ł���i��)
		generators_.push_back(std::vector<std::unique_ptr <Generator>>());

		for(int j = 0; j < MaxFrameY; j++)
		{
			std::unique_ptr <Generator> generator_;
			generator_ = std::make_unique<Generator>();
			generator_->Initialize(fields_[j][i].get());
			//���C���[�̗v�f��ǉ�
			generators_[i].push_back(std::move(generator_));
		}
	}



	//generator_ = new Generator();

	//for(int i = 0; i < MaxFrameX; i++)
	//{
	//	for(int j = 0; j < MaxFrameY; j++)
	//	{
	//		generator_->Initialize(fields_[i][j].get());
	//	}
	//}
}

void Frame::Update()
{
	//�}�E�X���擾
	GetMousePoint(&mouseX, &mouseY);
	

	for(int i = 0; i < MaxFrameX; i++)
	{
		for(int j = 0; j < MaxFrameY; j++)
		{
			fields_[i][j]->Update();
			//generator_->Update(fields_[i][j].get(),mouseX,mouseY, mouseMapPointX, mouseMapPointY);
			generators_[i][j]->Update(fields_[j][i].get(), mouseX, mouseY ,i,j);

		}
	}	

	//generator_->Update(fields_[0][0].get(), mouseX, mouseY, mouseMapPointX, mouseMapPointY);
	/*generators_[0][0]->Update(fields_[0][0].get(), mouseX, mouseY, mouseMapPointX, mouseMapPointY);
	generators_[0][1]->Update(fields_[0][1].get(), mouseX, mouseY, mouseMapPointX, mouseMapPointY);

	fields_[0][0]->Update();
	fields_[0][1]->Update();*/
	//generator_->Update(fields_[0][1].get(), mouseX, mouseY, mouseMapPointX, mouseMapPointY);*/

}

void Frame::Draw()
{
	/*for(int i = 0; i < MaxFrameX; i++)
	{
		for(int j = 0; j < MaxFrameY; j++)
		{
			fields_[i][j]->Draw(i,j);
			generators_[i][j]->Draw(mouseX,mouseY);
		}
	}*/

	fields_[0][0]->Draw(0, 0);
	generators_[0][0]->Draw(mouseX, mouseY);

	fields_[0][1]->Draw(0, 1);
	generators_[0][1]->Draw(mouseX, mouseY);

	fields_[1][0]->Draw(1, 0);
	generators_[1][0]->Draw(mouseX, mouseY);

	fields_[1][1]->Draw(1, 1);
	generators_[1][1]->Draw(mouseX, mouseY);



	DrawFormatString(0, 20, GetColor(0, 0, 255), "mouseX : %d", mouseX);
	DrawFormatString(0, 60, GetColor(0, 0, 255), "mouseY : %d", mouseY);

	DrawFormatString(0, 90, GetColor(0, 255, 0), "generators_ [0][0] isUpdate : %d", generators_[0][0]->isUpdate);
	DrawFormatString(0, 120, GetColor(0, 255, 0), "generators_ [0][1] isUpdate : %d", generators_[0][1]->isUpdate);
	DrawFormatString(0, 150, GetColor(0, 255, 0), "generators_ [1][0] isUpdate : %d", generators_[1][0]->isUpdate);
	DrawFormatString(0, 180, GetColor(0, 255, 0), "generators_ [1][1] isUpdate : %d", generators_[1][1]->isUpdate);

	DrawFormatString(0, 210, GetColor(0, 255, 0), "fields_[0][0]->pos.x : %d", fields_[0][0]->pos.x);
	DrawFormatString(0, 240, GetColor(0, 255, 0), "fields_[0][0]->pos.y : %d", fields_[0][0]->pos.y);
	DrawFormatString(0, 270, GetColor(0, 255, 0), "fields_[0][1]->pos.x : %d", fields_[0][1]->pos.x);
	DrawFormatString(0, 300, GetColor(0, 255, 0), "fields_[0][1]->pos.y : %d", fields_[0][1]->pos.y);
	DrawFormatString(0, 330, GetColor(0, 255, 0), "fields_[1][0]->pos.x : %d", fields_[1][0]->pos.x);
	DrawFormatString(0, 360, GetColor(0, 255, 0), "fields_[1][0]->pos.y : %d", fields_[1][0]->pos.y);

	

}
