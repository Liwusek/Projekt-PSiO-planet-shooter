#include "bonus.h"
#include <iostream>


Bonus::Bonus(std::vector<std::unique_ptr<sf::Drawable>> &things):sf::Sprite()
{
    Platform *platform;
    do{
        int index = rand() % things.size();
        platform = dynamic_cast<Platform *>(things[index].get());
    }while (platform == nullptr);
    //setSize(sf::Vector2f(size_,size_));
    setPosition(sf::Vector2f(platform->getPosition().x + platform->get_size().x/2, platform->getPosition().y - size_ - hight));
}

void Bonus::bonus_generator(sf::Time &time, sf::Clock &clock, std::vector<std::unique_ptr<sf::Drawable>> &things, int bonus_pause)
{
    if(time.asSeconds()>bonus_pause){
        std::unique_ptr<Bonus> bonus = std::make_unique<Bonus>(things);
        bonus->type_ = bonus->type(bonus->random());
        things.emplace_back(std::move(bonus));
        time = clock.restart();
    }
}

Type Bonus::random()
{
    Type type;
    int random = rand() % 4;
    switch(random)
    {
    case 0:
        type = Type::aid;
        break;

    case 1:
        type = Type::gun;
        break;
    case 2:
        type = Type::speed;
        break;

    }
    return type;
}

Type Bonus::type(Type type)
{
    if(type == Type::aid){
        texture_.loadFromFile("aid.png");
        setTexture(texture_);
        return Type::aid;
    }
    if(type == Type::gun){
        texture_.loadFromFile("gun.png");
        setTexture(texture_);
        return Type::gun;
    }
    if(type == Type::speed){
        texture_.loadFromFile("speed.png");
        setTexture(texture_);
        return Type::speed;
    }
    return Type::aid;
}

bool Bonus::touch(std::unique_ptr<Player> &player)
{
    if(player->getGlobalBounds().intersects(getGlobalBounds()))
        return true;
    else return false;
}

void Bonus::send(std::unique_ptr<Player> &player)
{
    player->bonus_type = type_;
}
