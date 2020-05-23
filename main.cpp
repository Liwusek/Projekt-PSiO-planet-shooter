#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "planet.h"
#include "player.h"
#include "functions.h"


int main() {
    int rotation = 10;


    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    std::vector<std::unique_ptr<sf::Drawable>> walls;

    Planet moon(10, rotation, window);
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
        player1.move1();
        window.display();
    }
    return 0;
}
