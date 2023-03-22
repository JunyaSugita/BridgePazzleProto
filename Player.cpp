#include "Player.h"
#include "DxLib.h"
#include "KeyboardInput.h"


void PlayerState::SetPlayer(Player* player)
{
	this->player = player;
}

Vector2 PlayerState::CalculateEndPos(Vector2 startPos, int moveLength)
{
	Vector2 endPos = {};

	if (player->GetMoveKey() == LEFT)
	{
		endPos = { startPos.x - moveLength,startPos.y };
	}
	else if (player->GetMoveKey() == UP)
	{
		endPos = { startPos.x,startPos.y - moveLength };
	}
	else if (player->GetMoveKey() == RIGHT)
	{
		endPos = { startPos.x + moveLength,startPos.y };
	}
	else if (player->GetMoveKey() == DOWN)
	{
		endPos = { startPos.x ,startPos.y + moveLength };
	}
	else
	{
		endPos = startPos;
	}

	return Vector2(endPos);
}

//-------------------------------------
void PlayerStateNotMoving::Update()
{
	//外部で移動フラグがたったら
	if (player->GetIsMoving())
	{
		//始点をセット
		player->SetStartPos(player->GetPos());
		//終点をセット
		player->SetEndPos(CalculateEndPos(player->GetStartPos(), player->GetMoveLength()));

		//ステート変更
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
	//割合(0~1)
	float t = (float)timer / (float)timerMax;
	//座標を更新
	player->SetPos(LerpVec2(player->GetStartPos(), player->GetEndPos(), EaseOut(t)));

	//線形補完が終わったらステート変更
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

int Player::GetPosGridX()
{
	return pos.x / Field::gridLength;
}

int Player::GetPosGridY()
{
	return pos.y / Field::gridLength;
}

void Player::MoveEndFunc()
{
	isMoving = false;
	moveKey = NONE;
	ChangeState(new PlayerStateNotMoving);
}

void Player::Initialize()
{
	//位置
	SetPosGrid(0, 0);
	isMoving = false;
	startPos = { 0,0 };
	endPos = { 0,0 };
	moveKey = NONE;

	ChangeState(new PlayerStateNotMoving);
}

void Player::Update()
{
	if (KeyboardInput::Getinstance().GetKeyTrigger(KEY_INPUT_LEFT) ||
		KeyboardInput::Getinstance().GetKeyTrigger(KEY_INPUT_UP) ||
		KeyboardInput::Getinstance().GetKeyTrigger(KEY_INPUT_RIGHT) ||
		KeyboardInput::Getinstance().GetKeyTrigger(KEY_INPUT_DOWN))
	{
		if (KeyboardInput::Getinstance().GetKeyTrigger(KEY_INPUT_LEFT))
		{
			isMoving = true;
			moveKey = (LEFT);
		}
		if (KeyboardInput::Getinstance().GetKeyTrigger(KEY_INPUT_UP))
		{
			isMoving = true;
			moveKey = (UP);
		}
		if (KeyboardInput::Getinstance().GetKeyTrigger(KEY_INPUT_RIGHT))
		{
			isMoving = true;
			moveKey = (RIGHT);
		}
		if (KeyboardInput::Getinstance().GetKeyTrigger(KEY_INPUT_DOWN))
		{
			isMoving = true;
			moveKey = (DOWN);
		}

		state->CalculateEndPos(pos, moveLength);
	}
	else if (
		KeyboardInput::Getinstance().GetKey(KEY_INPUT_LEFT) ||
		KeyboardInput::Getinstance().GetKey(KEY_INPUT_UP) ||
		KeyboardInput::Getinstance().GetKey(KEY_INPUT_RIGHT) ||
		KeyboardInput::Getinstance().GetKey(KEY_INPUT_DOWN)
		)
	{
		if (KeyboardInput::Getinstance().GetKey(KEY_INPUT_LEFT))
		{
			isMoving = true;
			moveKey = (LEFT);
		}
		if (KeyboardInput::Getinstance().GetKey(KEY_INPUT_UP))
		{
			isMoving = true;
			moveKey = (UP);
		}
		if (KeyboardInput::Getinstance().GetKey(KEY_INPUT_RIGHT))
		{
			isMoving = true;
			moveKey = (RIGHT);
		}
		if (KeyboardInput::Getinstance().GetKey(KEY_INPUT_DOWN))
		{
			isMoving = true;
			moveKey = (DOWN);
		}
	}
	else
	{
		moveKey = NONE;
	}

	//ステート
	state->Update();
}

void Player::Draw()
{
	DrawCircle(pos.x, pos.y, Field::gridLength / 2, GetColor(255, 255, 255));

	//ステート
	state->Draw();
}
