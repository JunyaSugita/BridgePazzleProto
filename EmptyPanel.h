#pragma once
#include "DxLib.h"
#include "GrovalSetting.h"

//空のパネル
class EmptyPanel
{
public:
	EmptyPanel();
	~EmptyPanel();

public:
	void Initialize();
	void Update();
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

public:
	int map[gridY][gridX];
	bool shortMap[gridY][gridX];
	
	//枠の中で使う座標
	Vector2 pos;
};


