#include "player.h"
#include <string>
#include <iostream>
#include <cmath>
#include <iostream>
#include <memory>

Player::Player(sf::RenderWindow &window, std::string texture_name, input input, unsigned int joy):sf::Sprite(),
      window_size(window.getSize()), image_count({8, 5}), input_(input), joy_nr(joy)
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


    fire_rate_old = fire_rate;
    move_speed_old = move_speed_;
    jump_speed_old = jump_speed_ ;
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

        if(sf::Joystick::getAxisPosition(joy_nr, sf::Joystick::Axis::X) >80 && sf::Joystick::getAxisPosition(joy_nr, sf::Joystick::Axis::X) < 120)velocity.x = move_speed_;
        else if(sf::Joystick::getAxisPosition(joy_nr, sf::Joystick::Axis::X) > -120 && sf::Joystick::getAxisPosition(joy_nr, sf::Joystick::Axis::X) < -80)velocity.x = -move_speed_;
        else velocity.x = 0;

    }
}

void Player::jetpack(bool on_platform)
{
    if(input_ == input::gamepad){
        if(sf::Joystick::isButtonPressed(joy_nr, 4) && (on_platform == false)){
            velocity.y = -jump_speed_;
            jetpack_ = true;
        }
        else jetpack_ = false;
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
        image_select(1, 1);
    }
    else if(velocity.x < 0 && on_platform){ //chodzenie w lewo
        image_select(1, 1, false);
    }
    else if((velocity.x >= 0) && (jetpack_ == true)){ //jetpack w prawo i w miejscu
        image_select(3, 3);
    }
    else if(velocity.x < 0 && jetpack_ == true){ //jetpack w lewo
        image_select(3, 3, false);
    }
    else if(velocity.x >= 0 && velocity.y > 0 && jetpack_ == false){ //skok w prawo i w miejscu
        image_select(2, 3);
    }

    else if(velocity.x < 0 && velocity.y > 0 && jetpack_ == false){ //skok w lewo
        image_select(2, 3, false);
    }


    else if(velocity.x >= 0 && velocity.y < 0){ //spadanie w prawo i w miejscu
        image_select(1, 3);
    }
    else if(velocity.x < 0 && velocity.y < 0){ //spadanie w lewo
        image_select(1, 3, false);
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

void Player::bulets_remove()
{
        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](auto const& bullet){ return bullet->dead; }), bullets.end());
}

void Player::hit(const std::unique_ptr<Player> &player)
{
    for (auto const &bullet:player->bullets){
        if(getGlobalBounds().contains(bullet->getPosition())){
            life -= damage;
            bullet->dead = true;
        }
    }

}

int Player::get_life()
{
    return life;
}

int Player::get_score()
{
    return score;
}


void Player::respawn(int hight, const std::vector<std::unique_ptr<sf::Drawable> > &things)
{
    if(life<=0){
        life = 100;
        Platform *platform;
        do{
            int index = rand() % things.size();
            platform = dynamic_cast<Platform *>(things[index].get());
        }while (platform == nullptr);
        setPosition(sf::Vector2f(platform->getPosition().x + platform->get_size().x/2, platform->getPosition().y + platform->get_size().y - sprite_size.y - hight));
        score += 1;
    }
}

void Player::bonus()
{
    if((bonus_type == Type::gun) && active_bonus && bonus_clock.getElapsedTime().asSeconds()<bonus_duration){
        fire_rate = 15;
    }
    else if((bonus_type == Type::aid) && active_bonus){
        if(life<=80)life += 20;
        active_bonus = false;
    }


    else if((bonus_type == Type::speed) && active_bonus && bonus_clock.getElapsedTime().asSeconds()<bonus_duration){

        move_speed_ = 400;
        jump_speed_ = 400;
    }
    else{
        bonus_clock.restart();
        fire_rate = fire_rate_old;
        move_speed_ = move_speed_old;
        jump_speed_ = jump_speed_old;
        active_bonus = false;
    }

}

void Player::hight_limit()
{
    if(getPosition().y<-400)
        life -= 1;
}

void Player::shooting()
{
    if(input_ == input::gamepad){
        std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>();
        float time = clock2.getElapsedTime().asSeconds();
        if(sf::Joystick::getAxisPosition(joy_nr, sf::Joystick::Axis::Z)<-50 && time > 1/fire_rate){
            bullet->setPosition(getPosition());
            bullet->setDir(shooting_dir());
            bullets.emplace_back(std::move(bullet));
            clock2.restart();

        }

    }

}



