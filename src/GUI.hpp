#pragma once
#ifndef ANGRYPLANES_GUI
#define ANGRYPLANES_GUI

//includes
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <string>
#include <vector>
#include "level.hpp"
#include "playingGui.hpp"


//constanst of the GUI
const int viewwidth = 1200;
const int viewheight = 700;
const int fps = 60;


class MainMenu
{
public:
	MainMenu(sf::RenderWindow& window,Level* level,playingGui* pg);

	void drawMenu();
	void trackMouse_mm(sf::Event e);
	void trackMouse_ls(sf::Event e);
	void drawMute_btn();
	std::vector<float> mouse_distance(sf::Event e,float offset_x,float offset_y,float object_x, float object_y);
	bool mouse_pressed(sf::Event e, std::vector<float> track, float size_x, float size_y);
	void drawMap_selector();
	void back_to_main_menu();

private:

	//miscellaneous
	sf::RenderWindow& window_;
	bool menu_open = true;
	bool menumusic_on = false;
	sf::Music menu_music_;
	bool deactivate_touch_ = true;
	bool selector_open = false;

	//textures
	sf::Texture bg_texture_;
	sf::Texture quit_texture_;
	sf::Texture start_texture_;
	sf::Texture mute_texture_;
	sf::Texture muted_texture_;
	sf::Texture level1_texture_;
	sf::Texture level2_texture_;
	sf::Texture level3_texture_;
	sf::Texture back_texture_;

	//sprites
	sf::Sprite background_;
	sf::Sprite quit_btn_;
	sf::Sprite start_btn_;
	sf::Sprite mute_btn_;
	sf::Sprite muted_btn_;
	sf::Sprite level1_btn_;
	sf::Sprite level2_btn_;
	sf::Sprite level3_btn_;
	sf::Sprite back_btn_;

	//button variables
	float button_size_x = 200;
	float button_size_y = 50;
	float mute_side_ = 50;
	float offset_x = 500;
	float offset_y_start = 350;
	float offset_y_quit = 500;
	float mute_x = 1150;
	float mute_y = 650;
	float maps_offset = 50;

	//level
	Level* level_;
	//playingGui
	playingGui* playingGui_;
};

#endif