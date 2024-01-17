
#include "playingGui.hpp"
#include <stdlib.h>
#include <time.h>

playingGui::playingGui(sf::RenderWindow& window, GameLogick* physicsWorld,Level* level) :
    window_(window), physicsWorld_(physicsWorld),level_(level) {
//load textures
    planeTexture0_.loadFromFile("resources/images/plane0.png");
    planeTexture1_.loadFromFile("resources/images/plane1.png");
    planeTexture2_.loadFromFile("resources/images/plane2.png");
    enemyTexture_.loadFromFile("resources/images/enemy.png");
    buildTexture_.loadFromFile("resources/images/woodblock.png");
    mainmenu_Texture_.loadFromFile("resources/images/back_to_mainmenu.png");
    mainmenu_btn_.setTexture(mainmenu_Texture_);
    font.loadFromFile("resources/fonts/arial.ttf");
    victory_Texture_.loadFromFile("resources/images/victory.png");
    victory_screen_.setTexture(victory_Texture_);

    physicsWorld_->addGround();
   
    groundTexture_.loadFromFile("resources/images/ground.png");
    ground_.setTexture(groundTexture_);
    ground_.setScale(0.30, 0.1);
    ground_.setPosition(0, 700 - 150);
    game_on = true;
    player_ = nullptr;
}

void playingGui::update() {

    if (enemies_.size() > 0) {
        start_wincon = true;
    }

    if (start_wincon) {
        enemies_left_ = enemies_.size();
    }

    physicsWorld_->physicsStep();
    //space to activate ability
    if (player_) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !(player_->usedAction_)) {
            this->player_->useAbility();
        }
    }
    for (int i = 0; i < enemies_.size(); i++) {
        if (enemies_[i]->GetBody()->GetLinearVelocity().LengthSquared() >= 20){
            delete enemies_[i];
            enemies_.erase(enemies_.begin()+ i);
        }
    }
}

void playingGui::render() {

    window_.clear();
    sf::Event e;

    while (window_.pollEvent(e))
    {
        trackMouse(e);
    }
    this->drawPlayerToBeLaunched();
    
    for (auto box : boxes_) {
        box->render(window_, 2);
    }
    for (auto enemy : enemies_) {
        enemy->render(window_, 2);
    }

    for (auto plane : planes_) {
        plane->render(window_, 2);
    }

    if (enemies_left_ < 1) {
        won = true;
    }
    display_shots();
    window_.draw(mainmenu_btn_);
    window_.draw(ground_);
    //drawRange();
    if (won) {
        window_.clear();
        draw_victory(e);
    }
    window_.display();
    
}

void playingGui::trackMouse(sf::Event e) {

    //check location of ur mouse from clickable
    std::vector<float> track_mainmenu = mouse_distance(e,25.f,25.f,0,0);
    std::vector<float> track_shooting = mouse_distance(e,cursor_arrea,cursor_arrea,spawn_x,spawn_y );

    //launch cordinates
    float launch_pos_y = -300.f;
    float launch_pos_x = 100.f;
    float touch_sensitivity = 30;

    //the distance from the projectile that counts mose down
    float projectile_rad = 10.f;

    //close game
    if (e.type == sf::Event::Closed) {
        window_.close();
    }

    //if pressed back
    if (mouse_pressed(e, track_mainmenu, 50.f, 50.f)) {
        game_on = false;
        planesLeft.clear();
        planes_.clear();
        boxes_.clear();
        enemies_.clear();
    }

    //for shooting the planes
    if (mouse_pressed(e, track_shooting, 2*cursor_arrea, 2*cursor_arrea)&&shots_left>0) {
        can_realease = true;
    }
    //calculates shot speed
    if (e.type == sf::Event::MouseMoved) {
        calc_speed(e);
        //std::cout << launch_dir[0] << std::endl;
        //std::cout << launch_dir[1] << std::endl;
        }
    // shoots the plane when mouse is released
    if (e.type == sf::Event::MouseButtonReleased&&can_realease)
    {
        if (!planesLeft.empty()) {
            b2Body *playerBody = physicsWorld_->addCircle(spawn_x/20, spawn_y/20, obj_size);
            player_ = new Plane(playerBody, planesLeft[0].first, planesLeft[0].second);
            planes_.push_back(player_);
            planesLeft.erase(planesLeft.begin());
            player_->launch(launch_dir[0]/4, launch_dir[1]/4);

            shots_left = planesLeft.size();
        }
        can_realease = false;
    }

}

void playingGui::drawScene() {
    game_on = true;
    while(game_on) {
        this->update();
        this->render();
    }
    window_.clear();
}

//checks if cursor is inside hitbox
std::vector<float> playingGui::mouse_distance(sf::Event e, float from_center_x, float from_center_y, float object_x, float object_y) {
    std::vector<float> x_and_y;
    x_and_y.push_back(fabsf((object_x + from_center_x - (float)e.mouseButton.x)));
    x_and_y.push_back(fabsf((object_y + from_center_y - (float)e.mouseButton.y)));

    return x_and_y;
}

//checks if mouse is pressed inside hitbox
bool playingGui::mouse_pressed(sf::Event e, std::vector<float> track, float size_x, float size_y) {
    if (e.type == sf::Event::MouseButtonPressed && track[0] <= size_x / 2 && track[1] <= size_y / 2) {
        return true;
    }
    return false;
}


