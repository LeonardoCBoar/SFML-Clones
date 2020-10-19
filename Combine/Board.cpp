#include "Board.hpp"
#include <cstdio>



Board::Board(int size)
    : size(size),board(size+2, vector<int>(size,0) )
    {}
void Board::print(){

    for(int y=0;y<board.size();y++){

        for(int x=0;x<board[y].size();x++){

            printf("%i",board[y][x]);
        }
        printf("\n");
    }

}

void Board::new_block(){
    //Generates the new block in the upper right corner
    for(int i=0;i<2;i++){
        board[i][size-1] = 1;
        new_block_pos[i] = sf::Vector2i(size-1,i);
    }

}

void Board::move_new_block(Move_Dir dir){

    //If it's a horizontal movement, the two blocks are moved 
    for (int i = 1; i >=0; i--)
    {   
        //Gets the old position as "pos" and its value
        sf::Vector2i pos = new_block_pos[i];
        int old_value = board[pos.y][pos.x];

        //Erases the value in the old position
        board[pos.y][pos.x] = 0;

        //Moves the block accordingly with the direction and updates pos variable
        //printf("Hor Old pos:X-%i Y-%i\n",pos.x,pos.y);
        pos.x +=dir;
        if(pos.x<0)pos.x=0;
        if(pos.x>=size)pos.x = size-1;
        //printf("Hor New pos:X-%i Y-%i\n",pos.x,pos.y);


        //Updates the board with the changes
        board[pos.y][pos.x] = old_value;
        new_block_pos[i] = pos;
    }
        
}



void Board::apply_gravity(){

    vector<int> shall_erase;

    //If it's a horizontal movement, the two blocks are moved 
    //printf("Size %i\n",fallable.size());
    for (int i = 0; i < fallable.size() ; i++)
    {   
        //Gets the old position as "pos" and its value
        sf::Vector2i pos = fallable[i];



        //printf("Working with the element at X%i Y%i\n",fallable[i].x,fallable[i].y);
        int old_value = board[pos.y][pos.x];

        //Erases the value in the old position
        board[pos.y][pos.x] = 0;

        //Moves the block respecting the borders
        //printf("Ver Old pos:X-%i Y-%i\n",pos.x,pos.y);
        pos.y+=1;
        //printf("Ver New pos:X-%i Y-%i\n",pos.x,pos.y);
        

        //Updates the board with the changes
        board[pos.y][pos.x] = old_value;
        fallable[i] = pos;


        //If the blocks reachs the bottom, it's removed
        if(pos.y+1>=board.size()){
            shall_erase.push_back(i);


            continue;
        }

        //Checks if there is any empty space below the block, meaning that's possible that it will fall
        bool space_below = false;
        for(int f=pos.y+1;f<board.size();f++){
            if(board[f][pos.x] == 0){
                space_below = true;
                break;
            }
        }

        if(!space_below){
            shall_erase.push_back(i);
        }

    }



    vector<sf::Vector2i> cascade;

    //Removes the blocks from fallable and adds to the combinable
    //outside of the loop in order to don't mess with the index
    


    for(int index = 0;index<shall_erase.size();index++){

        combinable.push_back(fallable[index]);
 
        fallable.erase(fallable.begin()+index);
        printf("Erasing and adding combinable\n");
        printf("Combinable size%i\n",combinable.size());
        
    }



    
    
        
}

