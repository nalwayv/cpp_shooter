#include "MathHelp.h"
#include <cmath>

namespace game {
	static float correct_degrees(float d)
	{
		while (d > 360.0f) {
			d -= 360.0f;
		}

		while (d < -360.0f) {
			d += 360.0f;
		}

		return d;
	}

	float deg_2_rad(float d)
	{
		auto degrees = correct_degrees(d);
		float radians = degrees * 0.0174533f;
		return radians;
	}

	float rad_2_deg(float r)
	{
		float degrees = r * 57.295754f;
		degrees = correct_degrees(degrees);
		return degrees;
	}

	float lerp(float from, float to, float weight)
	{
		return from + (to - from) * weight;
	}

	float clamp(float target, float min_v, float max_v)
	{
		if (target < min_v) return min_v;
		if (target > max_v) return max_v;
		return target;
	}
}