#ifndef INPUT
#define INPUT

#include <SFML\Graphics.hpp>
#include "Board.hpp"



class Input_Handler{

    sf::RenderWindow* window;
    Board *board;

    public:
        Input_Handler(sf::RenderWindow* window,Board* board);
        void handle_input();

};



#endif