#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <string>
namespace labyrinth {

    char** gen_labyrinth(int width, int height, int item_count);

    class Labyrinth {
    public:
        Labyrinth(int width, int height, int item_count);
        ~Labyrinth();
        void move_player(char direction);
        void set_visibility_limit(bool visibility);
        void set_shield(bool shield);
        void set_sword(bool sword);
        void set_hammer(bool hammer);
        void print();
    private:
        char **maze;
        int width;
        int height;
        int player_x;
        int player_y; 
        int item_longitude;
        std::string item_desc = "";
        bool visibility_limit = false;
        bool have_shield = false;
        bool have_sword = false;
        bool have_hammer = false;
        bool minotaur_alive = true;
        int minotaur_x;
        int minotaur_y;
        void move_minotaur();
        void remove_item();
        void gen_labyrinth(int width, int height, int item_count);
    };

}

#endif
