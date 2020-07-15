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
    bool gravity(float a, const std::vector<std::unique_ptr<sf::Drawable>> &platforms);
    void collision(const std::vector<std::unique_ptr<sf::Drawable>> &platforms);
    void animation(bool on_platform);
    void teleport();
    void movement();
    void shooting();
    bool bullets_delete(const std::vector<std::unique_ptr<sf::Drawable>> &vector);
    void bulets_remove();
    std::vector<std::unique_ptr<Bullet>> bullets;
    void hit(const std::unique_ptr<Player> &player);
    int get_life();
    int get_fire_rate();
    sf::Vector2f get_speed();
    int get_score();
    void set_life(int life);
    void set_fire_rate(int fire_rate);
    void set_speed(float move, float jump);
    void respawn(int hight, const std::vector<std::unique_ptr<sf::Drawable>> &platforms);
    bool active_bonus = false;
    Type bonus_type;
private:

    void image_select(float x, float y, bool is_right = true);
    sf::Vector2f shooting_dir();
    int life = 0;
    sf::Vector2f sprite_size;
    sf::Vector2f image_count;
    sf::IntRect rect;
    sf::Clock clock;
    sf::Clock clock2;
    input input_;
    unsigned int joy_nr;
    Bullet bullet_;
    int score = -1;
    int damage = 10;
    float fire_rate = 10;
    float move_speed_ = 200;
    float jump_speed_ = 200;
    sf::Vector2f velocity = {0, 0};
    sf::Vector2f window_size;
};

#endif // PLAYER_H
