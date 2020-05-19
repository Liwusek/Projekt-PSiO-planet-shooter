#include "functions.h"

Functions::Functions()
{
}

Functions::Functions(sf::RenderWindow &window):sf::Clock()
{
    getBounds(window);
}

void Functions::getBounds(sf::RenderWindow &window)
{
    this->screen_bounds.x = window.getSize().x;
    this->screen_bounds.y = window.getSize().y;
}

float Functions::getTime()
{
    sf::Time time = restart();
    return time.asSeconds();
}




