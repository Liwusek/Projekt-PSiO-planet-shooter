#include <iostream>
#include <memory>
#include <vector>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "planet.h"
#include "player.h"
#include  "platform.h"

using namespace std;


int main()
{
    //////////////////////OKNO//////////////////////
    sf::Vector2f window_size = {1600, 900};
    sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "Planet shooter"); //okno gry

    //////////////////////GRACZE//////////////////////
    std::vector<std::unique_ptr<Player>> players; //tworzenie graczy
    players.emplace_back(std::make_unique<Player>(window, "player.png", input::keybord_mouse)); //gracz1
    players.emplace_back(std::make_unique<Player>(window, "player.png", input::gamepad)); //gracz2

    //////////////////////KAMERA//////////////////////
    float proportion = 0.8f;
    std::vector<std::unique_ptr<sf::View>> views; //split screen
    std::unique_ptr<sf::View> view1 = std::make_unique<sf::View>(); //gracz1
    view1->setViewport(sf::FloatRect(0, 0, 0.5f, proportion));
    view1->setSize(sf::Vector2f(window_size.x/2, window_size.y*proportion));
    views.emplace_back(move(view1));
    std::unique_ptr<sf::View>  view2 = std::make_unique<sf::View>(); //gracz2
    view2->setViewport(sf::FloatRect(0.5, 0, 0.5f, proportion));
    view2->setSize(sf::Vector2f(window_size.x/2, window_size.y*proportion));
    views.emplace_back(move(view2));


    //////////////////////INTERFACE//////////////////////
    sf::Vector2f interface_pos = {0, -1000};
    int bar_offset = window_size.y*(1.0f - proportion);
    sf::RectangleShape bar(sf::Vector2f(window_size.x, bar_offset));
    bar.setPosition(interface_pos);
    bar.setOrigin(window_size.x/2, bar_offset/2);
    bar.setFillColor(sf::Color::Green);
    std::unique_ptr<sf::View>  view_inter = std::make_unique<sf::View>(); //interface
    view_inter->setViewport(sf::FloatRect(0, proportion, 1.0f, 1.0f - proportion));
    view_inter->setSize(sf::Vector2f(window_size.x, window_size.y*0.1));
    view_inter->setCenter(bar.getPosition());
    views.emplace_back(move(view_inter));

     //////////////////////PLATFORMY//////////////////////
    std::vector<std::unique_ptr<sf::Drawable>> platforms;
    int ground_overlap = 200;
    std::unique_ptr<Platform> base = std::make_unique<Platform>(-ground_overlap, window.getSize().y, sf::Vector2f(window.getSize().x + 2*ground_overlap, ground_overlap), sf::Vector2f(500, 500), "mars.jpg");
    base->repeate(40);
    platforms.emplace_back(move(base));
    sf::Clock clk;

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
                break;
            }
        }

        window.clear(sf::Color::Black);
        sf::Time time = clk.restart();
        for (size_t i = 0; i < players.size(); ++i){
            views[i]->setCenter(sf::Vector2f(players[i]->getPosition()));
            window.setView(*views[i]);
            for (auto const &player:players)window.draw(*player);
            bool on_platform = players[i]->gravity(4, platforms);
            players[i]->animation(on_platform);
            players[i]->control(on_platform);
            players[i]->collision(platforms);
            players[i]->movement();
            players[i]->teleport();
            players[i]->shooting();
            for (auto const &player:players){
                for (auto const &bullet:player->bullets){
                    bullet->move(bullet->getDir()*time.asSeconds());
                    window.draw(*bullet);
                }
            }

            for (auto &platform:platforms) {
                window.draw(*platform);
            }

        }
        sf::View interface = *views[views.size()-1];
        window.setView(interface);
        window.draw(bar);

        window.display();
    }
    return 0;
}
