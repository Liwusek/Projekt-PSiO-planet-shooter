#include "planet.h"


Planet::Planet()
{

}

Planet::Planet(int radius, int spin, sf::RenderWindow &window)
    :sf::CircleShape(radius), Functions(window),
    radius_(radius), spin_(spin)
{
    setOrigin(radius, radius);
    setPosition(screen_bounds.x/2, screen_bounds.y/2);
    setFillColor(sf::Color::Red);
}
