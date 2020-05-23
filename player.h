#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "functions.h"

class Player : public sf::RectangleShape, public Functions
        //sf::Transform
{
public:
    Player(sf::RenderWindow &window);
    Player();
    void animate();
    void move1();
private:
    double gravity_pow = 5;
    bool is_midair;
    sf::Vector2f speedv_ = {100, 100};
    int speed_ = 1;
    //sf::Vector2f size_;


};

#endif // PLAYER_H
