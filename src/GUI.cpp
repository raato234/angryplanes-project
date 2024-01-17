#include "GUI.hpp"
#include <math.h>

//creates the mainmenu object
MainMenu::MainMenu(sf::RenderWindow& window, Level* level, playingGui* pg)
:window_(window),level_(level),playingGui_(pg){

	//load textures
	bg_texture_.loadFromFile("resources/images/angry_planes.png");
	quit_texture_.loadFromFile("resources/images/quit_btn.png");
	start_texture_.loadFromFile("resources/images/start_btn.png");
	mute_texture_.loadFromFile("resources/images/mute.png");
	muted_texture_.loadFromFile("resources/images/muted.png");
	level1_texture_.loadFromFile("resources/images/level_1.png");
	level2_texture_.loadFromFile("resources/images/level_2.png");
	level3_texture_.loadFromFile("resources/images/level_3.png");
	back_texture_.loadFromFile("resources/images/back_btn.png");

	//set sprites
	background_.setTexture(bg_texture_);
	quit_btn_.setTexture(quit_texture_);
	start_btn_.setTexture(start_texture_);
	mute_btn_.setTexture(mute_texture_);
	muted_btn_.setTexture(muted_texture_);
	level1_btn_.setTexture(level1_texture_);
	level2_btn_.setTexture(level2_texture_);
	level3_btn_.setTexture(level3_texture_);
	back_btn_.setTexture(back_texture_);

//loads and plays audio in a loop
menu_music_.openFromFile("resources/audio/menu_music.wav");
menu_music_.setLoop(true);


//set position
quit_btn_.setPosition(offset_x, offset_y_quit);
start_btn_.setPosition(offset_x, offset_y_start);
mute_btn_.setPosition(mute_x, mute_y);
muted_btn_.setPosition(mute_x, mute_y);
level1_btn_.setPosition(offset_x, offset_y_start - maps_offset);
level2_btn_.setPosition(offset_x, offset_y_start + maps_offset);
level3_btn_.setPosition(offset_x, offset_y_quit);
}


void MainMenu::drawMenu() {

	if (menumusic_on) {
		menu_music_.play();
	}

	sf::Event e;

	//keeps the menu running
	while (menu_open)
	{

		while (window_.pollEvent(e))
		{
			trackMouse_mm(e);
		}
		window_.clear();

		//draws menu items order matters 
		window_.draw(background_);
		window_.draw(quit_btn_);
		window_.draw(start_btn_);
		drawMute_btn();

		window_.display();

		if (selector_open) {
			drawMap_selector();

			deactivate_touch_ = true;

			if (deactivate_touch_) {
				sf::Clock timer;
				while (timer.getElapsedTime().asSeconds() < 0.2f)
				{
					deactivate_touch_ = false;
				}
			}
		}
	}

	window_.clear();
}

//mouse events for mainmenu
void MainMenu::trackMouse_mm(sf::Event e) {

	//check location of ur mouse
	std::vector<float> track_start = mouse_distance(e, button_size_x/2, button_size_y/2, offset_x, offset_y_start);
	std::vector<float> track_quit = mouse_distance(e, button_size_x/2, button_size_y/2, offset_x, offset_y_quit);
	std::vector<float> track_mute = mouse_distance(e, mute_side_/2, mute_side_/2, mute_x, mute_y);

	//close game
	if (e.type == sf::Event::Closed || mouse_pressed(e, track_quit, button_size_x, button_size_y)) {
		window_.close();
		menu_music_.stop();
	}

	//start game
	if (mouse_pressed(e, track_start, button_size_x, button_size_y)) {
		selector_open = true;
	}

	//track if audio is on or off
	if (mouse_pressed(e,track_mute,mute_side_,mute_side_)) {
		if (menumusic_on) {
			menu_music_.stop();
			menumusic_on = false;
		}
		else
		{
			menumusic_on = true;
			menu_music_.play();
		}
	}
}

