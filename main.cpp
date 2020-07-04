#include <iostream>
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
    sf::Vector2f window_size = {800, 600};
    sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "Planet shooter"); //okno gry

    //////////////////////GRACZE//////////////////////
    std::vector<std::unique_ptr<Player>> players; //tworzenie graczy
    players.emplace_back(std::make_unique<Player>(window, "player.png")); //gracz1
    players.emplace_back(std::make_unique<Player>(window, "player.png")); //gracz2

    //////////////////////KAMERA//////////////////////
    std::vector<std::unique_ptr<sf::View>> views; //split screen
    std::unique_ptr view1 = std::make_unique<sf::View>(); //gracz1
    view1->setViewport(sf::FloatRect(0, 0, 0.5f, 0.9f));
    view1->setSize(sf::Vector2f(window_size.x/2, window_size.y*0.9));
    views.emplace_back(move(view1));
    std::unique_ptr view2 = std::make_unique<sf::View>(); //gracz2
    view2->setViewport(sf::FloatRect(0.5, 0, 0.5f, 0.9f));
    view2->setSize(sf::Vector2f(window_size.x/2, window_size.y*0.9));
    views.emplace_back(move(view2));
//    std::unique_ptr view_inter = std::make_unique<sf::View>(); //interface
//    view2->setViewport(sf::FloatRect(0, 0.9f, 0, 0.1f));
//    view_inter->setSize(sf::Vector2f(window_size.x, window_size.y*0.1));
//    views.emplace_back(move(view_inter));

     //////////////////////INTERFACE//////////////////////
//    int bar_offset = window_size.y*0.1;
//    sf::RectangleShape bar(sf::Vector2f(window_size.x, bar_offset));
//    bar.setPosition(0, window_size.y - bar_offset);
//    bar.setFillColor(sf::Color::Blue);

     //////////////////////PLATFORMY//////////////////////
    std::vector<std::unique_ptr<sf::Drawable>> platforms;
    int ground_offset = 100;
    std::unique_ptr base = std::make_unique<Platform>(-ground_offset, window.getSize().y - ground_offset, sf::Vector2f(window.getSize().x + ground_offset, ground_offset), sf::Vector2f(500, 500), "mars.jpg");
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

        for (size_t i = 0; i < players.size(); ++i){
            views[i]->setCenter(sf::Vector2f(players[i]->getPosition()));
            window.setView(*views[i]);
            window.draw(*players[i]);
            bool on_platform = players[i]->gravity(1, platforms);
            players[i]->animation(on_platform);
            players[i]->control(on_platform);
            players[i]->collision(platforms);

            for (auto &platform:platforms) {
                window.draw(*platform);
            }

        }
        //sf::View interface = *views[2];
        //window.setView(interface);
        //window.draw(bar);

        window.display();
    }
    return 0;
}
