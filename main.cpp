#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "planet.h"
#include "player.h"
#include "functions.h"


int main() {
    sf::Vector2f  window_size;

    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    Planet moon(10, window);
    Player player1(window);


    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        window.draw(moon);
        window.draw(player1);//, player1.sf::Transform::rotate(1, 400, 300));
        std::cout<<player1.getPosition().x<<std::endl;
        player1.gravity();
        window.display();
    }
    return 0;
}
