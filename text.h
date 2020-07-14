#ifndef TEXT_H
#define TEXT_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Text : public sf::Text
{
public:
    Text();
    Text(sf::Vector2f position, int size_);
private:
    int size_;
    sf::Font font;

};

#endif // TEXT_H
