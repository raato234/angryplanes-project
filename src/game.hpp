#pragma once
#ifndef ANGRYPLANES_GAME
#define ANGRYPLANES_GAME


//includes
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>
#include "level.hpp"
#include "GUI.hpp"
#include "Object.hpp"
#include "playingGui.hpp"




class Game {

    public:
        Game();

        double GetScore() const;

        void gamestate(); //keeps the game running if the app is not closed or quit button pressed
        void gameUpdateLevel();

    private:

        double score_;
        sf::RenderWindow appwindow_;

};
#endif
