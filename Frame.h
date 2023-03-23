#pragma once
#include "Field.h"
#include <memory>
#include <vector>
#include "Vector2.h"
#include "GrovalSetting.h"
#include "Generator.h"

class Frame
{
private:
	//大枠の縦と横の数（仮）
	int fieldFrameWidth = 3;
	int fieldFrameHeight = 3;
	//大枠の総数
	int fieldFrameNum = fieldFrameWidth * fieldFrameHeight;

	//枠の横の最大数
	static const int MaxFrameX = 3;
	//枠の縦の最大数
	static const int MaxFrameY = 3;


	/*static const int layerFrameWidth = 3;
	static const int layerFrameHeight = 3;
	static const int layerFrameNum = layerFrameWidth * layerFrameHeight;*/

public:

	//デストラクタ
	~Frame();
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Draw();

	//フィールドの中身をセットする関数

public:

	void SetFreamLayerNum();
	bool GetisSelect();

private:

	//フレームの中のフィールドの配列
	std::vector<std::vector<std::unique_ptr <Field>>> fields_;
	std::vector<std::unique_ptr <Field>> fieldInTheFrame[MaxFrameY][MaxFrameX] = {};

	std::vector<std::vector<std::unique_ptr <Generator>>> generators_;
	//std::vector<std::unique_ptr <Generator>> fieldInTheFrame[MaxFrameY][MaxFrameX] = {};


	Generator* generator_;

	int mouseX, mouseY;
	


public: //ゲッター

	const int GetFieldFrameWidth() { return fieldFrameWidth; }
	const int GetFieldFrameHeight() { return fieldFrameHeight; }
	const int GetFieldFrameNum() { return fieldFrameNum; }


};

