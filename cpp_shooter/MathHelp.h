#pragma once

namespace game {
	//float correct_degrees(float d);
	float deg_2_rad(float d);
	float rad_2_deg(float r);
	float lerp(float from, float to, float weight);
	float clamp(float target, float min_v, float max_v);
}

