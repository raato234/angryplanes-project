//
// Created by Matias Tarmo on 11.12.2022.
//
#include "enemy.hpp"
#include "gamelogick.hpp"

Enemy::Enemy(b2Body *b2Body, sf::Texture texture) : Object(b2Body, texture) {}
