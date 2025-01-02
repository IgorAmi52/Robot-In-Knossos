#ifndef UTILS_H
#define UTILS_H

#include <vector>
namespace utils {
    int get_random_int(int min, int max);
    int get_random_bool();
    char get_random_direction(const std::vector<char>& avoid_directions);
}

#endif