#pragma once
#include "DxLib.h"
#include "GrovalSetting.h"

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

	/// <summary>
	/// フィールドの座標をセットする
	/// </summary>
	void SetPos(int x, int y);

public:
	int map[gridY][gridX];
	bool shortMap[gridY][gridX];

	//グリッドの長さ
	static const int gridLength = 100;

	//枠内での座標
	Vector2 pos;
};

