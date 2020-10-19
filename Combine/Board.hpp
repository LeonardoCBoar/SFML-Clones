#ifndef BOARD
#define BOARD

#include <vector>
#include <SFML/Graphics.hpp>
#include <algorithm>


using std::vector;
using std::find;
using std::remove;

class Board{

    public:
        int size;
        Board(int size);

        void new_block();
        sf::Vector2i new_block_pos[2]{};

        //Enum that shows the possible movements of the new block
        enum Move_Dir{
            FALL = 2,
            LEFT = -1,
            RIGHT = 1
        };
        void move_new_block(Move_Dir dir);

        vector<sf::Vector2i> fallable;
        void apply_gravity();

        vector<sf::Vector2i> combinable;
        void check_combinations();
        void merge_combinations(vector<vector<sf::Vector2i>> *combinations);

        void print();

    vector<vector<int>> board;


};



#endif