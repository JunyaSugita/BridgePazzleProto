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
	int haveNum_;
	bool have_;
};