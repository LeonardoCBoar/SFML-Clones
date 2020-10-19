#include "Input.hpp"




Input_Handler::Input_Handler(sf::RenderWindow* window,Board* board)
    :window{window},
     board(board)
     {}

void Input_Handler::handle_input(){

    sf::Event input;

    while(window->pollEvent(input)){



        //Close Window/Esc 
        if((input.type == sf::Event::EventType::Closed)||(input.type==sf::Event::EventType::KeyPressed && input.key.code==sf::Keyboard::Escape)){
            this->window->close();
            return;
        }


        if(input.type == sf::Event::KeyPressed){

            switch (input.key.code)
            {
            //New Block Movement
            case sf::Keyboard::A:
                printf("A\n");
                board->move_new_block(Board::Move_Dir::LEFT);
                break;
            case sf::Keyboard::D:
                printf("D\n");
                board->move_new_block(Board::Move_Dir::RIGHT);
                break;
            case sf::Keyboard::S:
                printf("S\n");
                
                //Adds the blocks to the fallable list, from the bottom to top
                if(board->fallable.size() == 0){
                    printf("Adding elements\n");
                    board->fallable.push_back(board->new_block_pos[1]);
                    board->fallable.push_back(board->new_block_pos[0]);
                }
                board->apply_gravity();
                break;
            
            
            //New Block Creation
            case sf::Keyboard::Space:
                printf("Space\n");
                board->new_block();
                break;
            case sf::Keyboard::Enter:
                printf("Enter\n");
                board->check_combinations();
                break;

            default:
                break;
            }

        }
    }

    }