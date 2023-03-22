#include "Player.h"
#include "DxLib.h"
#include "KeyboardInput.h"


void PlayerState::SetPlayer(Player* player)
{
	this->player = player;
}

Vector2 PlayerState::CalculateEndPos(Vector2 startPos, int moveLength)
{
	int y = player->GetPosGridY();
	int x = player->GetPosGridX();

	if (player->GetMoveKey() == LEFT)
	{
		Field::PullBlock(y, x - 1, LEFT);
		return { startPos.x - moveLength,startPos.y };
	}
	if (player->GetMoveKey() == UP)
	{
		Field::PullBlock(y - 1, x, UP);
		return { startPos.x,startPos.y - moveLength };
	}
	if (player->GetMoveKey() == RIGHT)
	{
		Field::PullBlock(y, x + 1, RIGHT);
		return { startPos.x + moveLength,startPos.y };
	}
	if (player->GetMoveKey() == DOWN)
	{
		Field::PullBlock(y + 1, x, DOWN);
		return { startPos.x ,startPos.y + moveLength };
	}
	else /*if (player->GetMoveKey() == NONE)*/
	{
		return startPos;
	}
}

//-------------------------------------
void PlayerStateNotMoving::Update()
{
	//�O���ňړ��t���O����������
	if (player->GetIsMoving())
	{
		//�n�_���Z�b�g
		player->SetStartPos(player->GetPos());
		//�I�_���Z�b�g
		player->SetEndPos(CalculateEndPos(player->GetStartPos(), player->GetMoveLength()));

		//�X�e�[�g�ύX
		player->ChangeState(new PlayerStateMoving);
	}
}

void PlayerStateNotMoving::Draw()
{

}

//-------------------------------------
void PlayerStateMoving::Update()
{
	timer++;
	//����(0~1)
	float t = (float)timer / (float)timerMax;
	//���W���X�V
	player->SetPos(LerpVec2(player->GetStartPos(), player->GetEndPos(), EaseOut(t)));

	//���`�⊮���I�������X�e�[�g�ύX
	if (timer >= timerMax)
	{
		player->MoveEndFunc();
	}
}

void PlayerStateMoving::Draw()
{

}


//---------------------------------------------------------------
Player& Player::GetInstance()
{
	static Player instance;
	return instance;
}

void Player::ChangeState(PlayerState* state)
{
	delete this->state;
	this->state = state;
	this->state->SetPlayer(this);
}

void Player::SetPosGrid(int y, int x)
{
	pos = {
		x * (float)Field::gridLength + (float)Field::gridLength / 2.0f,
		y * (float)Field::gridLength + (float)Field::gridLength / 2.0f
	};
}

int Player::GetPosGridX(int addPos)
{
	return (int)pos.x / Field::gridLength + addPos;
}

int Player::GetPosGridY(int addPos)
{
	return (int)pos.y / Field::gridLength + addPos;
}

void Player::MoveEndFunc()
{
	isMoving = false;
	moveKey = NONE;
	ChangeState(new PlayerStateNotMoving);
}

void Player::Initialize()
{
	//�ʒu
	SetPosGrid(0, 0);
	isMoving = false;
	startPos = { 0,0 };
	endPos = { 0,0 };
	moveKey = NONE;

	ChangeState(new PlayerStateNotMoving);
}

void Player::Update()
{
	//�����ƂȂ�Ȃ��i�ړ����ɃL�[�����Ɓj
	if (KeyboardInput::Getinstance().GetKey(KEY_INPUT_LEFT) ||
		KeyboardInput::Getinstance().GetKey(KEY_INPUT_UP) ||
		KeyboardInput::Getinstance().GetKey(KEY_INPUT_RIGHT) ||
		KeyboardInput::Getinstance().GetKey(KEY_INPUT_DOWN))
	{
		int x = GetPosGridX();
		int y = GetPosGridY();

		if (KeyboardInput::Getinstance().GetKey(KEY_INPUT_LEFT) && Field::CanMoveGrid(y, x - 1, LEFT))
		{
			isMoving = true;
			moveKey = (LEFT);
		}
		if (KeyboardInput::Getinstance().GetKey(KEY_INPUT_UP) && Field::CanMoveGrid(y - 1, x, UP))
		{
			isMoving = true;
			moveKey = (UP);
		}
		if (KeyboardInput::Getinstance().GetKey(KEY_INPUT_RIGHT) && Field::CanMoveGrid(y, x + 1, RIGHT))
		{
			isMoving = true;
			moveKey = (RIGHT);
		}
		if (KeyboardInput::Getinstance().GetKey(KEY_INPUT_DOWN) && Field::CanMoveGrid(y + 1, x, DOWN))
		{
			isMoving = true;
			moveKey = (DOWN);
		}
	}
	else
	{
		moveKey = NONE;
	}



	//�X�e�[�g
	state->Update();
}

void Player::Draw()
{
	DrawCircle(pos.x, pos.y, Field::gridLength / 2, GetColor(255, 255, 255));

	//�X�e�[�g
	state->Draw();
}
