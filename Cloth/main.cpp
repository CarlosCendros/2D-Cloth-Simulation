#include "Sticks.hpp"
#include <vector>
#include <iomanip>

const int GAME_WIDTH = 900, GAME_HEIGHT = 600;
bool IS_DRAGGING = false;

int main(){
    sf::RenderWindow window(sf::VideoMode(GAME_WIDTH,GAME_HEIGHT),"Cloth Simulation");
    window.setFramerateLimit(60);

    sf::View view(sf::Vector2f(0,0), sf::Vector2f(GAME_WIDTH,GAME_HEIGHT));
    window.setView(view);

    // FPS
    sf::Clock clock;
    sf::Font font;
    font.loadFromFile("path/to/font.ttf");
    sf::Text frameRateText;
    frameRateText.setFont(font);
    frameRateText.setPosition(-GAME_WIDTH*0.5f+10,-GAME_HEIGHT*0.5f+10);
    frameRateText.setCharacterSize(15);
    frameRateText.setFillColor(sf::Color(0,255,0,150));

    // Create a mouse
    Mouse mouse(window);

    // Create Nodes
    int nCols = 150;
    int nRows = 55;
    std::vector<std::vector<Node>> Nodes(nRows,std::vector<Node>(nCols,Node(0.0f, 0.0f,false)));

    for(int i = 0; i < nRows; i++){
        for(int j = 0; j < nCols; j++){
            if(i==0)
                Nodes[i][j].fixed = true;
            Nodes[i][j].pos.x = -GAME_WIDTH*0.4+4.0f*j;
            Nodes[i][j].pos.y = -GAME_HEIGHT*0.4+4.0f*i;
            Nodes[i][j].old_pos = Nodes[i][j].pos;
        }
    }

    // Create rope  
    std::vector<std::vector<Stick>> HSticks(nRows, std::vector<Stick>(nCols, Stick()));
    std::vector<std::vector<Stick>> VSticks(nRows, std::vector<Stick>(nCols,Stick()));

    for(int i = 0; i < nRows; i++){
        for(int j = 0; j < nCols; j++){
            if(j+1<nCols){    
                HSticks[i][j].NodeA = &Nodes[i][j];
                HSticks[i][j].NodeB = &Nodes[i][j+1];
                HSticks[i][j].length = dist(Nodes[i][j],Nodes[i][j+1]);
            }
            if(i+1<nRows){    
                VSticks[i][j].NodeA = &Nodes[i][j];
                VSticks[i][j].NodeB = &Nodes[i+1][j];
                VSticks[i][j].length = dist(Nodes[i][j],Nodes[i+1][j]);
            }
        }
    }
    
    while(window.isOpen()){
        sf::Event event;
        
        sf::Time elapsed = clock.restart();
        float frameRate=1.0f/elapsed.asSeconds();
        std::ostringstream ss;
        ss << std::fixed << std::setprecision(1) << frameRate;
        std::string formattedFrameRate = ss.str();

        // Update the frame rate text
        frameRateText.setString(formattedFrameRate + " FPS");

        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed) window.close();
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
            else if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right){
                sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                IS_DRAGGING = true;
                for(int i = 0; i < nRows; i++){
                    for(int j = 0; j < nCols; j++){
                        if(Nodes[i][j].fixed == false && Nodes[i][j].pos.x > MousePos.x && Nodes[i][j].pos.x < MousePos.x +15 && Nodes[i][j].pos.y > MousePos.y && Nodes[i][j].pos.y < MousePos.y +15)
                            Nodes[i][j].exists = false;
                    }
                }
            }
            else if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right)
            IS_DRAGGING = false;
    
            else if(event.type == sf::Event::MouseMoved && IS_DRAGGING){
                sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                for(int i = 0; i < nRows; i++){
                    for(int j = 0; j < nCols; j++){
                        if(Nodes[i][j].fixed == false && Nodes[i][j].pos.x > MousePos.x && Nodes[i][j].pos.x < MousePos.x +15 && Nodes[i][j].pos.y > MousePos.y && Nodes[i][j].pos.y < MousePos.y +15)
                            Nodes[i][j].exists = false;
                    }
                }
            }
        }

        window.clear(sf::Color::Black);
        // Game Logic
        mouse.update(window);
        for(int i = 0; i < nRows; i++){
            for(int j = 0; j < nCols; j++){
                Nodes[i][j].update(elapsed,mouse);
                Nodes[i][j].render(window);
            }
        }
        for(int i = 0; i < nRows-1; i++){
            for(int j = 0; j < nCols-1; j++){
                HSticks[i][j].render(window);
                VSticks[i][j].render(window);
            }
        }
        window.draw(frameRateText);
        window.display();
    }
}
