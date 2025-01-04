#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <string>
namespace labyrinth {

    // Generates a labyrinth with the given width, height, and item count.
    char** gen_labyrinth(int width, int height, int item_count);

    class Labyrinth {
    public:
        Labyrinth(int width, int height, int item_count);
        ~Labyrinth();

        // Moves the player in the specified direction.
        void move_player(char direction);

        // Sets the visibility limit for the labyrinth.
        void set_visibility_limit(bool visibility);

        // Sets whether the player has a shield.
        void set_shield(bool shield);

        // Sets whether the player has a sword.
        void set_sword(bool sword);

        // Sets whether the player has a hammer.
        void set_hammer(bool hammer);

        // Prints the current state of the labyrinth to the console.
        void print();

        // Saves the final structure of the labyrinth to a file.
        void save_final_structure(std::string final_result) const;

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

        // Moves the minotaur within the labyrinth.
        void move_minotaur();

        // Removes any items the player has.
        void remove_item();

        // Generates the labyrinth with the given dimensions and item count.
        void gen_labyrinth(int width, int height, int item_count);
    };

}

#endif
