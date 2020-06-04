#include "Circle.h"

using sf::RenderWindow;
using sf::CircleShape;
using sf::Color;

namespace game {
	void Circle::draw(RenderWindow& window, Color color)
	{
		CircleShape c;
		c.setPosition(position);
		c.setRadius(radius);
		c.setFillColor(Color::Transparent);
		c.setOutlineColor(color);
		c.setOutlineThickness(1.0f);
		c.setOrigin(radius, radius);

		window.draw(c);
	}
}
