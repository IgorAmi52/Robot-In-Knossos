#include "labyrinth.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <width> <height> <item_count>" << std::endl;
        return 1;
    }

    int width = std::atoi(argv[1]);
    int height = std::atoi(argv[2]);
    int items_count = std::atoi(argv[3]);

    if (width < 15 || height < 15 || items_count < 3) {
        std::cerr << "Width and height must be at least 15, and item count must be at least 3." << std::endl;
        return -1;
    }

    std::cout << "\033[2J\033[1;1H"; // Clear the console

    labyrinth::Labyrinth *lab = new labyrinth::Labyrinth(width, height, items_count);

    while (true) {
        lab->print();
        char direction;
        std::cin >> direction;
        lab->move_player(direction);
    }

    delete lab;
    return 0;
}
