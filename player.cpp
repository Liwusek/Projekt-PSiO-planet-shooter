#include "player.h"
#include <string>
#include <iostream>
#include <cmath>
#include <iostream>
#include <memory>

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
    setOrigin(sprite_size.x/2, sprite_size.y/2);
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
        if(sf::Joystick::isButtonPressed(joy_nr, 0))
            if(velocity.y == 0 && on_platform)velocity.y = -jump_speed_;

        if(sf::Joystick::getAxisPosition(joy_nr, sf::Joystick::Axis::X) == 100)velocity.x = move_speed_;
        else if(sf::Joystick::getAxisPosition(joy_nr, sf::Joystick::Axis::X) == -100)velocity.x = -move_speed_;
        else velocity.x = 0;

    }
}

void Player::jetpack(bool on_platform)
{
    if(input_ == input::gamepad){
        if(sf::Joystick::isButtonPressed(joy_nr, 0) && (on_platform == false))
            velocity.y = -jump_speed_;
    }
}

bool Player::gravity(float a, const std::vector<std::unique_ptr<sf::Drawable>> &vector)
{
    int tolerance = 0;
    for(size_t i=0; i<vector.size(); i++){
        Platform *platform = dynamic_cast<Platform *>(vector[i].get());
        if (platform != nullptr){
            if(platform->getGlobalBounds().contains(getPosition() + sf::Vector2f(-sprite_size.x/2 + tolerance, -sprite_size.y/2)) || platform->getGlobalBounds().contains(getPosition() + sf::Vector2f(sprite_size.x/2 - tolerance, sprite_size.y/2))){
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
            if(platform->getGlobalBounds().contains(getPosition() + sf::Vector2f(0, -sprite_size.y/2))){ //góra sprita
                velocity.y = 0;
                move(0, far);
            }
            if(platform->getGlobalBounds().contains(getPosition() + sf::Vector2f(-sprite_size.x/2, -sprite_size.y/2 + tolerance_top)) || platform->getGlobalBounds().contains(getPosition() + sf::Vector2f(-sprite_size.x/2, 0)) || platform->getGlobalBounds().contains(getPosition() + sf::Vector2f(-sprite_size.x/2, sprite_size.y - tolerance_bottom))){ //lewa sprita
                move(far, 0);
            }
            if(platform->getGlobalBounds().contains(getPosition() + sf::Vector2f(sprite_size.x/2, -sprite_size.y/2 + tolerance_top)) || platform->getGlobalBounds().contains(getPosition() + sf::Vector2f(sprite_size.x/2, 0)) || platform->getGlobalBounds().contains(getPosition() + sf::Vector2f(sprite_size.x/2, sprite_size.y - tolerance_bottom))){ //prawa sprita
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
//    else if(getPosition().y>window_size.y)setPosition(getPosition().x, 0);
//    else if(getPosition().y<0)setPosition(getPosition().x, window_size.y);
}

void Player::movement()
{
    sf::Time time = clock.restart();
    move(velocity*time.asSeconds());
}

sf::Vector2f Player::shooting_dir()
{
    sf::Vector2f dir = {sf::Joystick::getAxisPosition(joy_nr, sf::Joystick::Axis::U), sf::Joystick::getAxisPosition(joy_nr, sf::Joystick::Axis::V)};
    sf::Vector2f dir_norm;
    dir_norm.x = dir.x / sqrt(pow(dir.x, 2) + pow(dir.y, 2));
    dir_norm.y = dir.y / sqrt(pow(dir.x, 2) + pow(dir.y, 2));
    sf::Vector2f dir_end;
    dir_end.x = dir_norm.x*bullet_.getSpeed();
    dir_end.y = dir_norm.y*bullet_.getSpeed();
    return dir_end;
}

bool Player::bullets_delete(const std::vector<std::unique_ptr<sf::Drawable>> &vector)
{
    for(auto &bullet : bullets){
        for (auto it = bullets.begin(); it != bullets.end(); it++){
            for(size_t i=0; i<vector.size(); i++){
                Platform *platform = dynamic_cast<Platform *>(vector[i].get());
                if (platform != nullptr){
                    if(platform->getGlobalBounds().contains(bullet->getPosition())){
                        bullets.erase(it);
                        return true;
                    }
                }
            }

            if((bullet->getPosition().x>window_size.x)
                    ||(bullet->getPosition().x<0)
                    ||(bullet->getPosition().y>window_size.y)
                    ||(bullet->getPosition().y<0)){
                bullets.erase(it);
                return true;
            }


        }
    }
    return false;
}

void Player::bulets_remove()
{
        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](auto const& bullet){ return bullet->dead; }), bullets.end());
}

void Player::hit(const std::unique_ptr<Player> &player)
{
    for (auto const &bullet:player->bullets){
        if(getGlobalBounds().contains(bullet->getPosition()))life -= 1;
        std::cout<<life<<std::endl;

    }

}

void Player::shooting()
{
    if(input_ == input::gamepad){
        std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>();
//        Bullet *bullet = new Bullet();
        float time = clock2.getElapsedTime().asSeconds();
        if(sf::Joystick::getAxisPosition(joy_nr, sf::Joystick::Axis::Z)<-50 && time > 1/fire_rate){
            bullet->setPosition(getPosition());
            bullet->setDir(shooting_dir());
            bullets.emplace_back(std::move(bullet));
//            bullets.emplace_back(bullet);
            clock2.restart();

        }

    }

}



