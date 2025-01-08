#include "labyrinth.hpp"
#include <iostream>

int main() {
    int width, height, items_count;
    labyrinth::Labyrinth *lab = nullptr;

    while(lab == nullptr){
        std::cout << "\033[2J\033[1;1H"; // Clear the console
        try {
            std::cout << "Enter the width of the labyrinth: ";
            std::cin >> width;
            if (std::cin.fail()) {
               throw std::invalid_argument("Width must be an integer!");
            }
            std::cout << "Enter the height of the labyrinth: ";
            std::cin >> height;
            if (std::cin.fail()) {

                throw std::invalid_argument("Height must be an integer!");
            }
            std::cout << "Enter the number of items in the labyrinth: ";
            std::cin >> items_count;
            if (std::cin.fail()) {
                throw std::invalid_argument("Items count must be an integer!");
            }
            lab = new labyrinth::Labyrinth(width, height, items_count);
        } catch(const std::exception& e) {
                std::cin.clear(); // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the input
                std::cerr << e.what() << '\n';
        }
    }

    std::cout << "\033[2J\033[1;1H"; // Clear the console

    while (true) {
        lab->print();
        char direction;
        std::cin >> direction;
        lab->move_player(direction);
    }
    delete lab;
}
