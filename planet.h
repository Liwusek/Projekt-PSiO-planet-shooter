#ifndef PLANET_H
#define PLANET_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "functions.h"

class Planet : public sf::CircleShape, Functions
{
public:
    Planet();
    Planet(int radius, sf::RenderWindow &window);
private:
    int radius_;
    sf::Vector3f color_;
};

#endif // PLANET_H
