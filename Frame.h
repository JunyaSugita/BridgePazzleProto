#pragma once
#include "Field.h"
#include <memory>
#include <vector>
#include "Vector2.h"

class Frame
{
private:
	//大枠の縦と横の数（仮）
	int fieldFrameWidth = 3;
	int fieldFrameHeight = 3;
	//大枠の総数
	int fieldFrameNum = fieldFrameWidth * fieldFrameHeight;

	/*static const int layerFrameWidth = 3;
	static const int layerFrameHeight = 3;
	static const int layerFrameNum = layerFrameWidth * layerFrameHeight;*/

public:

	//デストラクタ
	~Frame();
	//初期化
	void Initialize();
	//更新
	void Update(char* keys, char* oldkeys, int mouseX, int mouseY, int oldMouseX, int oldMouseY);
	//描画
	void Draw();

	//フィールドの中身をセットする関数
	
	//

	

public:

	void SetFreamLayerNum();
	bool GetisSelect();

private:

	//フレームの中のフィールドの配列
	std::vector<std::vector<std::unique_ptr <Field>>> field_;

public: //ゲッター

	const int GetFieldFrameWidth() { return fieldFrameWidth; }
	const int GetFieldFrameHeight() { return fieldFrameHeight; }
	const int GetFieldFrameNum() { return fieldFrameNum; }


};

