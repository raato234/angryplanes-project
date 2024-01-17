
#ifndef ANGRY_PLANES_PLANE_HPP
#define ANGRY_PLANES_PLANE_HPP
#include "Object.hpp"

class Plane : public Object{
public:
    Plane(b2Body *b2Body, sf::Texture, int type = 0, bool usedAction = false);
    ~Plane() = default;
    void launch(float x, float y);
    void useAbility();
    bool usedAction_;
    int getType() { return type_; }
    bool launched_;
private:
    int type_;
};


#endif //ANGRY_PLANES_PLANE_HPP
