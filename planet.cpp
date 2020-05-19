#include "planet.h"


Planet::Planet()
{

}

Planet::Planet(int radius, sf::RenderWindow &window)
    :sf::CircleShape(radius), Functions(window), radius_(radius)
{
    setOrigin(radius, radius);
    setPosition(screen_bounds.x/2, screen_bounds.y/2);
    setFillColor(sf::Color::Red);
}
