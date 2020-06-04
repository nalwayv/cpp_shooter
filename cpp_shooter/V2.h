#pragma once

#include <SFML/Graphics.hpp>


namespace game {
	float v2_dot(sf::Vector2f v1, sf::Vector2f v2);
	float v2_len(sf::Vector2f v1);
	float v2_len_sq(sf::Vector2f v1);
	float v2_angle(sf::Vector2f v1);

	float v2_distance_between(sf::Vector2f v1, sf::Vector2f v2);
	float v2_cross(sf::Vector2f v1, sf::Vector2f v2);
	float v2_angle_to(sf::Vector2f v1, sf::Vector2f v2);
	float v2_angle_to_point(sf::Vector2f v1, sf::Vector2f v2);

	sf::Vector2f v2_normal(sf::Vector2f v1, sf::Vector2f v2);
	sf::Vector2f v2_set_rotation(float by);
	sf::Vector2f v2_rotation_by(sf::Vector2f v1, float degrees);
	sf::Vector2f v2_set_len(sf::Vector2f v1, float len);
	sf::Vector2f v2_set_ang(sf::Vector2f v1, float ang);
	sf::Vector2f v2_unit(sf::Vector2f v1);
}

