#include "Pistol.h"
#include <iostream>
#include "MathHelp.h"

using sf::Vector2f;
using std::vector;

namespace game {
	Pistol::Pistol(Vector2f position, float angle)
		:position_(position),
		angle_(angle),
		max_bullet_count_(5),
		bullet_count_(5),
		current_time_(0.0f),
		max_time_(0.5f),
		projectile_speed_(50.0f),
		is_active_(true),
		is_reloading_(false),
		is_shooting_(false),
		can_shoot_(true),
		projectiles_(),
		pistol_state_(PistolState::NONE),
		obb_shape_(position, Vector2f(10.f, 10.f), angle)
	{
	}

	Vector2f Pistol::get_position() const
	{
		return position_;
	}

	void Pistol::set_position(Vector2f new_pos)
	{
		position_ = new_pos;
	}

	const OBB& Pistol::get_obb_shape() const
	{
		return obb_shape_;
	}

	void Pistol::set_angle(float new_angle)
	{
		angle_ = new_angle;
	}

	float Pistol::get_angle() const
	{
		return angle_;
	}

	void Pistol::set_texture(const sf::Texture& texture)
	{
		projectile_texture_ = texture;
	}

	vector<Projectile> Pistol::get_projectiles() const
	{
		return projectiles_;
	}

	void Pistol::shoot()
	{
		pistol_state_ = PistolState::IS_SHOOTING;

	}

	void Pistol::reload()
	{
		pistol_state_ = PistolState::IS_RELOADING;
	}

	void Pistol::filter_inactive_bullets()
	{
		if (projectiles_.size() != 0) {
			projectiles_.erase(
				std::remove_if(
					projectiles_.begin(), 
					projectiles_.end(), 
					[](Projectile p) {return !p.get_is_active(); }),
				projectiles_.end()
			);
		}
	}

	void Pistol::draw(sf::RenderWindow& window)
	{
		if (is_active_) {

			if (projectiles_.size() != 0) {
				for (auto& p : projectiles_) {
					p.draw(window);
				}
			}

			obb_shape_.draw(window, sf::Color::White);
		}
	}

	void Pistol::update(float dt)
	{
		current_time_ = game::clamp(current_time_ + dt, 0.0f, max_time_);
		if (current_time_ >= max_time_) {
			can_shoot_ = true;
		}
		else {
			can_shoot_ = false;
		}

		switch (pistol_state_) {

		case PistolState::IS_SHOOTING:

			if (can_shoot_ && bullet_count_ > 0) {
				// add new 

				Projectile new_p(position_, projectile_speed_, angle_);
				new_p.set_textue(projectile_texture_);

				projectiles_.push_back(new_p);

				// reset
				bullet_count_--;
				current_time_ = 0.0f;
				can_shoot_ = false;
				pistol_state_ = PistolState::NONE;

				std::cout << "BANG!: " << bullet_count_ << " bullets left in gun" << std::endl;

			}

			if (bullet_count_ <= 0) {

				pistol_state_ = PistolState::NONE;
				is_reloading_ = true;

				std::cout << "need to reload" << std::endl;

			}
			break;

		case PistolState::IS_RELOADING:
			if (is_reloading_) {
				bullet_count_ = max_bullet_count_;
				can_shoot_ = true;
				is_reloading_ = false;
				pistol_state_ = PistolState::NONE;

				std::cout << "reloaded" << std::endl;
			}
			else {
				std::cout << "no need to reload yet" << std::endl;
				pistol_state_ = PistolState::NONE;
			}
			break;

		case PistolState::NONE:
			// default state
			break;

		default:
			break;
		}

		obb_shape_.position = position_;
		obb_shape_.angle = rad_2_deg(angle_);


		if (projectiles_.size() != 0) {
			for (auto& p : projectiles_) {
				p.update(dt);
			}
		}

		filter_inactive_bullets();
	}
}