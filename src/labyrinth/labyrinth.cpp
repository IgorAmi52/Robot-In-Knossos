#include <iostream>
#include <thread> // Add this include for sleep functionality

#include "labyrinth.hpp"
#include "items.hpp"
#include "utils.hpp"

std::vector<std::pair<int, int>> get_valid_moves(char** maze, int pos_x, int pos_y) {
    std::vector<std::pair<int, int>> positions;
    if (maze[pos_y - 1][pos_x] == ' ' || maze[pos_y - 1][pos_x] == 'P') {
        positions.push_back(std::make_pair(pos_x, pos_y - 1));
    }
    if (maze[pos_y + 1][pos_x] == ' ' || maze[pos_y + 1][pos_x] == 'P') {
        positions.push_back(std::make_pair(pos_x, pos_y + 1));
    }
    if (maze[pos_y][pos_x - 1] == ' ' || maze[pos_y][pos_x - 1] == 'P') {
        positions.push_back(std::make_pair(pos_x - 1, pos_y));
    }
    if (maze[pos_y][pos_x + 1] == ' ' || maze[pos_y][pos_x + 1] == 'P') {
        positions.push_back(std::make_pair(pos_x + 1, pos_y));
    }
    return positions;
}
namespace labyrinth{
    Labyrinth::Labyrinth(int width, int height, int items_count){
        this->width = width;
        this->height = height;
        gen_labyrinth(width, height, items_count);
    }
    Labyrinth::~Labyrinth(){
        for(int i = 0; i < this->height; i++){
            delete[] maze[i];
        }
        delete[] maze;
    }
    void Labyrinth::set_visibility_limit(bool visibility){
        this->visibility_limit = visibility;
    }
    void Labyrinth::set_shield(bool shield){
        this->have_shield = shield;
    }
    void Labyrinth::set_sword(bool sword){
        this->have_sword = sword;
    }
    void Labyrinth::set_hammer(bool hammer){
        this->have_hammer = hammer;
    }
    void Labyrinth::remove_item(){
        this->have_shield = false;
        this->have_sword = false;
        this->have_hammer = false;
    }
    void Labyrinth::print(){
        std::cout << "\033[2J\033[1;1H"; // Add this line to clear the console
        for(int i = 0; i < this->height; i++){
            for(int j = 0; j < this->width; j++){
                if(this->visibility_limit){
                    if(std::abs(i - this->player_y) > 3 || std::abs(j - this->player_x) > 3){
                        std::cout << " ";
                        continue;
                    } 
                }
                std::cout << maze[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << this->item_desc << std::endl;
    }
    void Labyrinth::move_minotaur(){
        if (this->minotaur_x == this->player_x && std::abs(this->minotaur_y - this->player_y) == 1){
            if(this->have_shield){
                return;
            }
            else{
                this->maze[this->minotaur_x][this->minotaur_y] = ' ';
                this->maze[this->player_x][this->player_y] = 'M';
                print();
                std::cout << "You died" << std::endl;
                exit(0);
            }
        }
        else if(this->minotaur_y == this->player_y && std::abs(this->minotaur_x - this->player_x) == 1){
            if(this->have_shield){
                return;
            }
            else{
                this->maze[this->minotaur_x][this->minotaur_y] = ' ';
                this->maze[this->player_x][this->player_y] = 'M';
                print();
                std::cout << "You died" << std::endl;
                exit(0);
            }
        }
        //minotaur moves randomly

        std::vector<std::pair<int, int>> valid_moves = get_valid_moves(this->maze, this->minotaur_x, this->minotaur_y);
        int move_index = utils::get_random_int(0, valid_moves.size() - 1);

        this->maze[this->minotaur_y][this->minotaur_x] = ' ';
        this->minotaur_x = valid_moves[move_index].first;
        this->minotaur_y = valid_moves[move_index].second;
        this->maze[this->minotaur_y][this->minotaur_x] = 'M';
    }
    void Labyrinth::move_player(char direction){
        int new_x = this->player_x;
        int new_y = this->player_y;
        switch(direction){
            case 'w':
                new_y--;
                break;
            case 's':
                new_y++;
                break;
            case 'a':
                new_x--;
                break;
            case 'd':
                new_x++;
                break;
            case 'q':
                exit(0);
            default:
                return;
        }

        if(this->have_hammer && this->maze[new_y][new_x] == '#'){ // If player has hammer and goes over a wall
            if (new_y != this->player_y){
                if(new_y > this->player_y)new_y++;
                else new_y--;  
            }
            else{
                if(new_x > this->player_x)new_x++;
                else new_x--;
            }
        }
        if(new_x < 0 || new_x >= this->width || new_y < 0 || new_y >= this->height){
            return;
        }
        this->maze[player_y][player_x] = ' ';
        
        if(this->maze[new_y][new_x] == 'M'){
            if(this->have_sword){
                this->minotaur_alive = false;
            }
            else{
                std::cout << "You died" << std::endl;
                exit(0);
            }
        }    
        if(this->maze[new_y][new_x] == 'P'){
            items::Item* item = items::get_random_item();
            item->use(*this);
            this->item_desc = item->get_description();
            delete item;
            this->item_longitude = 4;
        }
        this->maze[new_y][new_x] = 'R';
        this->player_x = new_x;
        this->player_y = new_y;

        if (this->maze[new_y+1][new_x] == 'I') {
            print();
            std::cout << "You won!" << std::endl;
            exit(0);
        }
        this->item_longitude--;
        if(this->item_longitude == 0){
            this->item_desc = "";
            remove_item();
        }
        if(this->minotaur_alive){
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Add this line to wait for one second
            move_minotaur();
        }
 
        
    }
}

