#include "CustomMath.h"
#include <iostream>

namespace CustomMath {
	float GetDistance(float x1, float y1, float x2, float y2) {
		float distanceX = (x1 - x2) * (x1 - x2);
		float distanceY = (y1 - y2) * (y1 - y2);
		float distance = sqrt(distanceX + distanceY);
		return distance;
	}
}