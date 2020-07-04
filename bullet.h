#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>


class Bullet : public sf::CircleShape
{
public:
    Bullet();
private:
    int size_ = 5;
    int speed_;
    sf::Vector2f velocity_;
};

#endif // BULLET_H
