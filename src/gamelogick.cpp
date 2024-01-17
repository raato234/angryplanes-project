#include "gamelogick.hpp"
//create a physics world b2vec2 is the gravity
GameLogick::GameLogick(): world(b2World(b2Vec2(0, 10.f))) {}

b2Body *GameLogick::addGround() {
    //creating a ground body according to the example on the box2d tutorials https://box2d.org/documentation/md__d_1__git_hub_box2d_docs_hello.html
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(-20.f, 40);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(160.0f, 9.5f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    return groundBody;
}

b2Body *GameLogick::addCircle(float x, float y, float radius) {
    //creating a dynamic circle according to the example on https://box2d.org/documentation/md__d_1__git_hub_box2d_docs_hello.html

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);
    b2Body* body = world.CreateBody(&bodyDef);

    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = radius;


    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.4f;
    body->CreateFixture(&fixtureDef);
    return body;
}

b2Body *GameLogick::addSquare(float x, float y, float side) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);
    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape square;
    square.SetAsBox(side / 2, side/ 2);


    b2FixtureDef fixtureDef;
    fixtureDef.shape = &square;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
    return body;
}

void GameLogick::physicsStep() {
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    world.Step(timeStep, velocityIterations, positionIterations);
}

void GameLogick::clearWorld() {
    b2Body* body = world.GetBodyList();
    while (body) {
        world.DestroyBody(body);
        body = world.GetBodyList();
    }

}

