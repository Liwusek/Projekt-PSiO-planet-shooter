#ifndef BONUS_H
#define BONUS_H
#include "platform.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>

class Bonus : sf::RectangleShape
{
public:
    Bonus(const std::vector<std::unique_ptr<sf::Drawable> > &things);
    static void bonus_generator(sf::Clock clock, std::vector<std::unique_ptr<sf::Drawable>> &things);
private:
    int size_ = 10;
    int hight = 5;
};

#endif // BONUS_H
