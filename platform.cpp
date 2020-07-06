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


void Platform::platform_maker(int quantity, sf::Vector2f size, float space, sf::Vector2f screen,
sf::Vector2f texture_size, std::string texture_name, std::vector<std::unique_ptr<sf::Drawable>> &vector)
{
    float y = screen.y - space;
    screen.x = screen.x + 1 - size.x;
    for (int i = 0; i < quantity; ++i){
        vector.emplace_back(std::make_unique<Platform>(rand() % int(screen.x), y, size, texture_size, texture_name));
        y -= space;
    }
}
