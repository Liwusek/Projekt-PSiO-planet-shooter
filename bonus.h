#ifndef BONUS_H
#define BONUS_H
#include "platform.h"
#include "player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>

class Bonus : public sf::Sprite
{
public:
    Bonus(std::vector<std::unique_ptr<sf::Drawable>> &things);
    static void bonus_generator(sf::Time &time, sf::Clock &clock, std::vector<std::unique_ptr<sf::Drawable>> &things, int bonus_pause);
    Type random();
    Type type(Type type);
    bool touch(std::unique_ptr<Player> &player);
    void send(std::unique_ptr<Player> &player);
private:
    Type type_;
    int size_ = 50;
    int hight = 10;
    sf::Texture texture_;
    sf::Vector2f speed_;
    int aid_;
    int fire_rate_;
};

#endif // BONUS_H
