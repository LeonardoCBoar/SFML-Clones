#ifndef VISUAL
#define VISUAL

#include <SFML\Graphics.hpp>
#include <vector>
#include "Board.hpp"

using namespace std;


class Visual{

    public:
        sf::RenderWindow window;
        Board *board;
        Visual(Board *board);

        int sqr_s;
        vector<vector<sf::RectangleShape>> g_board;
        void initialize_g_board();

        const sf::Color colors[7]{
            sf::Color::White,
            sf::Color::Blue,
            sf::Color::Cyan,
            sf::Color::Green,
            sf::Color::Magenta,
            sf::Color::Red,
            sf::Color::Yellow,

        };
        void update_square_color(sf::RectangleShape* square, int value);
        
        
        void update();


};





#endif