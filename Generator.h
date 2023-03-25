#pragma once
#include "DxLib.h"
#include "Field.h"

class Generator {
public:
	Generator();
	~Generator();

public:
	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="field">フィールドクラス</param>
	void Initialize(Field* field);

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="field">フィールドクラス</param>
	void Update(Field* field);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 発電機同士を繋げる
	/// </summary>
	void ConnectGenerator();

	//離した発電機の配線を解除
	void Disconnectgenerator();

public:
	//フィールドclassの情報
	Field* field_;
	//マウス座標
	int mouseX, mouseY;
	//マップチップ上のマウス座標
	int mouseMapPointX, mouseMapPointY;
	//今持っている発電機の数字(廃止され1のみに)
	int haveNum_[gridY][gridX];
	//発電機を持っているかのフラグ
	bool have_;
	//発電機の元の場所の記憶用
	int oldHavePosX_, oldHavePosY_;
};