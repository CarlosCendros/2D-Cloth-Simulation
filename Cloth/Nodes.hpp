#ifndef NODES_HPP
#define NODES_HPP

#include <SFML/Graphics.hpp>
#include "Mouse.hpp"

struct Node{
    sf::Vector2f pos;
    sf::Vector2f old_pos;
    sf::Vector2f vel = {0,0};
    sf::Vector2f acc = {0,0};
    sf::CircleShape node;
    float mass = 1.0f;
    bool fixed;
    bool exists;
    
    Node(float posx, float posy, bool fixed){
        pos.x = posx; pos.y = posy;
        old_pos = pos;
        this->fixed = fixed;
        exists = true;

        node.setPosition(pos);
        node.setRadius(5);
        node.setOrigin(5,5);
    }
    void render(sf::RenderWindow& window){
        if(exists){
            node.setPosition(pos);
        }
    }
    void update(sf::Time elapsed, const Mouse& mouse){
        if(!fixed && exists){
            float dt = elapsed.asSeconds();
            apply_force(mouse);
            // Verlet
            vel.x = pos.x - old_pos.x;
            vel.y = pos.y - old_pos.y;

            old_pos.x = pos.x;
            old_pos.y = pos.y;

            pos.x += vel.x + acc.x*dt*dt;
            pos.y += vel.y + acc.y*dt*dt;
            acc = {0,30};
        }
    }
    void apply_force(const Mouse& mouse){
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && exists){
            float d = distance(mouse);
            if(d > 10){
                // Create force
                sf::Vector2f direction = {float(mouse.pos.x - mouse.old_pos.x) , float(mouse.pos.y - mouse.old_pos.y)};
                float inv_d = 1.0f/d;
                float F = 50;
                sf::Vector2f force = F * direction * inv_d;
                // Apply force
                acc += force/mass;
            }
            else{
                // Create force
                sf::Vector2f direction = {float(mouse.pos.x - mouse.old_pos.x) , float(mouse.pos.y - mouse.old_pos.y)};
                float inv_d = 1.0f/50;
                float F = 50;
                sf::Vector2f force = F * direction * inv_d;
                // Apply force
                acc += force/mass;
            }
        }
    }
};

#endif