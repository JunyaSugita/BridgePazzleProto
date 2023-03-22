#include "Util.h"
#include <math.h>


bool CheckHitBoxAndBox(Vector2 pos, Vector2 length, Vector2 pos2, Vector2 length2)
{
	if (pos.x - length.x / 2.0f < pos2.x + length2.x / 2.0f &&
		pos2.x - length2.x / 2.0f < pos.x + length.x / 2.0f &&
		pos.y - length.y / 2.0f < pos2.y + length2.y / 2.0f &&
		pos2.y - length2.y / 2.0f < pos.y + length.y / 2.0f)
	{
		return true;
	}

	return false;
}

Vector2 LerpVec2(const Vector2& v1, const Vector2& v2, float t)
{
	return v1 + t * (v2 - v1);
}

float EaseIn(float t)
{
	return 1 - cos((t * 3.14f) / 2.0f);
}

float EaseOut(float t)
{
	return sin((t * 3.14f) / 2.0f);
}
