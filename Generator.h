#pragma once
#include "DxLib.h"
#include "Field.h"

class Generator {
public:
	Generator();
	~Generator();

public:
	void Initialize(Field* field);
	void Update(Field* field,int mouseX, int mouseY, int mouseMapPointX, int mouseMapPointY, int i, int j);
	void Draw(int mouseX, int mouseY);

public:
	Field* field_;
	int mouseX_, mouseY_;
	//int mouseMapPointX, mouseMapPointY;

	int haveNum_;
	bool have_;
	int oldHavePosX_, oldHavePosY_;

	//更新フラグ
	bool isUpdate = false;
};