#pragma once
#include "DxLib.h"

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
	static const int gridX = 5;
	static const int gridY = 5;

	int map[gridY][gridX];
};

