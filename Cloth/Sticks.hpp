#ifndef STICKS_HPP
#define STICKS_HPP

#include <SFML/Graphics.hpp>
#include "Nodes.hpp"

struct Stick{
    Node* NodeA;
    Node* NodeB;
    sf::VertexArray rope;
    float length;
    bool exists;
    
    Stick() : NodeA(nullptr), NodeB(nullptr), length(0.0f) {
        rope.setPrimitiveType(sf::Lines);
        rope.resize(2);
        exists = true;

        rope[0].position = sf::Vector2f(0.0f, 0.0f);
        rope[1].position = sf::Vector2f(0.0f, 0.0f);
        rope[0].color = sf::Color(0, 255, 0, 100);
        rope[1].color = sf::Color(0, 255, 0, 100);
    }
    Stick(Node* NodeA, Node* NodeB, float length){
        this->NodeA = NodeA; this->NodeB = NodeB;
        this->length = length;

        rope.setPrimitiveType(sf::Lines);
        rope.resize(2);
        
        rope[0].position = NodeA->pos;
        rope[1].position = NodeB->pos;

        rope[0].color = sf::Color(0,255,0,100);
        rope[1].color = sf::Color(0,255,0,100);
    }
    void render(sf::RenderWindow& window){
        if(exists){
            update();
            
            rope[0].position = NodeA->pos;
            rope[1].position = NodeB->pos;
        }
        window.draw(rope);
    }
    void update(){
        float dx = NodeB->pos.x - NodeA->pos.x;
        float dy = NodeB->pos.y - NodeA->pos.y;
        
        float dist = sqrt(dx*dx + dy*dy);
        if(dist > 1.5f*length){
            float diff = length - dist;
            float percent = (diff/dist)/2;

            float offset_x = dx * percent;
            float offset_y = dy * percent;
            if(NodeA->fixed == false){
                NodeA->pos.x -= 0.4f*offset_x;
                NodeA->pos.y -= 0.4f*offset_y;

                NodeB->pos.x += 0.4f*offset_x;
                NodeB->pos.y += 0.4f*offset_y;
            }
            else if(NodeA->fixed){
                NodeB->pos.x+=2*offset_x;
                NodeB->pos.y+=2*offset_y;
            }
        }
        if((NodeA->exists == false || NodeB->exists == false) && exists == true){
                exists = false;
                rope[0].color = sf::Color::Black;
                rope[1].color = sf::Color::Black;
        }  
    }
};
float dist(Node A, Node B){
    return std::sqrt(pow(A.pos.x-B.pos.x,2)+pow(A.pos.y-B.pos.y,2));
}

#endif