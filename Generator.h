#pragma once
#include "DxLib.h"
#include "Field.h"

class Generator {
public:
	Generator();
	~Generator();

public:
	void Initialize(Field* field);
	void Update(Field* field);
	void Draw();

public:
	Field* field_;
	int mouseX, mouseY;
	int mouseMapPointX, mouseMapPointY;

	int haveNum_;
	bool have_;
	int oldHavePosX_, oldHavePosY_;
};