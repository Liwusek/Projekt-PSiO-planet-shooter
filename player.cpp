#include <math.h>
#include "player.h"

Player::Player(sf::RenderWindow &window)
    :sf::RectangleShape(sf::Vector2f(10, 10)),
    //sf::Transform(),
      Functions(window)
{
    setFillColor(sf::Color::Green);
    setPosition(100, 100);
    setOrigin(5, 5);
}

void Player::gravity()
{
    const float PI = 3.14159265;
    double angle = atan2(screen_bounds.x - getPosition().x, screen_bounds.y - getPosition().y) * 180 / PI;
    double angle2 = atan2(getPosition().x - screen_bounds.x, getPosition().y - screen_bounds.y) * 180 / PI;
    setRotation(angle2);
    move(0, speed_.y*getTime());
}
