#pragma once
#include"Util.h"
#include"Field.h"

class Player;

//ステート親クラス
class PlayerState
{
protected:
	//playerのポインタ
	Player* player = nullptr;
	//
	int timer = 0;
	const int timerMax = 10;
	//進む方向
	int moveDireciton = NONE;

public:
	//playerのポインタをセット
	void SetPlayer(Player* player);

	//進む方向
	void SetMoveDirection(int direction) { this->moveDireciton = direction; }
	int GetMoveDirection() { return moveDireciton; }

	//終点を計算
	Vector2 CalculateEndPos(Vector2 startPos, int moveLength);

	virtual void Update() = 0;
	virtual void Draw() = 0;
};

//動いてない
class PlayerStateNotMoving : public PlayerState
{
private:

public:
	void Update() override;
	void Draw() override;
};

//動いている
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
	//変数
private:
	//位置
	Vector2 pos = { 0,0 };
	//ステート
	PlayerState* state = nullptr;
	//
	bool isMoving = false;
	//移動開始,終点地点
	Vector2 startPos = { 0,0 };
	Vector2 endPos = { 0,0 };
	//進む長さ
	const int moveLength = Field::gridLength;
	//最後に押されたキー
	int priorityKey = NONE;
	int moveKey = NONE;

public:


	//関数
private://シングルトン用
	Player() { ; }
	~Player() { ; }
public:
	static Player& GetInstance();
	//コピーコンストラクタを無効
	Player(const Player& obj) = delete;
	//代入演算子も
	Player& operator=(const Player& obj) = delete;

public://ステート
	void ChangeState(PlayerState* state);
	PlayerState* GetState() { return state; }

public:
	//座標
	void SetPos(Vector2 pos) { this->pos = pos; }
	Vector2 GetPos() { return pos; }
	//グリッドで見たときの位置
	void SetPosGrid(int y, int x);
	//addposは、一個右とか指定出来る用
	int GetPosGridX(int addPos = 0);
	int GetPosGridY(int addPos = 0);
	//動いてるかフラグ
	void SetIsMoving(bool is) { this->isMoving = is; }
	bool GetIsMoving() { return isMoving; }
	//始点
	void SetStartPos(Vector2 pos) { this->startPos = pos; }
	Vector2 GetStartPos() { return this->startPos; }
	// 終点
	void SetEndPos(Vector2 pos) { this->endPos = pos; }
	Vector2 GetEndPos() { return this->endPos; }
	//最後に押されたキー
	void SetMoveKey(int key) { moveKey = key; }
	int GetMoveKey() { return moveKey; }
	//進む長さ
	int GetMoveLength() { return moveLength; }
	//移動終わった時に呼び出す
	void MoveEndFunc();
	//
	void Move(int key);

public:
	void Initialize();
	void Update();
	void Draw();
};

