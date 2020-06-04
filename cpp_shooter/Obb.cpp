#include "Obb.h"
#include "V2.h"

using sf::Vector2f;
using sf::RenderWindow;
using sf::Color;
using sf::Vertex;
using std::vector;

namespace game {
	std::vector<Vector2f> OBB::get_shape() const
	{
		const int SIZE = 5;
		Vector2f base_shape[SIZE];
		vector<Vector2f>points(SIZE);

		base_shape[0] = Vector2f(half_extents.x, -half_extents.y);
		base_shape[1] = half_extents;
		base_shape[2] = Vector2f(-half_extents.x, half_extents.y);
		base_shape[3] = Vector2f(-half_extents.x, -half_extents.y);
		base_shape[4] = Vector2f(half_extents.x, -half_extents.y);

		for (int i = 0; i < SIZE; i++) {
			points[i] = v2_rotation_by(base_shape[i], angle);
			points[i] += position;
		}

		return points;
	}

	void OBB::draw(RenderWindow& window, Color color)
	{
		const int SIZE = 5;

		auto shape = get_shape();

		bool ok = false;
		if (shape.size() == SIZE) {
			ok = true;
		}

		if (ok) {

			Vertex base_shape[SIZE];
			for (int idx = 0; idx < SIZE; idx++) {
				base_shape[idx].position = shape[idx];
				base_shape[idx].color = color;
			}

			window.draw(base_shape, SIZE, sf::LinesStrip);
		}
	}
}