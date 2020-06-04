#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include "Line.h"
#include "Obb.h"
#include "Circle.h"

namespace game {
	class Player
	{
	private:
		sf::Vector2f position_;
		sf::Vector2f velocity_;
		sf::Vector2f mouse_pos_;
		sf::Vector2f size_;
		sf::Vector2f target_pos_;

		Line direction_line_;
		Line angle_line_;
		Line fov_line_up_;
		Line fov_line_down_;
		Line target_line_;

		float speed_;
		float max_speed_;
		float angle_;
		float friction_;
		float fov_;

		bool is_debug_mode_;
		bool is_active_;
		bool is_moving_up_;
		bool is_moving_down_;
		bool is_moving_left_;
		bool is_moving_right_;
		bool has_target_;

		Circle circle_shape_;

		OBB obb_shape_;

		sf::Sprite sprite_;

	public:
		Player(sf::Vector2f pos);

		const OBB& get_obb_shape() const;
		
		sf::Vector2f get_position()const;

		void set_textue(const sf::Texture& texture);
		void set_mouse_pos(sf::Vector2f new_mouse_pos);
		
		float get_angle()const;

		void set_velocity(sf::Vector2f new_velocity);
		sf::Vector2f get_velocity() const;

		void check_target(const OBB& target);
		
		void screen_clamp(float width, float height);
		void input(const std::map<sf::Keyboard::Key, bool>& key_map);
		void update(float dt);
		void draw(sf::RenderWindow& window);

	};
}

