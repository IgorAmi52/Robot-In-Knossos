 #include "labyrinth.hpp"
#include <iostream>

int main() {

    labyrinth::Labyrinth lab = labyrinth::Labyrinth(15, 10, 5);
    while (true) {
        lab.print();
        char direction;
        std::cin >> direction;
        lab.move_player(direction);
        }
}
