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
	void Draw();

	int GetMapNum(int x, int y);
	void SetMapNum(int x, int y, int num);

public:
	int map[gridY][gridX];
};

