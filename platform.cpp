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

void Platform::repeate(float x, float y)
{
    setTextureRect( sf::IntRect(0, 0, texture_size.x*x, texture_size.y*y));
}


void Platform::platform_maker(sf::Vector2f quantity, sf::Vector2f size, sf::Vector2f screen,
sf::Vector2f texture_size, std::string texture_name, sf::Vector2f texture_multi, std::vector<std::unique_ptr<sf::Drawable>> &vector)
{
    float space = screen.y / quantity.y;
    screen.y = screen.y - space;
    screen.x = screen.x - size.x;
    for (int i = 0; i < quantity.y; ++i){
        for (int i = 0; i < quantity.x; ++i){
            bool are_colliding;
            std::unique_ptr<Platform> new_platform;
            do{
                are_colliding = false;
                new_platform = std::make_unique<Platform>(rand() % int(screen.x), screen.y, size, texture_size, texture_name);
                new_platform->repeate(texture_multi.x, texture_multi.y);
                for(size_t i=0; i<vector.size(); i++){
                    Platform *platform = dynamic_cast<Platform *>(vector[i].get());
                    if (platform != nullptr){
                        if(platform->getGlobalBounds().intersects(new_platform->getGlobalBounds())){
                            are_colliding = true;
//                            std::cout<<"Wrong position, relocating"<<std::endl;
                        }
                    }
                }

            }while(are_colliding);
//            std::cout<<"Succes"<<std::endl;
            vector.emplace_back(std::move(new_platform));
        }
            screen.y -= space;
    }
}

sf::Vector2f Platform::get_size()
{
    return size_;
}
