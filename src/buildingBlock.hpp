
#ifndef ANGRY_PLANES_BUILDINGBLOCK_HPP
#define ANGRY_PLANES_BUILDINGBLOCK_HPP
#include "Object.hpp"

class buildingBlock : Object{
public:
    buildingBlock(b2Body *b2Body, sf::Texture texture);
    ~buildingBlock() = default;

};


#endif //ANGRY_PLANES_BUILDINGBLOCK_HPP
