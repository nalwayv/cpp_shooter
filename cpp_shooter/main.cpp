// cpp_game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include <array>
#include <cmath>
#include <algorithm>
#include <vector>
#include <memory>
#include "Player.h"
#include "Obb.h"
#include "V2.h"
#include "TextureManager.h"
#include "Pistol.h"
#include "MathHelp.h"

using sf::RenderWindow;
using sf::VideoMode;
using sf::Event;
using sf::Color;
using sf::Clock;
using sf::Keyboard;
using sf::RectangleShape;
using sf::Vector2f;
using std::map;
using std::cout;
using std::endl;
using std::array;
using std::cosf;
using std::sinf;
using std::min;
using std::max;
using std::vector;
using game::Player;
using game::TextureManager;
using game::Pistol;
using game::OBB;


bool sat_collision(const vector<Vector2f>& p1, const vector<Vector2f>& p2) {

    constexpr float inf = std::numeric_limits<float>::infinity();

    auto r1 = &p1;
    auto r2 = &p2;

    for (size_t tally = 0; tally < 2; tally++)
    {
        // swap
        if (tally == 1) {
            r1 = &p2;
            r2 = &p1;
        }

        for (size_t x = 0; x < r1->size(); x++) {
            // loop back around
            size_t y = (x + 1) % r1->size();

            auto normal = game::v2_normal(r1->at(x), r1->at(y));

            // get min/max for shape 1
            auto min_v1 = inf;
            auto max_v1 = -inf;
            for (size_t idx = 0; idx < r1->size(); idx++) {
                auto dot = game::v2_dot(r1->at(idx), normal);

                min_v1 = min(min_v1, dot);
                max_v1 = max(max_v1, dot);
            }

            // get min/max for shape 2
            auto min_v2 = inf;
            auto max_v2 = -inf;
            for (size_t idx = 0; idx < r2->size(); idx++) {
                auto dot = game::v2_dot(r2->at(idx), normal);

                min_v2 = min(min_v2, dot);
                max_v2 = max(max_v2, dot);
            }

            // check overlap
            if (!(max_v2 >= min_v1 && max_v1 >= min_v2)) {
                return false;
            }
        }
    }

    return true;
}

void key_populate(map<sf::Keyboard::Key, bool>& data) {
    data.insert({ sf::Keyboard::W, false });
    data.insert({ sf::Keyboard::A, false });
    data.insert({ sf::Keyboard::S, false });
    data.insert({ sf::Keyboard::D, false });
    data.insert({ sf::Keyboard::Space, false });
}


int main()
{
    std::cout << "game" << endl;

    RenderWindow window(VideoMode(500, 500), "game");
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(true);
    Clock clock;

    bool is_paused = false;

    map<Keyboard::Key, bool> key_map;
    key_populate(key_map);
    Vector2f mouse_pos(0.0f, 0.0f);

    TextureManager tm;
    tm.load("player", "../assets/img/player.png");
    tm.load("bullet", "../assets/img/bullet.png");
    
    Player player(Vector2f(100.0f, 100.0f));
    player.set_textue(tm.get("player"));

    OBB r1;
    auto r1_col = Color::White;
    r1.position = Vector2f(250.0f, 250.0f);
    r1.half_extents = Vector2f(25.0f, 25.0f);
    r1.angle = 0.0f;

    // TODO: tmp
    Pistol pistol(player.get_position(), player.get_angle());
    pistol.set_texture(tm.get("bullet"));

    while (window.isOpen()) {
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == Event::MouseMoved) {
                // get current mouse position.
                auto m = sf::Mouse::getPosition(window);
                mouse_pos.x = static_cast<float>(m.x);
                mouse_pos.y = static_cast<float>(m.y);
            }

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    window.close();
                }

                if (event.key.code == Keyboard::P) {
                    is_paused = !is_paused;
                }

                if (event.key.code == Keyboard::Z) {
                    pistol.shoot();
                }
                if (event.key.code == Keyboard::X) {
                    pistol.reload();
                }
 

                // key map
                if (event.key.code == Keyboard::W) {
                    if (key_map.find(Keyboard::W) != key_map.end()) {
                        key_map[Keyboard::W] = true;
                    }
                }

                if (event.key.code == Keyboard::A) {
                    if (key_map.find(Keyboard::A) != key_map.end()) {
                        key_map[Keyboard::A] = true;
                    }
                }

                if (event.key.code == Keyboard::S) {
                    if (key_map.find(Keyboard::S) != key_map.end()) {
                        key_map[Keyboard::S] = true;
                    }
                }

                if (event.key.code == Keyboard::D) {
                    if (key_map.find(Keyboard::D) != key_map.end()) {
                        key_map[Keyboard::D] = true;
                    }
                }

                if (event.key.code == Keyboard::Space) {
                    if (key_map.find(Keyboard::Space) != key_map.end()) {
                        key_map[Keyboard::Space] = true;
                    }
                }
            }
        
            if (event.type == Event::KeyReleased){
            
                if (event.key.code == Keyboard::W) {
                    if (key_map.find(Keyboard::W) != key_map.end()) {
                        key_map[Keyboard::W] = false;
                    }
                }

                if (event.key.code == Keyboard::A) {
                    if (key_map.find(Keyboard::A) != key_map.end()) {
                        key_map[Keyboard::A] = false;
                    }
                }

                if (event.key.code == Keyboard::S) {
                    if (key_map.find(Keyboard::S) != key_map.end()) {
                        key_map[Keyboard::S] = false;
                    }
                }

                if (event.key.code == Keyboard::D) {
                    if (key_map.find(Keyboard::D) != key_map.end()) {
                        key_map[Keyboard::D] = false;
                    }
                }

                if (event.key.code == Keyboard::Space) {
                    if (key_map.find(Keyboard::Space) != key_map.end()) {
                        key_map[Keyboard::Space] = false;
                    }
                }
            }
        }

  
        if (!is_paused) {
            float dt = clock.restart().asSeconds();
 
            // Inputs ---
            player.input(key_map);
            player.set_mouse_pos(mouse_pos);


            // Update ---
            player.update(dt);
            player.check_target(r1);

            auto pistol_offset = game::v2_set_ang(Vector2f(1.0, 0.0), game::deg_2_rad(20.0f) + player.get_angle()) * 50.0f;
            pistol.set_position(player.get_position() + pistol_offset);
            pistol.set_angle(player.get_angle());
            pistol.update(dt);
            
            auto test_collision = sat_collision(player.get_obb_shape().get_shape(), r1.get_shape());
            if (test_collision) {
                r1_col = Color::Red;
            }

            for (const auto& p : pistol.get_projectiles()) {
                if (p.get_is_active()) {
                    auto test_collision = sat_collision(p.get_collision_shape().get_shape(), r1.get_shape());
                    if (test_collision) {
                        r1_col = Color::Red;
                    }
                }
            }

            // Render ---
            window.clear(Color(21, 21, 21));
            // ->
            player.draw(window);
            r1.draw(window, r1_col);
            pistol.draw(window);
            // <-
            window.display();

            // reset
            r1_col = Color::White;
        }
        else {
            clock.restart();
        }
    }

    return 0;
}