//used for testing aiming
void playingGui::draw_aimline() {
    float gravity_effect = 25;
    float projectile_rad = 5.f;
    float start_x = spawn_x - (cursor_arrea / 2) - (obj_size / 2);
    float start_y = 200.f - spawn_y - (cursor_arrea / 2);
    float pos_x = start_x;
    float pos_y = start_y;
    sf::CircleShape shape(projectile_rad);
    shape.setFillColor({ 255, 255, 255 });

    for (int i = 1; i < 10; i++) {
        shape.setFillColor({ 255, 0, 0 });
        pos_x = pos_x + x_speed * i;
        pos_x = pos_y + y_speed * i;
        shape.setPosition({pos_x,200-pos_y });
        window_.draw(shape);
    }

    //todo calculate unit vector of direction of the vector from mouse to cursor arrea
    
}

void playingGui::calc_speed(sf::Event e) {
    
    std::vector<float> unit_vector;

    //sets speeds from cursor position
    x_speed = fabsf(spawn_x+cursor_arrea - (float)e.mouseMove.x);
    y_speed = fabsf(spawn_y+cursor_arrea - (float)e.mouseMove.y);
    launch_dir[0]=(spawn_x+cursor_arrea- (float)e.mouseMove.x);
    launch_dir[1]=(spawn_y+cursor_arrea- (float)e.mouseMove.y);

    //prevents dragging from giving more than max speed
    if (x_speed > max_speed) {
        x_speed = max_speed;
    }
    if (y_speed > max_speed) {
        y_speed = max_speed;
    }
}

void playingGui::initLevel() {
    //clear world
    physicsWorld_->clearWorld();
    physicsWorld_->addGround();
    track_score = 0;
    //add boxes
    for (auto boxCoord : level_->boxCoords()) {
        b2Body* boxBody = physicsWorld_->addSquare(boxCoord.first, boxCoord.second, 4);
        boxes_.push_back(new Box(boxBody, buildTexture_));
        
    }
    //add enemies
    for (auto enemyCoord : level_->enemyCoords()) {
        b2Body* boxBody = physicsWorld_->addCircle(enemyCoord.first, enemyCoord.second, 2);
        enemies_.push_back(new Enemy(boxBody, enemyTexture_));
    }
    //add playable Planes
    for (auto planeProperties : level_->planeData()) {

        if (planeProperties.first == 0) {
            planesLeft.emplace_back(planeTexture0_, planeProperties.second);
        } else if (planeProperties.first == 1) {
            planesLeft.emplace_back(planeTexture1_, planeProperties.second);
        } else {
            planesLeft.emplace_back(planeTexture2_, planeProperties.second);
        }
    }
    shots_left = planesLeft.size();

}


//used for testing hitboxes
void playingGui::drawRange() {
    sf::CircleShape range(cursor_arrea);
    range.setFillColor(sf::Color(255, 255, 255, 0));
    range.setOutlineThickness(-3);
    range.setOutlineColor({ 255,255,255 });
    range.setPosition({ spawn_x , spawn_y });

    sf::RectangleShape testpos({ 1.f, 1.f });
    testpos.setFillColor(sf::Color::Red);
    testpos.setPosition(spawn_x+cursor_arrea, spawn_y+cursor_arrea);

    window_.draw(testpos);
    window_.draw(range);
}

//displays how many shots are left
void playingGui::display_shots() {
    
    shotcounter.setFont(font);
    string aki = to_string(shots_left);
    shotcounter.setString("Shots: "+aki);
    shotcounter.setCharacterSize(25);
    shotcounter.setFillColor(sf::Color::White);
    shotcounter.setStyle(sf::Text::Bold);
    shotcounter.setPosition(100,0);
    window_.draw(shotcounter);
}

void playingGui::drawPlayerToBeLaunched() {
    if (!planesLeft.empty()) {
        currentPlayable_.setTexture(planesLeft[0].first);
        currentPlayable_.setScale(0.25f, 0.25f);
        currentPlayable_.setOrigin(currentPlayable_.getLocalBounds().width/2, currentPlayable_.getLocalBounds().height/2);
        currentPlayable_.setPosition(200+40, 200+40);
        window_.draw(currentPlayable_);
    }
}

void playingGui::draw_victory(sf::Event e) {

    //ads points for unused ammo
    if (!score_counted) {
        for (int i = 0; i < shots_left + 1; i++) {
            track_score += 500;
        }
        score_counted = true;
    }

    window_.draw(victory_screen_);

    end_score.setFont(font);
    string aki = to_string(track_score);
    end_score.setString("Your Score: " + aki);
    end_score.setCharacterSize(75);
    end_score.setFillColor(sf::Color::Black);
    end_score.setStyle(sf::Text::Bold);
    end_score.setOutlineThickness(1);
    end_score.setOutlineColor({ 255,255,255 });
    end_score.setPosition(325, 425);
    window_.draw(end_score);

    
    if (e.type==sf::Event::MouseButtonPressed) {
        start_wincon = false;
        game_on = false;
        won = false;
        score_counted = false;
        planesLeft.clear();
        planes_.clear();
        boxes_.clear();
        enemies_.clear();
    }
}
