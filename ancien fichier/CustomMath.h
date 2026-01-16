#pragma once

struct Vector2
{
	float x;
	float y;
};

namespace CustomMath
{
	float GetDistance(float x1, float y1, float x2, float y2);
}