//draws mute button
void MainMenu::drawMute_btn() {
	if (menumusic_on) {
		window_.draw(mute_btn_);
	}
	else
	{
		window_.draw(muted_btn_);
	}
}

//checks if cursor is inside hitbox
std::vector<float> MainMenu::mouse_distance(sf::Event e, float from_center_x, float from_center_y, float object_x, float object_y) {
	std::vector<float> x_and_y;
	x_and_y.push_back(fabsf((object_x + from_center_x - (float)e.mouseButton.x)));
	x_and_y.push_back(fabsf((object_y + from_center_y - (float)e.mouseButton.y)));

	return x_and_y;
}

//checks if mouse is pressed inside hitbox
bool MainMenu::mouse_pressed(sf::Event e, std::vector<float> track, float size_x, float size_y) {
	if (e.type == sf::Event::MouseButtonPressed && track[0] <= size_x/2 && track[1] <= size_y/2){
		return true;
	}
	return false;
}

//draws map selector
void MainMenu::drawMap_selector() {

	//prevents inheriting touch from previous scene
	if (deactivate_touch_) {
		sf::Clock timer;
		while (timer.getElapsedTime().asSeconds() < 0.2f)
		{
			deactivate_touch_ = false;
		}
	}

	

	//main loop for the map selector
	while (selector_open)
	{
		sf::Event e;

		while (window_.pollEvent(e))
		{
			trackMouse_ls(e);
		}
		window_.clear();
		window_.draw(background_);
		window_.draw(level1_btn_);
		window_.draw(level2_btn_);
		window_.draw(level3_btn_);
		drawMute_btn();
		window_.draw(back_btn_);
		window_.display();

	}
	//todo make able to select maps and make able to go back to main menu

}

void MainMenu::trackMouse_ls(sf::Event e) {

	//check location of ur mouse from clickable
	std::vector<float> track_map1 = mouse_distance(e, button_size_x / 2, button_size_y / 2, offset_x, (offset_y_start - maps_offset));
	std::vector<float> track_map2 = mouse_distance(e, button_size_x / 2, button_size_y / 2, offset_x, offset_y_start + maps_offset);
	std::vector<float> track_map3 = mouse_distance(e, button_size_x / 2, button_size_y / 2, offset_x, offset_y_quit);
	std::vector<float> track_mute = mouse_distance(e, mute_side_ / 2, mute_side_ / 2, mute_x, mute_y);
	std::vector<float> track_back = mouse_distance(e, mute_side_ / 2, mute_side_ / 2, 0, 0);

	//close game
	if (e.type == sf::Event::Closed) {
		window_.close();
		menu_music_.stop();
	}

	//todo make all buttons take to different level when levels are ready
	
	//when level1 is selected
	if (mouse_pressed(e, track_map1, button_size_x, button_size_y)) {
		level_->Load(1);
		playingGui_->initLevel();
		menu_open = false;
		selector_open=false;
		menu_music_.stop();
	}

	//when level2 is selected
	if (mouse_pressed(e, track_map2, button_size_x, button_size_y)) {
		level_->Load(2);
		playingGui_->initLevel();
		menu_open = false;
		selector_open = false;
		menu_music_.stop();
	}

	//when level3 is selected
	if (mouse_pressed(e, track_map3, button_size_x, button_size_y)) {
		level_->Load(3);
		playingGui_->initLevel();
		menu_open = false;
		selector_open = false;
		menu_music_.stop();
	}

	//if pressed back
	if (mouse_pressed(e, track_back, mute_side_, mute_side_)) {
		selector_open=false;
	}

	//track if audio is on or off
	if (mouse_pressed(e, track_mute, mute_side_, mute_side_)) {
		if (menumusic_on) {
			menu_music_.stop();
			menumusic_on = false;
		}
		else
		{
			menumusic_on = true;
			menu_music_.play();
		}
	}
}

void MainMenu::back_to_main_menu() {
	menu_open = true;
}