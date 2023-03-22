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

private:
	//playerがブロックとか押す用
	static bool PullBlock(int y, int x, int moveDirection);

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

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
	static bool CanMoveGrid(int y, int x,int moveDirection);

public:
	//マップ
	static int map[gridY][gridX];

	//グリッドの長さ
	static const int gridLength = 100;
};

