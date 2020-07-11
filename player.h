#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "platform.h"
#include "bullet.h"
#include <vector>

enum class input{
    keybord_mouse,
    gamepad
};

class Player : public sf::Sprite
{
public:
    Player(sf::RenderWindow &window, std::string texture_name, input, unsigned int joy=0);
    void control(bool on_platform);
    void jetpack(bool on_platform);
    bool gravity(float a, const std::vector<std::unique_ptr<sf::Drawable>> &platforms);
    void collision(const std::vector<std::unique_ptr<sf::Drawable>> &platforms);
    sf::Texture texture;
    void animation(bool on_platform);
    void image_select(float x, float y, bool is_right = true);
    void teleport();
    void movement();
    void shooting();
    sf::Vector2f shooting_dir();
    bool bullets_delete(const std::vector<std::unique_ptr<sf::Drawable>> &vector);
    std::vector<std::unique_ptr<Bullet>> bullets;
    void hit(std::vector<std::unique_ptr<Player>> players);
    int life = 100;
private:
    sf::Vector2f sprite_size;
    sf::Vector2f image_count;
    sf::IntRect rect;
    sf::Clock clock;
    sf::Clock clock2;
    input input_;
    unsigned int joy_nr;
    Bullet bullet_;

    float fire_rate = 10;
    float move_speed_ = 200;
    float jump_speed_ = 200;
    sf::Vector2f velocity = {0, 0};
    sf::Vector2f window_size;
};

#endif // PLAYER_H
