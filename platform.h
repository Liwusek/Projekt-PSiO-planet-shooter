#ifndef PLATFORM_H
#define PLATFORM_H
#include <SFML/Graphics.hpp>
#include <memory>

class Platform : public sf::RectangleShape
{
public:
    Platform();
    Platform(int x, int y, sf::Vector2f size, sf::Vector2f texture_size, std::string texture_name);
    void repeate(float x, float y = 1);
    static void platform_maker(sf::Vector2f quantity, sf::Vector2f size, sf::Vector2f screen,
    sf::Vector2f texture_size, std::string texture_name, sf::Vector2f texture_multi, std::vector<std::unique_ptr<sf::Drawable>> &vector);
    sf::Vector2f get_size();
private:
    sf::Texture texture_;
    sf::Vector2f size_;
    sf::Vector2f texture_size;

};

#endif // PLATFORM_H

