#include <SFML\Graphics.hpp>
#include "Visual.hpp"


Visual::Visual(Board *board)
    :window(sf::VideoMode(400,500),"Combine"),board(board),
     sqr_s(30),
     
     /*Creates a 2D vector that storages the squares, it's higher in the vertical in order to 
       show the squares of the next piece*/
     g_board(board->size+2, vector<sf::RectangleShape>
     (board->size,sf::RectangleShape(sf::Vector2f(sqr_s,sqr_s))) )
    
    {
        this->window.setFramerateLimit(60);
        initialize_g_board();
    }

void Visual::initialize_g_board(){
    //Basic setup of all squares of the game

    for(int y=0;y<g_board.size();y++){
        
        for(int x=0;x<g_board[0].size();x++){
            
            g_board[y][x].setPosition(sf::Vector2f(50+x*sqr_s,50+y*sqr_s));
            g_board[y][x].setFillColor(sf::Color::White);
            g_board[y][x].setOutlineColor(sf::Color::Black);
            g_board[y][x].setOutlineThickness(1);

        }
    }

}

void Visual::update_square_color(sf::RectangleShape* square, int value){
    //Matches the color of the square by his block value

    value = value%10;

    square->setFillColor(colors[value]);


}


void Visual::update(){
    //Updates the game screen every frame

    window.clear(sf::Color::Black);

    for(int y=0;y<g_board.size();y++){
        
        for(int x=0;x<g_board[0].size();x++){
            //Update the color of the square that will be rendered
            update_square_color(&g_board[y][x],board->board[y][x]);
            
            //De facto renders the square in the window
            window.draw(g_board[y][x]);
        }
    }

    

    window.display();
}
