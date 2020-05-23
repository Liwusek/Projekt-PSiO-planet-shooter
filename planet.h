#ifndef PLANET_H
#define PLANET_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "functions.h"

class Planet : public sf::CircleShape, Functions
{
public:
    Planet();
    Planet(int radius, int spin, sf::RenderWindow &window);
    void animate();
private:
    int radius_;
    int spin_;
};

#endif // PLANET_H
