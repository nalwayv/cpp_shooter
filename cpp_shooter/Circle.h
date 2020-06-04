#pragma once
#include <SFML/Graphics.hpp>

namespace game {
	struct Circle {
		sf::Vector2f position;
		float radius = 0.0f;

		Circle() {};
		Circle(sf::Vector2f pos, float rad) :position(pos), radius(rad) {};
		void draw(sf::RenderWindow& window, sf::Color color);
	};
}
