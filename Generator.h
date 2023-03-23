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

	/// <summary>
	/// 発電機同士を繋げる
	/// </summary>
	void ConnectGenerator();

	//離した発電機の配線を解除
	void Disconnectgenerator(int mouseMapPointX, int mouseMapPointY);

public:
	Field* field_;
	//int mouseX_, mouseY_;
	//int mouseMapPointX, mouseMapPointY;
	
	int haveNum_;
	bool have_;
	int oldHavePosX_, oldHavePosY_;

	//更新フラグ
	bool isUpdate = false;
};