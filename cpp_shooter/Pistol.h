#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Projectile.h"
#include "Obb.h"

namespace game {

	enum class PistolState {
		IS_RELOADING,
		IS_SHOOTING,
		NONE,
	};

	class Pistol
	{
	private:
		sf::Vector2f position_;
		float angle_;

		int max_bullet_count_;
		int bullet_count_;

		float current_time_;
		float max_time_;
		float projectile_speed_;

		bool can_shoot_;
		bool is_active_;
		bool is_reloading_;
		bool is_shooting_;

		std::vector<Projectile> projectiles_;

		OBB obb_shape_;

		PistolState pistol_state_;

		sf::Texture projectile_texture_;

	public:
		Pistol(sf::Vector2f position, float angle);
		

		sf::Vector2f get_position()const;
		void set_position(sf::Vector2f new_pos);

		const OBB& get_obb_shape() const;

		void set_angle(float new_angle);
		float get_angle() const;

		void set_texture(const sf::Texture& texture);


		std::vector<Projectile> get_projectiles()const;
		
		void shoot();
		void reload();

		void filter_inactive_bullets();

		void draw(sf::RenderWindow & window);
		void update(float dt);
	};
}

