#include "Object.hpp"


class Enemy : public Object {

public:
    Enemy(b2Body *b2Body, sf::Texture texture);
    ~Enemy() = default;


private:

};