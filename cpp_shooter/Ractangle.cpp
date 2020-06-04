#include "Ractangle.h"
#include <algorithm>

using sf::Vector2f;
using sf::RectangleShape;
using sf::RenderWindow;
using sf::Color;
using std::min;
using std::max;

namespace game {
	Vector2f Rectangle::get_min() const
	{
		Vector2f p1 = position;
		Vector2f p2 = position + size;

		return Vector2f(min(p1.x, p2.x), min(p1.y, p2.y));
	}

	Vector2f Rectangle::get_max() const
	{
		Vector2f p1 = position;
		Vector2f p2 = position + size;

		return Vector2f(max(p1.x, p2.x), max(p1.y, p2.y));
	}

	void Rectangle::draw(RenderWindow& window, Color color)
	{
		RectangleShape shape;
		shape.setPosition(position);
		shape.setSize(size);
		shape.setFillColor(Color::Transparent);
		shape.setOutlineColor(color);
		shape.setOutlineThickness(1.0f);

		window.draw(shape);
	}
}