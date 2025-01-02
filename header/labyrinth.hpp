#ifndef LABYRINTH_H
#define LABYRINTH_H

#include "items.hpp"

namespace labyrinth {

    char** gen_labyrinth(int width, int height, int item_count);

    class Labyrinth {
    public:
        Labyrinth(int width, int height, int item_count);
        ~Labyrinth();
        void print();
    private:
        char **maze;
        int width;
        int height;
        int player_x;
        int player_y;
        items::Item curr_item;
        int item_longitude;
        int minotaur_x;
        int minotaur_y;
        void gen_labyrinth(int width, int height, int item_count);
    };

}

#endif
