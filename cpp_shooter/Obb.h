#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace game {

	struct OBB {
		sf::Vector2f position;
		sf::Vector2f half_extents;
		float angle = 0.0f;

		OBB() {};
		OBB(sf::Vector2f pos, sf::Vector2f half, float a)
			:position(pos), half_extents(half), angle(a) {};

		std::vector<sf::Vector2f> get_shape() const;
		void draw(sf::RenderWindow& window, sf::Color color);
	};
}

