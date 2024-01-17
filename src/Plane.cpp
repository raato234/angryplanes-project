
#include "Plane.hpp"

Plane::Plane(b2Body *b2Body, sf::Texture texture, int   type, bool usedAction) : Object(b2Body, texture), usedAction_(usedAction), type_(type) {
    launched_ = false;
}

void Plane::launch(float x, float y) {
    float mass = body_->GetMass();
    body_->ApplyLinearImpulseToCenter(b2Vec2(x*5, y*5), true);
    launched_ = true;
}

void Plane::useAbility()
{
    int tyyppi = type_;   
    if (tyyppi == 1) {         //ability 1: speedboost
        body_->SetLinearVelocity(b2Vec2(body_->GetLinearVelocity().x * 2.5, body_->GetLinearVelocity().y * 2.5));
        usedAction_ = true;
    }

    if (tyyppi == 2) {         //ability 2: fly backwards
        body_->SetLinearVelocity(b2Vec2(body_->GetLinearVelocity().x * -3, body_->GetLinearVelocity().y * 0.5));
        usedAction_ = true;
    }
     
}