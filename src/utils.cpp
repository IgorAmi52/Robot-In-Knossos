#include "utils.hpp"
#include <random>
#include <vector>
#include <cstdlib>  // For rand()
#include <ctime>    // For time()

namespace utils{
    int get_random_int(int min, int max){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }
    int get_random_bool(){
        return get_random_int(0, 1);
    }

    // Utility to get a random direction, avoiding specified directions
    char get_random_direction(const std::vector<char>& avoid_directions) {
        // Define all possible directions
        std::vector<char> directions = {'U', 'D', 'L', 'R'};

        // Remove the directions to avoid
        for (char avoid : avoid_directions) {
            directions.erase(std::remove(directions.begin(), directions.end(), avoid), directions.end());
        }

        // If there are no directions left, return a default direction ('U')
        if (directions.empty()) {
            return 'U';
        }

        // Seed the random number generator if it's not already seeded
        std::srand(std::time(0));

        // Pick a random direction from the remaining directions
        int random_index = std::rand() % directions.size();

        return directions[random_index];
    }

}
