//#include "bonus.h"


//Bonus::bonus(const std::vector<std::unique_ptr<sf::Drawable>> &things):sf::RectangleShape()
//{
//Platform *platform;
//do{
//int index = rand() % things.size();
//platform = dynamic_cast<Platform *>(things[index].get());
//}while (platform == nullptr);
//setSize(sf::Vector2f(size_,size_));
//setPosition(sf::Vector2f(platform->getPosition().x + platform->get_size().x/2, platform->getPosition().y + platform->get_size().y + size_ + hight));
//}

//void Bonus::bonus_generator(sf::Clock clock, std::vector<std::unique_ptr<sf::Drawable>> &things)
//{
//    if(clock.getElapsedTime().asSeconds()>30){
//        std::unique_ptr<Bonus> bonus = std::make_unique<Bonus>(std::vector<std::unique_ptr<sf::Drawable>> things);
////        clock.restart();
//    }
//}
