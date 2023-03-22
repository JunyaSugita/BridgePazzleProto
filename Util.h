#pragma once
#include"Vector2.h"

bool CheckHitBoxAndBox(Vector2 pos, Vector2 length, Vector2 pos2, Vector2 length2);

//ê¸å`ï‚äÆ
Vector2 LerpVec2(const Vector2& v1, const Vector2& v2, float t);

//
float EaseIn(float t);

float EaseOut(float t);