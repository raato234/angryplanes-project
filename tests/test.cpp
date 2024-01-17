#include <iostream>
#include <string>
//#include "../src/game.hpp"
//#include "../src/gameobject.hpp"
//#include "../src/enemy.hpp"
#include <SFML/Graphics.hpp>


using namespace std;

// to run and up the exe with out sfml:
// cd src
// g++ -IC:\SFML-2.5.1\include -c test.cpp -o test.o
// g++ -LC:\SFML-2.5.1\lib .\test.o -o app.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -mwindows

class Filemanager {
    public:


    private:

};

class Gameobject {
  public: 

    Gameobject(double x, double y); 

    std::pair<double,double> GetPos() const; //returns the coordinates in x,y pair

 //   virtual void update() = 0; // pure virtual function, subclasses will implement this

  private:
    double x_,y_;

};
Gameobject::Gameobject(double x, double y)
  : x_(x),y_(y) {}

std::pair<double,double> Gameobject::GetPos() const {
    return std::make_pair(x_,y_);
}

class Enemy : public Gameobject {

public:

    Enemy(double x, double y)
         :Gameobject(x,y) {}

private:

};

class Game {

    public:

    ~Game();
    double GetScore() const;
    void Add(Gameobject* g);
    std::vector<Gameobject*>::iterator objectIterator = objects_.begin();
 //   bool Load(); //loads a game. return true if succesful, else return false
   // bool Save();


    private:
    
    std::vector<Gameobject*> objects_;
    double score_;
    Filemanager filemanager_;


};
void Game::Add(Gameobject* g) {
    objects_.push_back(g);
}

double Game::GetScore() const {
    return score_;
}

Game::~Game() {
    for (auto object : objects_)  delete object;
}
class Projectile : public Gameobject {

public: 
    Projectile(double x, double y)
        :Gameobject(x,y) {}



private:

};




struct vec2 {
    float x, y;
};

struct ball {
    vec2 pos, vel;
    bool flying;
};

ball update(ball b, float dt) {
    b.pos = {
        b.pos.x + b.vel.x * dt, 
        b.pos.y + b.vel.y * dt - (1.f / 2.f) * 100.f * dt * dt
    };
    b.vel.y -= 100.f * dt;
    return b;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    sf::CircleShape shape(5.f);

    Game testGame;
    testGame.Add(new Enemy(500,500));
    


    shape.setFillColor(sf::Color::Green);

    ball b{
        {0.f, 0.f},
        {0.f, 0.f},
        false
    };
    b.flying = true;
    
    float speed = 5.f;
    sf::Clock timer;
    while (window.isOpen())
    {
        float dt = timer.getElapsedTime().asSeconds();
        timer.restart();

        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();

            if (e.type == sf::Event::MouseButtonPressed) {
                b.flying = false;
                b.pos = vec2{(float)e.mouseButton.x, 200.f - (float)e.mouseButton.y};
            }
            if (e.type == sf::Event::MouseMoved && !b.flying) {
                b.vel = vec2{
                    speed * (b.pos.x - (float)e.mouseMove.x), 
                    speed * (b.pos.y - (200.f - (float)e.mouseMove.y))
                };
            }
            if (e.type == sf::Event::MouseButtonReleased) {
                b.vel = vec2{
                    speed * (b.pos.x - (float)e.mouseButton.x), 
                    speed * (b.pos.y - (200.f - (float)e.mouseButton.y))
                };
                b.flying = true;
            }
        }

        window.clear();

        if(b.flying)
            b = update(b, dt);
        
        shape.setFillColor({0, 255, 0});
        shape.setPosition({b.pos.x, 200.f - b.pos.y});
        window.draw(shape);
        
        if (!b.flying) {
            if(b.vel.x * b.vel.x + b.vel.y * b.vel.y > 10.f){
                for (int i = 1; i < 10; i++) {
                    ball a = update(b, i * .5f);
                    shape.setFillColor({255, 0, 0});
                    shape.setPosition({a.pos.x, 200.f - a.pos.y});
                    window.draw(shape);
                }
            }
        }

        window.display();
    }
	return 0;
}