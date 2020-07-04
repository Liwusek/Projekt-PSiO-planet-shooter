#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "platform.h"
enum class input{
    keybord_mouse,
    gamepad
};

class Player : public sf::Sprite
{
public:
    Player(sf::RenderWindow &window, std::string texture_name);
    void control(bool on_platform);
    bool gravity(float a, const std::vector<std::unique_ptr<sf::Drawable>> &platforms);
    void collision(const std::vector<std::unique_ptr<sf::Drawable>> &platforms);
    sf::Texture texture;
    void animation(bool on_platform);
    void image_select(float x, float y, bool is_right = true);

private:
    sf::Vector2f sprite_size;
    sf::Vector2f image_count;
    sf::IntRect rect;
    sf::Clock clock;

    float move_speed_ = 200;
    float jump_speed_ = 500;
    sf::Vector2f velocity = {0, 0};
    sf::Vector2f window_size;
};

#endif // PLAYER_H
