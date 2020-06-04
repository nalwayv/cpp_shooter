#pragma once
#include <SFML/Graphics.hpp>

namespace game {

	struct Line {
		sf::Vector2f start;
		sf::Vector2f end;

		Line() {};
		Line(sf::Vector2f s, sf::Vector2f e):start(s), end(e) {};


		void draw(sf::RenderWindow& window, sf::Color color);

	};

	//void line_reset(Line& line);
	//void line_draw(const Line& line, sf::RenderWindow& window, sf::Color color);
	//sf::Vector2f line_get_point_at(const Line& line, float t);
}

