#include "Object.hpp"
#include <iostream>



Object::Object(b2Body *B2body, sf::Texture texture) : body_(B2body), texture_(texture) {
    sprite_.setTexture(texture_);
    sprite_.setScale(0.25f, 0.25f);
    sprite_.setOrigin(sprite_.getLocalBounds().width/2, sprite_.getLocalBounds().height/2);
    hp_ = 5;
}

float Object::getPhysicsXpos() {
    return body_->GetPosition().x;
}

float Object::getPhysicsYpos() {
    return body_->GetPosition().y;
}

void Object::updateSpritePos() {
    this->sprite_.setPosition(getPhysicsXpos()*20, getPhysicsYpos()*20);
}

void Object::render(sf::RenderWindow &Renderwindow, float physicsOffset) {
    this->updateSpritePos();
    //std::cout<<getPhysicsYpos()<<std::endl;
    this->sprite_.setRotation(this->body_->GetAngle()*(180.0f/3.14f));
    Renderwindow.draw(this->sprite_);
}



