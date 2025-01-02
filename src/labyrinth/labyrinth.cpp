#include "labyrinth.hpp"
#include <iostream>

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
    void Labyrinth::print(){
        for(int i = 0; i < this->height; i++){
            for(int j = 0; j < this->width; j++){
                std::cout << maze[i][j];
            }
            std::cout << std::endl;
        }
    }
}

