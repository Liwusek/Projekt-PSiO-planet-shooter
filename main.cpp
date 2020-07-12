#include <iostream>
#include <memory>
#include <vector>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "player.h"
#include  "platform.h"
#include "background.h"
#include "bullet.h"

using namespace std;



int main()
{
    string platform_texture = "moon.png";


    //////////////////////OKNO//////////////////////
    sf::Vector2f window_size = {1600, 900};
    sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "Planet shooter"); //okno gry

    //////////////////////GRACZE//////////////////////
    std::vector<std::unique_ptr<Player>> players; //tworzenie graczy
    players.emplace_back(std::make_unique<Player>(window, "player.png", input::gamepad, 1)); //gracz1
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
    Background bar(sf::Vector2f(window_size.x, bar_offset), sf::Vector2f(100, 100), "background.png");
    bar.setPosition(interface_pos);
    bar.setOrigin(window_size.x/2, bar_offset/2);
    //bar.setFillColor(sf::Color::Green);
    std::unique_ptr<sf::View>  view_inter = std::make_unique<sf::View>(); //interface
    view_inter->setViewport(sf::FloatRect(0, proportion, 1.0f, 1.0f - proportion));
    view_inter->setSize(sf::Vector2f(window_size.x, window_size.y*0.1));
    view_inter->setCenter(bar.getPosition());
    views.emplace_back(move(view_inter));

    //////////////////////TLO//////////////////////
    std::unique_ptr<Background> background = std::make_unique<Background>(window_size, sf::Vector2f(700, 700), "background.png");
    background->repeate(2, 1);
    //    background.setFillColor(sf::Color::Red);
    //    sf::RectangleShape back(window_size);
    //    back.setFillColor(sf::Color::Green);

    //////////////////////PLATFORMY//////////////////////
    std::vector<std::unique_ptr<sf::Drawable>> things;
    int ground_overlap = 200;
    std::unique_ptr<Platform> base = std::make_unique<Platform>(-ground_overlap, window.getSize().y, sf::Vector2f(window.getSize().x + 2*ground_overlap, ground_overlap), sf::Vector2f(100, 100), platform_texture);
    base->repeate(30, 3);
    things.emplace_back(move(base));

    Platform::platform_maker(sf::Vector2f(3, 5), sf::Vector2f(200, 30), window_size,
                             sf::Vector2f(100, 100), platform_texture, sf::Vector2f(3, 1), things);





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
//        window.draw(*background);
        sf::Time time = clk.restart();
        for (size_t i = 0; i < players.size(); ++i){
            views[i]->setCenter(sf::Vector2f(players[i]->getPosition()));
            window.setView(*views[i]);
            for (auto const &player:players)
            window.draw(*player);
            bool on_platform = players[i]->gravity(4, things);
            players[i]->animation(on_platform);
            players[i]->control(on_platform);
            players[i]->collision(things);
            players[i]->movement();
            players[i]->teleport();
            players[i]->shooting();
            players[i]->jetpack(on_platform);
            players[i]->bulets_remove();

            for (auto const &player:players){
                for (auto const &bullet:player->bullets){
                    bullet->move(bullet->getDir()*time.asSeconds());
                    window.draw(*bullet);
                    if(!bullet->dead)bullet->dead = bullet->is_dead(window_size, things);
                }
            }

            players[0]->hit(players[1]);
            players[1]->hit(players[0]);


            for(size_t i=0; i<things.size(); i++){
                Platform *platform = dynamic_cast<Platform *>(things[i].get());
                if (platform != nullptr)window.draw(*platform);
            }


        }

        sf::View interface = *views[views.size()-1];
        window.setView(interface);
        window.draw(bar);

        window.display();
    }
    return 0;
}
