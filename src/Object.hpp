#pragma once
#ifndef ANGRY_PLANES_OBJECT_H
#define ANGRY_PLANES_OBJECT_H

#include <box2d/b2_body.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Object {
public:
    Object(b2Body *B2body, sf::Texture texture);
    virtual ~Object() = default;

    b2Body* GetBody() {return body_;}
    sf::Sprite& GetSprite() {return sprite_;}

    float getPhysicsXpos();
    float getPhysicsYpos();
    void updateSpritePos();

    void render(sf::RenderWindow &window, float physicsOffset);



    bool IsIntact() {return intact;}


protected:
    sf::Sprite sprite_;
    b2Body *body_;
    sf::Texture texture_;
    int hp_;
    bool intact = true;

};


#endif //ANGRY_PLANES_OBJECT_H
