#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

struct Mouse{
    sf::Vector2i pos;
    sf::Vector2i old_pos;

    Mouse(sf::RenderWindow& window){
        pos = sf::Mouse::getPosition(window);
        old_pos = pos;
    }
    void update(sf::RenderWindow& window){
        old_pos = pos;
        pos = sf::Mouse::getPosition(window);
    }
};
float distance(Mouse mouse){
    return std::sqrt(pow(mouse.pos.x - mouse.old_pos.x , 2) + pow(mouse.pos.y - mouse.old_pos.y , 2));
}

#endif