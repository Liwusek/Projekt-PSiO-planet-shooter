#include "bullet.h"

Bullet::Bullet() : sf::CircleShape()
{
    setRadius(size_);
    setOrigin(size_, size_);
    setFillColor(sf::Color::Green);
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

bool Bullet::is_dead(sf::Vector2f window_size, const std::vector<std::unique_ptr<sf::Drawable>> &vector)
{
            for(size_t i=0; i<vector.size(); i++){
                Platform *platform = dynamic_cast<Platform *>(vector[i].get());
                if (platform != nullptr){
                    if(platform->getGlobalBounds().contains(getPosition())){
                        return true;
                    }
                }
            }

            if((getPosition().x>window_size.x)
                    ||(getPosition().x<0)
                    ||(getPosition().y>window_size.y)
                    ||(getPosition().y<0)){
                return true;
            }
    return false;
}


