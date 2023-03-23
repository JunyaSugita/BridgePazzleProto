#pragma once
#include "DxLib.h"
#include "GrovalSetting.h"

//進む方向用
enum MoveDirection
{
	NONE,//進まない
	LEFT,//左
	UP,//上
	RIGHT,//右
	DOWN,//下
};


class Field
{
public:
	Field();
	~Field();

public:
	void Initialize();
	void Update();
	void Draw(int wide, int height);

	/// <summary>
	/// 指定座標のマップチップ番号の取得
	/// </summary>
	/// <param name="x">指定座標</param>
	/// <param name="y">指定座標</param>
	/// <returns>マップチップ番号</returns>
	int GetMapNum(int x, int y);

	/// <summary>
	/// 指定座標にマップチップ番号をセット
	/// </summary>
	/// <param name="x">指定座標</param>
	/// <param name="y">指定座標</param>
	/// <param name="num">セットしたいマップチップ番号</param>
	void SetMapNum(int x, int y, int num);

	//進める場所か返す
	static bool CanMoveGrid(int y, int x, int moveDirection);
	//playerがブロックとか押す用
	static bool PullBlock(int y, int x, int moveDirection);
	//押せるかどうかだけ（移動したりはしない）
	static bool GetPullBlock(int y, int x, int moveDirection);

	/// <summary>
	/// フィールドの座標をセットする
	/// </summary>
	void SetPos(int x, int y);

public:
	int map[gridY][gridX];
	bool shortMap[gridY][gridX];

	//アンドゥ用
	static const int ANDO_MAP_CONST = 50;
	int andoMap[ANDO_MAP_CONST][gridY][gridX];
	bool andoMapActive[ANDO_MAP_CONST];
	bool isAndo;

	//グリッドの長さ
	static const int gridLength = 100;

	//枠内での座標
	Vector2 pos;
};

