#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Functions : public sf::Clock, public sf::Time
{
public:
    Functions();
    virtual ~Functions() = default;
    Functions(sf::RenderWindow &window);
    virtual void getBounds(sf::RenderWindow &window);
    virtual float getTime();

protected:

    sf::Vector2f screen_bounds;
};

#endif // FUNCTIONS_H
