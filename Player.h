#pragma once
#include"Util.h"
#include"Field.h"

class Player;

//�X�e�[�g�e�N���X
class PlayerState
{
protected:
	//player�̃|�C���^
	Player* player = nullptr;
	//
	int timer = 0;
	const int timerMax = 10;
	//�i�ޕ���
	int moveDireciton = NONE;

public:
	//player�̃|�C���^���Z�b�g
	void SetPlayer(Player* player);

	//�i�ޕ���
	void SetMoveDirection(int direction) { this->moveDireciton = direction; }
	int GetMoveDirection() { return moveDireciton; }

	//�I�_���v�Z
	Vector2 CalculateEndPos(Vector2 startPos, int moveLength);

	virtual void Update() = 0;
	virtual void Draw() = 0;
};

//�����ĂȂ�
class PlayerStateNotMoving : public PlayerState
{
private:

public:
	void Update() override;
	void Draw() override;
};

//�����Ă���
class PlayerStateMoving : public PlayerState
{
private:

public:
	void Update() override;
	void Draw() override;
};


//---------------
class Player final
{
	//�ϐ�
private:
	//�ʒu
	Vector2 pos = { 0,0 };
	//�X�e�[�g
	PlayerState* state = nullptr;
	//
	bool isMoving = false;
	//�ړ��J�n,�I�_�n�_
	Vector2 startPos = { 0,0 };
	Vector2 endPos = { 0,0 };
	//�i�ޒ���
	const int moveLength = Field::gridLength;
	//�Ō�ɉ����ꂽ�L�[
	int priorityKey = NONE;
	int moveKey = NONE;

public:


	//�֐�
private://�V���O���g���p
	Player() { ; }
	~Player() { ; }
public:
	static Player& GetInstance();
	//�R�s�[�R���X�g���N�^�𖳌�
	Player(const Player& obj) = delete;
	//������Z�q��
	Player& operator=(const Player& obj) = delete;

public://�X�e�[�g
	void ChangeState(PlayerState* state);
	PlayerState* GetState() { return state; }

public:
	//���W
	void SetPos(Vector2 pos) { this->pos = pos; }
	Vector2 GetPos() { return pos; }
	//�O���b�h�Ō����Ƃ��̈ʒu
	void SetPosGrid(int y, int x);
	//addpos�́A��E�Ƃ��w��o����p
	int GetPosGridX(int addPos = 0);
	int GetPosGridY(int addPos = 0);
	//�����Ă邩�t���O
	void SetIsMoving(bool is) { this->isMoving = is; }
	bool GetIsMoving() { return isMoving; }
	//�n�_
	void SetStartPos(Vector2 pos) { this->startPos = pos; }
	Vector2 GetStartPos() { return this->startPos; }
	// �I�_
	void SetEndPos(Vector2 pos) { this->endPos = pos; }
	Vector2 GetEndPos() { return this->endPos; }
	//�Ō�ɉ����ꂽ�L�[
	void SetMoveKey(int key) { moveKey = key; }
	int GetMoveKey() { return moveKey; }
	//�i�ޒ���
	int GetMoveLength() { return moveLength; }
	//�ړ��I��������ɌĂяo��
	void MoveEndFunc();
	//
	void Move(int key);

public:
	void Initialize();
	void Update();
	void Draw();
};

