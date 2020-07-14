#include "text.h"

Text::Text(sf::Vector2f position, int size_):sf::Text(), size_(size_)
{
    font.loadFromFile("font.ttf");
    setFont(font);
    setPosition(position);
    setCharacterSize(size_);
}
