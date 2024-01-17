#pragma once
#include "SFML/Graphics.hpp"
#include "GUI.hpp"
#include <math.h>



class Projectile {

public: 

    struct vec2 {
        float x, y;
    };

    struct plane {
        vec2 pos, vel;
        bool flying;
        bool ability_used;
    };

    plane update(plane b, float dt) {
        b.pos = {
            b.pos.x + b.vel.x * dt,
            b.pos.y + b.vel.y * dt - (1.f / 2.f) * 100.f * dt * dt
        };
        b.vel.y -= 100.f * dt;
        return b;
    }

    //launch cordinates
    float launch_pos_y = -300.f;
    float launch_pos_x = 100.f;

    //the distance from the projectile that counts mose down
    float touch_sensitivity = 30;

    float projectile_rad = 10.f;

    //prevents user from aplying speed after projectile is shot
    bool can_realease = true;

    plane b{
            {launch_pos_x,launch_pos_y},
            {0.f, 0.f},
            false,
            false                          //not flying and ability not used when starting
    };
    

    float speed = 5.f;


    

    void updateplane(sf::RenderWindow& window, float dt) {

        if (!activate_touch_) {
            sf::Clock timer;
            while (timer.getElapsedTime().asSeconds()<0.2f)
            {
                activate_touch_ = true;
            }
        }

        sf::CircleShape shape(projectile_rad);
        shape.setFillColor(sf::Color::Green);

        sf::CircleShape range(touch_sensitivity);
        range.setFillColor(sf::Color(255,255,255,0));

        sf::Event e;

        while (window.pollEvent(e))
        {
            trackmouse(e, window);
        }
        
        window.clear();

        if (b.flying)
            b = update(b, dt);

        //draws the arrea where from you can shoot the ball
        range.setOutlineThickness(-3);
        range.setOutlineColor({ 255,255,255 });
        range.setPosition({launch_pos_x-(touch_sensitivity/2)-(projectile_rad/2), 200.f - launch_pos_y-(touch_sensitivity / 2) - (projectile_rad / 2) });
        window.draw(range);

        //draws the ball
        shape.setFillColor({ 0, 255, 0 });
        shape.setPosition({ b.pos.x, 200.f - b.pos.y });
        window.draw(shape);
        

        if (!b.flying) {
            if (b.vel.x * b.vel.x + b.vel.y * b.vel.y > 10.f) {
                for (int i = 1; i < 10; i++) {
                    plane a = update(b, i * .5f);
                    shape.setFillColor({ 255, 0, 0 });
                    shape.setPosition({ a.pos.x, 200.f - a.pos.y });
                    window.draw(shape);
                }
            }
        }

        window.display();
    }



    void trackmouse(sf::Event e, sf::RenderWindow& window) {

        //distance from the projectile
        float touch_range_x = fabsf((launch_pos_x - (float)e.mouseButton.x));
        float touch_range_y = fabsf(launch_pos_y - (200.f - (float)e.mouseButton.y));

        

        if (e.type == sf::Event::Closed)
            window.close();

        if (e.type == sf::Event::MouseButtonPressed&&touch_sensitivity>=touch_range_x&&touch_sensitivity>=touch_range_y) {
            b.flying = false;
            b.pos = vec2{ launch_pos_x,launch_pos_y };
            can_realease = true;
            b.ability_used = false;                                    //reset ability when resetting projectile
        }

        if (e.type == sf::Event::MouseMoved && !b.flying) {
            b.vel = vec2{
                speed * (b.pos.x - (float)e.mouseMove.x),
                speed * (b.pos.y - (200.f - (float)e.mouseMove.y))
            };
        }
        if (e.type == sf::Event::MouseButtonReleased&&can_realease) {
            b.vel = vec2{
                speed * (b.pos.x - (float)e.mouseButton.x),
                speed * (b.pos.y - (200.f - (float)e.mouseButton.y))
            };
            b.flying = true;
            can_realease = false;
        }
        if (e.type == sf::Event::MouseButtonPressed && b.flying && !b.ability_used) {   //simple ability to 2x velocity in both directions
            b.vel.x = b.vel.x * 2;
            b.vel.y = b.vel.y * 2;
            b.ability_used = true;                           //mark ability used resetting projectile
        }
    }

private:

    bool activate_touch_ = false;
};


