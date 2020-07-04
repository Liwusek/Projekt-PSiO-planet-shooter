#include "player.h"
#include <string>
#include <iostream>
#include <cmath>
#include <iostream>

Player::Player(sf::RenderWindow &window, std::string texture_name, input input, unsigned int joy):sf::Sprite(),
    image_count({8, 5}), input_(input), joy_nr(joy), window_size(window.getSize())
{
    texture.loadFromFile(texture_name);
    texture.setSmooth(true);
    setTexture(texture);

    rect.width = texture.getSize().x / float(image_count.x);
    rect.height = texture.getSize().y / float(image_count.y);
    rect.left = 0;
    rect.top = 0;
    setTextureRect(rect);

    sprite_size = sf::Vector2f(rect.width, rect.height);
}

void Player::control(bool on_platform)
{
    if(input_ == input::keybord_mouse){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            if(velocity.y == 0 && on_platform)velocity.y = -jump_speed_;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))velocity.x = move_speed_;
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))velocity.x = -move_speed_;
        else velocity.x = 0;
    }
    else if(input_ == input::gamepad){
        std::cout<<sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X)<<std::endl;
        if(sf::Joystick::isButtonPressed(joy_nr, 3))
            if(velocity.y == 0 && on_platform)velocity.y = -jump_speed_;

        if(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) == 100)velocity.x = move_speed_;
        else if(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) == -100)velocity.x = -move_speed_;
        else velocity.x = 0;

    }
}

bool Player::gravity(float a, const std::vector<std::unique_ptr<sf::Drawable>> &vector)
{
    int tolerance = 0;
    for(size_t i=0; i<vector.size(); i++){
        Platform *platform = dynamic_cast<Platform *>(vector[i].get());
        if (platform != nullptr){
            if(platform->getGlobalBounds().contains(getPosition() + sf::Vector2f(tolerance, sprite_size.y)) || platform->getGlobalBounds().contains(getPosition() + sf::Vector2f(sprite_size.x - tolerance, sprite_size.y))){
                velocity.y = 0;
                return true;
            }
        }
    }
    velocity.y += a;
    return false;
}

void Player::collision(const std::vector<std::unique_ptr<sf::Drawable>> &vector)
{
    float far = move_speed_/60;
    int tolerance_top = 1;
    int tolerance_bottom = 5;
    for(size_t i=0; i<vector.size(); i++){
        Platform *platform = dynamic_cast<Platform *>(vector[i].get());
        if (platform != nullptr){
            if(platform->getGlobalBounds().contains(getPosition() + sf::Vector2f(sprite_size.x/2, 0))){ //góra sprita
                velocity.y = 0;
                move(0, far);
            }
            if(platform->getGlobalBounds().contains(getPosition() + sf::Vector2f(0, tolerance_top)) || platform->getGlobalBounds().contains(getPosition() + sf::Vector2f(0, sprite_size.y/2)) || platform->getGlobalBounds().contains(getPosition() + sf::Vector2f(0, sprite_size.y - tolerance_bottom))){ //lewa sprita
                move(far, 0);
            }
            if(platform->getGlobalBounds().contains(getPosition() + sf::Vector2f(sprite_size.x, tolerance_top)) || platform->getGlobalBounds().contains(getPosition() + sf::Vector2f(sprite_size.x, sprite_size.y/2)) || platform->getGlobalBounds().contains(getPosition() + sf::Vector2f(sprite_size.x, sprite_size.y - tolerance_bottom))){ //prawa sprita
                move(-far, 0);
            }

        }
    }
}

void Player::animation(bool on_platform)
{

    if(velocity.x == 0 && on_platform){ //stanie
        image_select(0, 0);
    }
    else if(velocity.x > 0 && on_platform){ //chodzenie w prawo
        image_select(5, 0);
    }
    else if(velocity.x < 0 && on_platform){ //chodzenie w lewo
        image_select(5, 0, false);
    }

    else if(velocity.x >= 0 && velocity.y > 0){ //skok w prawo i w miejscu
        image_select(6, 0);
    }
    else if(velocity.x < 0 && velocity.y > 0){ //skok w lewo
        image_select(6, 0, false);
    }

    else if(velocity.x >= 0 && velocity.y < 0){ //spadanie w prawo i w miejscu
        image_select(7, 0);
    }
    else if(velocity.x < 0 && velocity.y < 0){ //spadanie w lewo
        image_select(7, 0, false);
    }
    setTextureRect(rect);
}

void Player::image_select(float x, float y, bool is_right)
{
    if(is_right){
    sf::Vector2f image = {x, y};
    rect.left = image.x * rect.width;
    rect.top = image.y * rect.height;
    rect.width = abs(rect.width);
    sprite_size = sf::Vector2f(rect.width, rect.height);
    }
    else{
        sf::Vector2f image = {x, y};
        rect.left = (image.x + 1) * abs(rect.width);
        rect.top = image.y * rect.height;
        rect.width = -abs(rect.width);
        sprite_size = sf::Vector2f(abs(rect.width), abs(rect.height));
    }
}

void Player::teleport()
{
    if(getPosition().x>window_size.x)setPosition(0, getPosition().y);
    else if(getPosition().x<0)setPosition(window_size.x, getPosition().y);
    else if(getPosition().y>window_size.y)setPosition(getPosition().x, 0);
    else if(getPosition().y<0)setPosition(getPosition().x, window_size.y);
}

void Player::movement()
{
    sf::Time time = clock.restart();
    move(velocity*time.asSeconds());
}



