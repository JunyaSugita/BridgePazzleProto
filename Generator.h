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

public:
	Field* field_;
	int mouseX, mouseY;
	int mouseMapPointX, mouseMapPointY;

	int haveNum_;
	bool have_;
	int oldHavePosX_, oldHavePosY_;
};