#include "background.h"

Background::Background(sf::Vector2f size, sf::Vector2f texture_size, std::string texture_name):
    sf::RectangleShape(size), size_(size), texture_size(texture_size)
{
    setPosition(0, 0);
    texture_.loadFromFile(texture_name);
    texture_.setRepeated(true);
    setTexture(&texture_);
}

void Background::repeate(float x, float y)
{
    setTextureRect( sf::IntRect(0, 0, texture_size.x*x, texture_size.y*y));
}