void Board::check_combinations(){

    //Storages the positions of connected squares while searching
    vector<vector<sf::Vector2i>> combinations; 

    //Storages the position of connected squares after the search
    vector<vector<sf::Vector2i>> full_combinations;


    //Copy the combinables positions to the combinations vector
    for (int i = 0; i < combinable.size(); i++)
    {
        combinations.push_back(vector<sf::Vector2i>{combinable[i]});
    }

    //Searchs for consecutive blocks
    while(combinations.size()!=0){
        for (int i = 0; i < combinations[i].size(); i++)
        {   


            bool has_changed = false; //Used to verify if there were any changes from the last 
            //iteration, if not, this combination is considered full

            vector<sf::Vector2i> new_combs;//Storages the changes

            //Checks the blocks in every four sides of the blocks looking for equal values
            //It's redundant, the same blocks are checked multiple times in the loop
            //THIS NEEDS IMPROVEMENT IN THE FUTURE
            for(sf::Vector2i pos:combinations[i]){
                

                //Ignore blocks outside the bouns
                if(pos.y<0) continue;
                if(pos.x<0) continue;
                if(pos.y>board.size()-1)continue;
                if(pos.x>board[0].size()-1)continue;

                //Ignore Blank blocks
                if(board[pos.y][pos.x]==0) continue;


                //Above block check
                if(pos.y > 0            && board[pos.y][pos.x]==board[pos.y-1][pos.x])
                {
                    //Avoid duplicated positions
                    if(find(combinations[i].begin(), combinations[i].end(), sf::Vector2i(pos.x,pos.y-1)) == combinations[i].end() ){
                        new_combs.push_back(sf::Vector2i(pos.x,pos.y-1));
                        has_changed = true;
                    }
                    

                }
                //Left block check
                if(pos.x > 0            && board[pos.y][pos.x]==board[pos.y][pos.x-1])
                {
                    //Avoid duplicated positions
                    if(find(combinations[i].begin(), combinations[i].end(), sf::Vector2i(pos.x-1,pos.y)) == combinations[i].end() ){
                        new_combs.push_back(sf::Vector2i(pos.x-1,pos.y));
                        has_changed = true;
                    }
                }
                
                //Below block check
                if(pos.y < board.size()-1 && board[pos.y][pos.x]==board[pos.y+1][pos.x])
                {
                    //Avoid duplicated positions
                    if(find(combinations[i].begin(), combinations[i].end(), sf::Vector2i(pos.x,pos.y+1)) == combinations[i].end() ){
                        new_combs.push_back(sf::Vector2i(pos.x,pos.y+1));
                        has_changed = true;

                    }
                }

                //Right block check
                if(pos.x  <board[i].size()-1 && board[pos.y][pos.x]==board[pos.y][pos.x+1])
                {
                    //Avoid duplicated positions
                    if(find(combinations[i].begin(), combinations[i].end(), sf::Vector2i(pos.x+1,pos.y)) == combinations[i].end() ){
                        new_combs.push_back(sf::Vector2i(pos.x+1,pos.y));
                        has_changed = true;

                    }
                }



            }


            //If there were no additions to the combination, the search is finished
            //And the amount of elements is counted
            if(!has_changed){
                

                if(combinations[i].size()>=3){
                    printf("Founded a 3 combination!!!\n");
                    full_combinations.push_back(combinations[i]);
                    
                    //Removes other combinations that uses the blocks from the founded combination
                    vector<vector<sf::Vector2i>> rremove;
                    for(vector<sf::Vector2i> comb:combinations){
                        for(sf::Vector2i used_block:combinations[i]){
                           if( find(comb.begin(), comb.end(), used_block) != comb.end() ){
                               rremove.push_back(comb);
                           }
                        }
                    }
                    for(int r=0;r<rremove.size();r++){
                        combinations.erase(remove(combinations.begin(), combinations.end(), rremove[r]), combinations.end());
                    }


                }
                else{
                    printf("Not founded a combination\n");
                    combinations.erase(combinations.begin() + i);
                }

            }
            //If there were additions, they're applied
            else{
                for (int c = 0; c < new_combs.size(); c++)
                {
                    combinations[i].push_back(new_combs[c]);
                }
                
            }

        
        }


    }

    //At last, cleans combinable
    combinable.clear();

    merge_combinations(&full_combinations);


    




}

void Board::merge_combinations(vector<vector<sf::Vector2i>> *combinations){

    

for (int c = 0; c < combinations->size(); c++)
{   
    vector<sf::Vector2i> comb = (*combinations)[c];

    //Get the value of the new block
    int value = (board[comb[0].y][comb[0].x] +1)%7;

    //Reset the value of the old blocks and start the fallable and combineable operations
    for(sf::Vector2i pos:comb){
        board[pos.y][pos.x] = 0;


        //Combineable to all side blocks
        combinable.push_back(sf::Vector2i(pos.x,pos.y+1));
        combinable.push_back(sf::Vector2i(pos.x,pos.y-1));
        combinable.push_back(sf::Vector2i(pos.x+1,pos.y));
        combinable.push_back(sf::Vector2i(pos.x-1,pos.y));
        

    }


    //Set the value of the new block
    board[comb[0].y][comb[0].x] = value;

    //Adds the block to the fallable if valid and to combineable
    bool may_fall = false;
    for(int y = comb[0].y;y<board.size();y++){
        if(board[y][comb[0].x] ==0){
            fallable.push_back(comb[0]);
            //Falleable to up block

            if(board[comb[0].y-1][comb[0].x] !=0){
                fallable.push_back(sf::Vector2i(comb[0].y-1,comb[0].x));
                }
            break;
        }
    }
}

    





}