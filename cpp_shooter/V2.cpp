#include "V2.h"
#include <cmath>
#include "MathHelp.h";

using sf::Vector2f;
using std::sqrtf;
using std::cosf;
using std::sinf;
using std::atan2f;

namespace game {
	float v2_dot(Vector2f v1, Vector2f v2)
	{
		return (v1.x * v2.x) + (v1.y * v2.y);
	}

	float v2_len(Vector2f v1)
	{
		return sqrtf((v1.x * v1.x) + (v1.y * v1.y));
	}

	float v2_len_sq(Vector2f v1)
	{
		return (v1.x * v1.x) + (v1.y * v1.y);
	}

	float v2_angle(Vector2f v1)
	{
		return atan2f(v1.y, v1.x);
	}

	float v2_distance_between(Vector2f v1, Vector2f v2)
	{
		return sqrtf(v2_len_sq(v1 - v2));
	}

	float v2_cross(Vector2f v1, Vector2f v2)
	{
		return (v1.x * v2.y) - (v1.y * v2.x);
	}

	float v2_angle_to(Vector2f v1, Vector2f v2)
	{
		return atan2f(v2_cross(v1, v2), v2_dot(v1, v2));
	}

	float v2_angle_to_point(Vector2f v1, Vector2f v2)
	{
		return atan2f(v1.y - v2.y, v1.x - v2.x);
	}

	Vector2f v2_normal(Vector2f v1, Vector2f v2)
	{
		return Vector2f(-(v2.y - v1.y), v2.x - v1.x);
	}

	Vector2f v2_set_rotation(float by)
	{
		return Vector2f(cosf(by), sinf(by));
	}

	Vector2f v2_rotation_by(Vector2f v1, float degrees)
	{
		auto r = deg_2_rad(degrees);
		auto c = cosf(r);
		auto s = sinf(r);

		return Vector2f(
			(v1.x * c) - (v1.y * s),
			(v1.x * s) + (v1.y * c)
		);
	}

	Vector2f v2_set_len(Vector2f v1, float len)
	{
		return v2_set_rotation(v2_angle(v1)) * len;
	}

	Vector2f v2_set_ang(Vector2f v1, float ang)
	{
		return v2_set_rotation(ang) * v2_len(v1);
	}

	Vector2f v2_unit(Vector2f v1)
	{
		auto l = v2_len_sq(v1);
		if (l != 0.0f) {
			return v1 / sqrtf(l);
		}
		return Vector2f(0.0f, 0.0f);
	}
}
