#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "platform.h"
#include <memory>


class Bullet : public sf::CircleShape
{
public:
    Bullet();
    ~Bullet();
    int getSpeed();
    void setDir(sf::Vector2f dir);
    sf::Vector2f getDir();
    bool is_dead(sf::Vector2f window_size, const std::vector<std::unique_ptr<sf::Drawable>> &vector);
    bool dead = false;

private:
    int size_ = 5;
    int speed_ = 300;
    sf::Vector2f dir;
};

#endif // BULLET_H
