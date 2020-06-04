#include <iostream>
#include <cmath>

#include "Player.h"
#include "V2.h"
#include "MathHelp.h"

// USING
using sf::Vector2f;
using sf::RenderWindow;
using sf::Keyboard;
using sf::Color;
using sf::Texture;
using std::map;
using std::cout;
using std::endl;
using std::acosf;
using std::abs;

namespace game {
	Player::Player(Vector2f pos)
		:position_(pos),
		velocity_(0.0f, 0.0f),
		size_(20.0f, 25.0f),
		speed_(15.0f),
		max_speed_(400.0f),
		mouse_pos_(0.0f, 0.0f),
		target_pos_(0.0f, 0.0f),
		angle_(0.0f),
		friction_(0.1f),
		fov_(55.0f),
		is_active_(true),
		is_moving_up_(false),
		is_moving_down_(false),
		is_moving_left_(false),
		is_moving_right_(false),
		has_target_(false),
		is_debug_mode_(true),
		direction_line_(),
		angle_line_(),
		fov_line_up_(),
		fov_line_down_(),
		target_line_(),
		circle_shape_(position_, 135.0f),
		obb_shape_(position_, size_, angle_),
		sprite_()
	{
		sprite_.setPosition(position_);
		sprite_.setOrigin(size_ * 0.5f);
		sprite_.setRotation(rad_2_deg(angle_));
	}

	const OBB& Player::get_obb_shape() const
	{
		return obb_shape_;
	}

	void Player::screen_clamp(float width, float height)
	{
		if (position_.x >= width - size_.x) {
			position_.x = width - size_.x;
		}

		if (position_.y >= height - size_.y) {
			position_.y = height - size_.y;
		}

		if (position_.x <= size_.x) position_.x = size_.x;
		if (position_.y <= size_.y) position_.y = size_.y;
	}

	void Player::set_mouse_pos(Vector2f new_mouse_pos)
	{
		mouse_pos_ = new_mouse_pos;
	}

	float Player::get_angle() const
	{
		return angle_;
	}

	void Player::set_velocity(Vector2f new_velocity)
	{
		velocity_ = new_velocity;
	}

	Vector2f Player::get_velocity() const
	{
		return velocity_;
	}

	Vector2f Player::get_position() const
	{
		return position_;
	}

	void Player::set_textue(const Texture& texture)
	{
		sprite_.setTexture(texture);
	}

	// TODO: 
	void Player::check_target(const OBB& target)
	{
		auto player_dir = v2_unit(mouse_pos_ - position_);
		auto dir_to_npc = v2_unit(target.position - position_);

		// store for line draw
		target_pos_ = target.position;

		auto result = false;

		// is in range
		if (v2_distance_between(target.position, position_) < circle_shape_.radius) {

			// is within fov range
			auto angle_to_target = rad_2_deg(v2_angle_to(player_dir, dir_to_npc));
			if (abs(angle_to_target) < fov_ / 2.0f) {
				result = true;
			}
		}

		if (result) {
			has_target_ = true;
		}
		else {
			has_target_ = false;
		}
	}

	void Player::input(const map<Keyboard::Key, bool>& key_map)
	{
		if (key_map.find(Keyboard::W) != key_map.end()) {
			is_moving_up_ = key_map.at(Keyboard::W);
		}

		if (key_map.find(Keyboard::A) != key_map.end()) {
			is_moving_left_ = key_map.at(Keyboard::A);
		}

		if (key_map.find(Keyboard::S) != key_map.end()) {
			is_moving_down_ = key_map.at(Keyboard::S);
		}

		if (key_map.find(Keyboard::D) != key_map.end()) {
			is_moving_right_ = key_map.at(Keyboard::D);
		}
	}

	void Player::update(float dt)
	{
		if (is_active_) {
			screen_clamp(500.0f, 500.0f);

			if (is_moving_up_) {
				velocity_.y = clamp(velocity_.y - speed_, -max_speed_, 0.0f);
			}
			else if (is_moving_down_) {
				velocity_.y = clamp(velocity_.y + speed_, 0.0, max_speed_);
			}
			else if (is_moving_left_) {
				velocity_.x = clamp(velocity_.x - speed_, -max_speed_, 0.0f);
			}
			else if (is_moving_right_) {
				velocity_.x = clamp(velocity_.x + speed_, 0.0, max_speed_);
			}
			else {
				// slow down
				velocity_.x = lerp(velocity_.x, 0.0f, friction_);
				velocity_.y = lerp(velocity_.y, 0.0f, friction_);
			}


			// angle
			auto new_angle = v2_angle(mouse_pos_ - position_);
			angle_ = new_angle;

			if (is_debug_mode_) {
				// ray2D

				direction_line_.start = position_;
				direction_line_.end = (position_ +v2_set_len(velocity_, circle_shape_.radius));

				angle_line_.start = (position_);
				angle_line_.end = (position_ + v2_set_len(mouse_pos_ - position_, circle_shape_.radius));

				auto fov_angle = deg_2_rad(fov_ / 2);
				fov_line_up_.start = (position_);
				fov_line_up_.end = (position_ + v2_set_ang(Vector2f(1.0, 0.0), fov_angle + angle_) * circle_shape_.radius);
				fov_line_down_.start = (position_);
				fov_line_down_.end = (position_ + v2_set_ang(Vector2f(1.0, 0.0), -fov_angle + angle_) * circle_shape_.radius);

				target_line_.start = (position_);
				target_line_.end = (position_ + v2_set_len(target_pos_ - position_, circle_shape_.radius));
			}

			// collision shapes
			obb_shape_.position = position_;
			obb_shape_.angle = rad_2_deg(angle_);

			circle_shape_.position = position_;

			// sprite
			sprite_.setPosition(position_);
			sprite_.setRotation(rad_2_deg(angle_));


			position_ += velocity_ * dt;
		}
	}

	void Player::draw(RenderWindow& window)
	{
		if (is_active_) {
			if (is_debug_mode_) {

				direction_line_.draw(window, Color::White);
				angle_line_.draw(window, Color::White);
				fov_line_up_.draw(window, Color::Yellow);
				fov_line_down_.draw(window, Color::Yellow);

				if (has_target_) {
					target_line_.draw(window, Color::Red);
				}

				circle_shape_.draw(window, Color::White);

				obb_shape_.draw(window, Color::White);
			}

			window.draw(sprite_);

		}
	}
}