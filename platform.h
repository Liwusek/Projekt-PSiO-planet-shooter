#ifndef PLATFORM_H
#define PLATFORM_H
#include <SFML/Graphics.hpp>


class Platform : public sf::RectangleShape
{
public:
    Platform();
    Platform(int x, int y, sf::Vector2f size, sf::Vector2f texture_size, std::string texture_name);
    void repeate(int x, int y = 1);
private:
    sf::Texture texture_;
    sf::Vector2f size_;
    sf::Vector2f texture_size;

};

#endif // PLATFORM_H
