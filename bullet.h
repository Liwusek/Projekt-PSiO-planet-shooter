#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>


class Bullet : public sf::CircleShape
{
public:
    Bullet();
    int getSpeed();
    void setDir(sf::Vector2f dir);
    sf::Vector2f getDir();
    bool dead = false;
private:
    int size_ = 5;
    int speed_ = 300;
    sf::Vector2f dir;
};

#endif // BULLET_H
