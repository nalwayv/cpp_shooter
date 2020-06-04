#pragma once
#include <SFML/Graphics.hpp>
#include "Obb.h"

namespace game {
	class Projectile
	{
	private:
		sf::Vector2f position_;
		sf::Vector2f velocity_;

		float speed_;
		float max_speed_;
		float current_life_;
		float max_life_;
		float angle_;

		bool is_active_;
		bool is_debug_;
		bool has_timer_;
		bool has_texture_;

		OBB obb_shape_;
		sf::Sprite sprite_;

	public:

		Projectile(sf::Vector2f position, float acceleration, float angle);

		const OBB& get_collision_shape() const;

		bool get_is_active() const;
		void set_is_active(bool value);

		void set_textue(const sf::Texture& texture);

		void set_position(sf::Vector2f new_pos);
		void set_angle(float new_angle);
		void set_speed(float new_speed);

		void update(float dt);
		void draw(sf::RenderWindow& window);

	};
}

