#pragma once
#ifndef ANGRY_PLANES_PLAYINGGUI_HPP
#define ANGRY_PLANES_PLAYINGGUI_HPP
#include "SFML/Graphics.hpp"
#include <string>
#include <vector>
#include "gamelogick.hpp"
#include "Plane.hpp"
#include "box.hpp"
#include "level.hpp"
#include "enemy.hpp"

using namespace std;

class playingGui {
public:


    playingGui(sf::RenderWindow& window, GameLogick *physicsWorld, Level* level);
    void pollEvent();
    void update();
    void render();
    void drawScene();
    void initLevel();
    void calc_speed(sf::Event e);
    bool won = false;


private:
    sf::RenderWindow& window_;
    void trackMouse(sf::Event e);
    std::vector<float> mouse_distance(sf::Event e, float offset_x, float offset_y, float object_x, float object_y);
    bool mouse_pressed(sf::Event e, std::vector<float> track, float size_x, float size_y);
    void draw_aimline();
    void drawRange();
    void display_shots();
    void drawPlayerToBeLaunched();
    void draw_victory(sf::Event e);

    //random values
    float cursor_arrea = 50; //arrea where mouse interacts with the plane
    float spawn_x = 200;
    float spawn_y = 200;
    float obj_size = 2;
    float max_speed = 250;
    float x_speed = 0;
    float y_speed = 0;
    bool can_realease = false;
    std::vector<float> launch_dir{ 0.f,0.f };
    sf::Text shotcounter;
    int shots_left;
    int track_score = 0;
    sf::Text end_score;
    bool score_counted = false;
    int enemies_left_=1;
    bool start_wincon = false;


    //Textures
    sf::Texture planeTexture0_;
    sf::Texture planeTexture1_;
    sf::Texture planeTexture2_;
    sf::Texture buildTexture_;
    sf::Texture enemyTexture_;
    sf::Texture groundTexture_;
    sf::Texture mainmenu_Texture_;
    sf::Texture victory_Texture_;

    //font
    sf::Font font;

    //sprite
    sf::Sprite mainmenu_btn_;
    sf::Sprite ground_;
    sf::Sprite currentPlayable_;
    sf::Sprite victory_screen_;

    //Physics world
    GameLogick *physicsWorld_;

    //player
    vector<pair<sf::Texture, int>> planesLeft;
    Plane *player_;
    bool game_on;
    vector<Plane*> planes_;

    //boxes
    vector<Box*> boxes_;

    //enemies
    vector<Enemy*> enemies_;

    //filemanager
    Level* level_;
};


#endif //ANGRY_PLANES_PLAYINGGUI_HPP

