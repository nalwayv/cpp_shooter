#include "Projectile.h"
#include "MathHelp.h"
#include "V2.h"

using game::Projectile;

using sf::Vector2f;
using sf::RenderWindow;
using sf::Texture;
using sf::Color;

namespace game {

	Projectile::Projectile(Vector2f position, float acceleration, float angle)
		:position_(position),
		velocity_(0.0f, 0.0f),
		speed_(acceleration),
		max_speed_(400.0f),
		current_life_(0.0f),
		max_life_(8.0f),
		angle_(angle),
		is_active_(true),
		is_debug_(true),
		has_timer_(true),
		has_texture_(false),
		obb_shape_(position, Vector2f(10.0f, 4.0f), angle),
		sprite_()
	{

		sprite_.setPosition(position_);
		sprite_.setOrigin(Vector2f(10.0f, 4.0f) * 0.5f);
		sprite_.setRotation(rad_2_deg(angle_));
	}

	const OBB& Projectile::get_collision_shape() const
	{
		return obb_shape_;
	}

	bool Projectile::get_is_active() const
	{
		return is_active_;
	}

	void Projectile::set_is_active(bool value)
	{
		is_active_ = value;
	}

	void Projectile::set_textue(const Texture& texture)
	{
		sprite_.setTexture(texture);
		has_texture_ = true;
	}

	void Projectile::set_position(Vector2f new_pos)
	{
		position_ = new_pos;
	}

	void Projectile::set_angle(float new_angle)
	{
		angle_ = new_angle;
	}

	void Projectile::set_speed(float new_speed)
	{
		speed_ = new_speed;
	}


	void Projectile::update(float dt)
	{
		if (is_active_) {
			if (has_timer_) {
				current_life_ += dt;
				if (current_life_ > max_life_) {
					is_active_ = false;
				}
			}

			obb_shape_.position = position_;
			obb_shape_.angle = rad_2_deg(angle_);

			sprite_.setPosition(position_);
			sprite_.setRotation(rad_2_deg(angle_));

			velocity_.x = clamp(velocity_.x + speed_, 0.0, max_speed_);
			velocity_.y = clamp(velocity_.y + speed_, 0.0, max_speed_);

			position_ += v2_set_ang(velocity_, angle_) * dt;
		}
	}

	void Projectile::draw(RenderWindow& window)
	{
		if (is_active_) {
			if (is_debug_) {
				obb_shape_.draw(window, Color::White);
			}

			if (has_texture_) {
				window.draw(sprite_);
			}
		}
	}
}