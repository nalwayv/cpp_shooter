#pragma once
#include <SFML/Graphics.hpp>

namespace game {
	struct Rectangle {
		sf::Vector2f position;
		sf::Vector2f size;

		Rectangle() {};
		Rectangle(sf::Vector2f pos, sf::Vector2f s)
			:position(pos), size(s) {};


		sf::Vector2f get_min() const;
		sf::Vector2f get_max() const;
		void draw(sf::RenderWindow& window, sf::Color color);
	};
}

