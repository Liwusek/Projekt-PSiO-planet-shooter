#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "platform.h"
#include "bullet.h"
#include <list>

enum class input{
    keybord_mouse,
    gamepad
};

class Player : public sf::Sprite
{
public:
    Player(sf::RenderWindow &window, std::string texture_name, input, unsigned int joy=0);
    void control(bool on_platform);
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

    std::list<std::unique_ptr<Bullet>> bullets;
private:
    sf::Vector2f sprite_size;
    sf::Vector2f image_count;
    sf::IntRect rect;
    sf::Clock clock;
    input input_;
    unsigned int joy_nr;
    Bullet bullet_;

    float move_speed_ = 200;
    float jump_speed_ = 200;
    sf::Vector2f velocity = {0, 0};
    sf::Vector2f window_size;
};

#endif // PLAYER_H
