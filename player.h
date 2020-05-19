#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "functions.h"

class Player : public sf::RectangleShape, public Functions,
        //sf::Transform
{
public:
    Player(sf::RenderWindow &window);
    Player();
    void gravity();
private:
    double gravity_pow = 5;
    bool is_midair;
    sf::Vector2f speed_ = {100, 100};
    //sf::Vector2f size_;


};

#endif // PLAYER_H
