#include <iostream>
#include <thread> // Add this include for sleep functionality
#include <chrono> // Add this include for timing
#include <fstream> // Add this include for file operations

#include "labyrinth.hpp"
#include "items.hpp"
#include "utils.hpp"

/**
 * Gets valid moves for the minotaur.
 * @param maze The maze array.
 * @param pos_x The x position of the minotaur.
 * @param pos_y The y position of the minotaur.
 * @return A vector of valid move positions.
 */
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
    /**
     * Constructs a Labyrinth object with the given dimensions and item count.
     * @param width The width of the labyrinth.
     * @param height The height of the labyrinth.
     * @param items_count The number of items in the labyrinth.
     * @throws std::invalid_argument if width or height is less than 15, or if items_count is less than 3.
     */
    Labyrinth::Labyrinth(int width, int height, int items_count){
        if(width < 15 || height < 15){
            throw std::invalid_argument("Width and height must be at least 15");
        }
        if (items_count < 3) {
            throw std::invalid_argument("Items count must be at least 3");
        }
        this->width = width;
        this->height = height;

        auto start = std::chrono::high_resolution_clock::now(); // Start timing
        gen_labyrinth(width, height, items_count);
        auto end = std::chrono::high_resolution_clock::now(); // End timing

        std::chrono::duration<double> duration = end - start;
        std::cout << "Labyrinth generated in " << duration.count() << " seconds." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000)); 
    }

    /**
     * Destructor for the Labyrinth object. Cleans up allocated memory.
     */
    Labyrinth::~Labyrinth(){
        save_final_structure(""); 
        for(int i = 0; i < this->height; i++){
            delete[] maze[i];
        }
        delete[] maze;
    }

    /**
     * Sets the visibility limit for the labyrinth.
     * @param visibility True to enable visibility limit, false to disable.
     */
    void Labyrinth::set_visibility_limit(bool visibility){
        this->visibility_limit = visibility;
    }

    /**
     * Sets whether the player has a shield.
     * @param shield True if the player has a shield, false otherwise.
     */
    void Labyrinth::set_shield(bool shield){
        this->have_shield = shield;
    }

    /**
     * Sets whether the player has a sword.
     * @param sword True if the player has a sword, false otherwise.
     */
    void Labyrinth::set_sword(bool sword){
        this->have_sword = sword;
    }

    /**
     * Sets whether the player has a hammer.
     * @param hammer True if the player has a hammer, false otherwise.
     */
    void Labyrinth::set_hammer(bool hammer){
        this->have_hammer = hammer;
    }

    /**
     * Removes any items the player has.
     */
    void Labyrinth::remove_item(){
        this->have_shield = false;
        this->have_sword = false;
        this->have_hammer = false;
    }

    /**
     * Prints the current state of the labyrinth to the console.
     */
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

    /**
     * Moves the minotaur within the labyrinth.
     */
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
                save_final_structure("Minotaur killed the player.");
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
                save_final_structure("Minotaur killed the player.");
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

    /**
     * Moves the player in the specified direction.
     * @param direction The direction to move the player ('w', 'a', 's', 'd').
     */
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
                save_final_structure("Player quit the game.");
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
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); //wait for half a second
            move_minotaur();
        }
    }

    /**
     * Saves the final structure of the labyrinth to a file.
     * @param final_result A string describing the final result of the game.
     */
    void Labyrinth::save_final_structure(std::string final_result) const {
        std::ofstream file("final_maze_structure.txt");
        if (file.is_open()) {
            for (int i = 0; i < this->height; i++) {
                for (int j = 0; j < this->width; j++) {
                    file << maze[i][j];
                }
                file << std::endl;
            }
            file << final_result;
            file.close();
        } else {
            std::cerr << "Unable to open file to save maze structure." << std::endl;
        }
    }
}

