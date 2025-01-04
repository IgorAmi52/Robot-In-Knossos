#include "labyrinth.hpp"
#include <iostream>

int main() {
    int width, height, items_count;
    
    std::cout << "Enter the width of the labyrinth: ";
    std::cin >> width;
    std::cout << "Enter the height of the labyrinth: ";
    std::cin >> height;
    std::cout << "Enter the number of items in the labyrinth: ";
    std::cin >> items_count;

    std::cout << "\033[2J\033[1;1H"; // Clear the console

    labyrinth::Labyrinth *lab = new labyrinth::Labyrinth(width, height, items_count);
    while (true) {
        lab->print();
        char direction;
        std::cin >> direction;
        lab->move_player(direction);
    }
    delete lab;
}
