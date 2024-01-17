#pragma once
#include "game.hpp"



Game::Game() 
    : appwindow_(sf::VideoMode(viewwidth,viewheight), "Angry Planes") {
    appwindow_.setFramerateLimit(fps);
}

void Game::gamestate() {
    GameLogick gameLogick;
    Level level;
    playingGui playingGui(appwindow_, &gameLogick, &level);
    MainMenu menu(appwindow_, &level, &playingGui);
    
    



    while (appwindow_.isOpen())
    {
        //draws main menu
        menu.drawMenu();

        //draws the level
        playingGui.drawScene();

        menu.back_to_main_menu();
    }
}



double Game::GetScore() const {
    return score_;
}

void Game::gameUpdateLevel() {

}
