#include "platform.h"
#include <memory>
#include <iostream>

Platform::Platform()
{}

Platform::Platform(int x, int y, sf::Vector2f size, sf::Vector2f texture_size, std::string texture_name):
    sf::RectangleShape(size), size_(size), texture_size(texture_size)
{
    texture_.loadFromFile(texture_name);
    texture_.setRepeated(true);
    setTexture(&texture_);
    setPosition(x, y);
}

void Platform::repeate(int x, int y)
{
    setTextureRect( sf::IntRect(0, 0, texture_size.x*x, texture_size.y*y));
}


void Platform::platform_maker(sf::Vector2f quantity, sf::Vector2f size, float space, sf::Vector2f screen,
sf::Vector2f texture_size, std::string texture_name, std::vector<std::unique_ptr<sf::Drawable>> &vector)
{
    space = screen.y / quantity.y;
    screen.y = screen.y - space;
    screen.x = screen.x - size.x;
    for (int i = 0; i < quantity.y; ++i){
        for (int i = 0; i < quantity.x; ++i){
            bool are_colliding = false;
            std::unique_ptr<Platform> new_platform;
            do{
                new_platform = std::make_unique<Platform>(rand() % int(screen.x), screen.y, size, texture_size, texture_name);
                for(size_t i=0; i<vector.size(); i++){
                    Platform *platform = dynamic_cast<Platform *>(vector[i].get());
                    if (platform != nullptr){
                        if(platform->getGlobalBounds().intersects(new_platform->getGlobalBounds())){
                            are_colliding = true;
                            std::cout<<"dupa"<<std::endl;
                        }
                    }
                }

            }while(are_colliding);
            std::cout<<"DUPA"<<std::endl;
            vector.emplace_back(std::move(new_platform));
        }
            screen.y -= space;
            if(screen.y <= size.y) break;
    }
}
