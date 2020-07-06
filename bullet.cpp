#include "bullet.h"

Bullet::Bullet() : sf::CircleShape()
{
    setRadius(size_);
}

Bullet::~Bullet()
{

}

int Bullet::getSpeed()
{
    return speed_;
}

void Bullet::setDir(sf::Vector2f dir)
{
    this->dir = dir;
}

sf::Vector2f Bullet::getDir()
{
    return dir;
}
