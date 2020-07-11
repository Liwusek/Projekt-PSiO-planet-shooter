#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <SFML/Graphics.hpp>
#include <memory>

class Background : public sf::RectangleShape
{
        public:
            Background();
            Background(sf::Vector2f size, sf::Vector2f texture_size, std::string texture_name);
            void repeate(float x, float y = 1.0);
        private:
            sf::Texture texture_;
            sf::Vector2f size_;
            sf::Vector2f texture_size;
        };

#endif // BACKGROUND_H
