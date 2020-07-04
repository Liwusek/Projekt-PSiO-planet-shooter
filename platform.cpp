#include "platform.h"
#include <memory>

Platform::Platform()
{}

Platform::Platform(int x, int y, sf::Vector2f size, sf::Vector2f texture_size, std::string texture_name):
    sf::RectangleShape(size), size_(size), texture_size(texture_size)
{
    texture_.loadFromFile(texture_name);
    texture_.setRepeated(true);
    setTexture(&texture_);
    setPosition(x, y);
}

void Platform::repeate(int x, int y)
{
    setTextureRect( sf::IntRect(0, 0, texture_size.x*x, texture_size.y*y));
}
