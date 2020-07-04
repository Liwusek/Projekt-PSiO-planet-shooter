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
    sf::Vector2f window_size = {800, 600};
    sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "Planet shooter");
    std::vector<std::unique_ptr<Player>> players;
    std::vector<std::unique_ptr<sf::View>> views;

    int quantity_players = 1;
    for (int i = 0; i < quantity_players; ++i){
        players.emplace_back(std::make_unique<Player>(window, "player.png"));
        std::unique_ptr view = std::make_unique<sf::View>();
        view->setSize(sf::Vector2f(200.f, 200.f));
        views.emplace_back(move(view));
    }

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

        for (auto &platform:platforms) {
                window.draw(*platform);
            }
        for (size_t i = 0; i < players.size(); ++i){
            views[i]->setCenter(sf::Vector2f(players[i]->getPosition()));
            //window.setView(*views[i]);
            window.draw(*players[i]);
                bool on_platform = players[i]->gravity(1, platforms);
                players[i]->animation(on_platform);
                players[i]->control(on_platform);
                players[i]->collision(platforms);

            }

        window.display();
    }
    return 0;
}
