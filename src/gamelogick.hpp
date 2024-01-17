//"engine of the game" used to run most of the background logic and physics in the game
#pragma once
#include <box2d/box2d.h>



class GameLogick {

public:
    GameLogick();

    ~GameLogick() = default;
    // Add the ground to the game world and return reference to it
    b2Body* addGround();

    b2Body* addCircle(float x, float y, float radius);

    b2Body* addSquare(float x, float y, float side);

    void physicsStep();

    void clearWorld();

private:
    // world where all the physics objects are stored
    b2World world;

};