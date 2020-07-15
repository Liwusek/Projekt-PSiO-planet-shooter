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
enum class Type{
    aid,
    gun,
    speed
};


class Player : public sf::Sprite
{
public:
    Player(sf::RenderWindow &window, std::string texture_name, input, unsigned int joy=0);
    sf::Texture texture;
    void control(bool on_platform);
    void jetpack(bool on_platform);
    void hit(const std::unique_ptr<Player> &player);
    void collision(const std::vector<std::unique_ptr<sf::Drawable>> &platforms);
    void animation(bool on_platform);
    void teleport();
    void movement();
    void shooting();
    void bulets_remove();
    void respawn(int hight, const std::vector<std::unique_ptr<sf::Drawable>> &platforms);
    void bonus();
    void hight_limit();
    int get_life();
    int get_score();
    bool gravity(float a, const std::vector<std::unique_ptr<sf::Drawable>> &platforms);
    bool active_bonus = false;
    Type bonus_type;
    std::vector<std::unique_ptr<Bullet>> bullets;

private:


    void image_select(float x, float y, bool is_right = true);
    sf::Vector2f shooting_dir();
    sf::Vector2f velocity = {0, 0};
    sf::Vector2f window_size;
    sf::Vector2f sprite_size;
    sf::Vector2f image_count;
    sf::IntRect rect;
    sf::Clock clock;
    sf::Clock clock2;
    sf::Clock bonus_clock;

    input input_;
    Bullet bullet_;
    unsigned int joy_nr;
    int bonus_duration = 10;
    int life = 0;
    int score = -1;
    int damage = 10;
    float fire_rate = 5;
    float fire_rate_old;
    float move_speed_ = 200;
    float jump_speed_ = 200;
    float move_speed_old;
    float jump_speed_old;

    bool jetpack_ = false;
};

#endif // PLAYER_H
