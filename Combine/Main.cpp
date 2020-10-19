#include <vector>
#include "Board.hpp"
#include "Visual.hpp"
#include "Input.hpp"

using  std::vector;

int main(){




    //Game systems objects
    Board board(10);
    Visual visual(&board);
    Input_Handler input_handler(&visual.window,&board);

    int frame_count = 0;
    while (visual.window.isOpen())
    {   
        //Input Handling
        input_handler.handle_input();
        
        //Physical Update
        if(frame_count==6){
            frame_count = 0;
            board.apply_gravity();
        }
        frame_count++;


        //Graphical frame update
        visual.update();
    }
    


    
    
};