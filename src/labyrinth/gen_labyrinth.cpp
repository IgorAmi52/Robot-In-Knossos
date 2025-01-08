#include <set>
#include <vector>
#include <cstdlib>
#include <ctime>    
#include <iostream>

#include "labyrinth.hpp"
#include "utils.hpp"

/**
 * Adds frontier cells to the list of frontiers.
 * @param frontiers The list of frontier cells.
 * @param x The x position of the current cell.
 * @param y The y position of the current cell.
 * @param width The width of the maze.
 * @param height The height of the maze.
 * @param maze The maze array.
 */
void add_frontiers(std::vector<std::pair<int, int>>& frontiers, int x, int y, int width, int height, char** maze) {
    // Only add cells that are at least 2 steps away and not touching borders
    if (x + 2 <= width - 2 && maze[y][x + 2] == '#') {
        frontiers.push_back(std::make_pair(x + 2, y));
    }
    if (x - 2 >= 1 && maze[y][x - 2] == '#') {
        frontiers.push_back(std::make_pair(x - 2, y));
    }
    if (y - 2 >= 1 && maze[y - 2][x] == '#') {
        frontiers.push_back(std::make_pair(x, y - 2));
    }
    if (y + 2 <= height - 2 && maze[y + 2][x] == '#') {
        frontiers.push_back(std::make_pair(x, y + 2));
    }
}

/**
 * Checks if a cell is a path.
 * @param cell The cell character.
 * @return True if the cell is a path, false otherwise.
 */
bool is_path(char cell) {
    return cell == ' ' || cell == 'R';
}

/**
 * Gets valid positions for placing items and the minotaur.
 * @param maze The maze array.
 * @param width The width of the maze.
 * @param height The height of the maze.
 * @return A vector of valid positions.
 */
std::vector<std::pair<int, int>> get_valid_positions(char** maze, int width, int height) {
    std::vector<std::pair<int, int>> positions;
    for(int y = 1; y < height - 1; y++) {
        for(int x = 1; x < width - 1; x++) {
            if(maze[y][x] == ' ') {
                positions.push_back(std::make_pair(x, y));
            }
        }
    }
    return positions;
}

namespace labyrinth {
    /**
     * Generates the labyrinth with the given dimensions and item count.
     * @param width The width of the labyrinth.
     * @param height The height of the labyrinth.
     * @param items_count The number of items in the labyrinth.
     * @throws std::invalid_argument if width or height is less than 5.
     */
    void Labyrinth::gen_labyrinth(int width, int height, int items_count) {
        if (width < 5 || height < 5) {
            throw std::invalid_argument("Width and height must be at least 5");
        }

        // Initialize maze with walls
        char** maze = new char*[height];
        for (int i = 0; i < height; i++) {
            maze[i] = new char[width];
            for (int j = 0; j < width; j++) {
                maze[i][j] = '#';
            }
        }

        // Create entrance from top only
        int entrance = utils::get_random_int(1, width - 2);
        maze[0][entrance] = 'U';
        maze[1][entrance] = 'R';

        std::vector<std::pair<int, int>> frontier;
        add_frontiers(frontier, entrance, 1, width, height, maze);

        std::set<std::pair<int, int>> visited;
        visited.insert(std::make_pair(entrance, 1));

        // Keep track of bottom row paths
        std::vector<int> bottom_paths;

        while (!frontier.empty()) {
            int random_front = utils::get_random_int(0, frontier.size() - 1);
            std::pair<int, int> current = frontier[random_front];
            frontier.erase(frontier.begin() + random_front);

            int x = current.first;
            int y = current.second;

            if (visited.find(current) != visited.end()) {
                continue;
            }

            // Check neighbors (avoiding borders)
            std::vector<std::pair<int, int>> neighbors;
            if (x - 2 >= 1 && is_path(maze[y][x - 2])) neighbors.push_back(std::make_pair(x - 2, y));
            if (x + 2 <= width - 2 && is_path(maze[y][x + 2])) neighbors.push_back(std::make_pair(x + 2, y));
            if (y - 2 >= 1 && is_path(maze[y - 2][x])) neighbors.push_back(std::make_pair(x, y - 2));
            if (y + 2 <= height - 2 && is_path(maze[y + 2][x])) neighbors.push_back(std::make_pair(x, y + 2));

            if (!neighbors.empty()) {
                int random_neighbor = utils::get_random_int(0, neighbors.size() - 1);
                std::pair<int, int> neighbor = neighbors[random_neighbor];

                maze[y][x] = ' ';
                maze[(y + neighbor.second) / 2][(x + neighbor.first) / 2] = ' ';
                
                // If we're creating a path in the second-to-last row, track it
                if (y == height - 2) {
                    bottom_paths.push_back(x);
                }
                
                visited.insert(current);
                add_frontiers(frontier, x, y, width, height, maze);
            }
        }

        // If no paths reach the bottom, create one
        if (bottom_paths.empty()) {
            int x = utils::get_random_int(1, width - 2);
            maze[height - 2][x] = ' ';
            bottom_paths.push_back(x);
        }

        // Choose a random path from the bottom paths for the exit
        int exit_index = utils::get_random_int(0, bottom_paths.size() - 1);
        maze[height - 1][bottom_paths[exit_index]] = 'I';

        std::vector<std::pair<int, int>> valid_positions = get_valid_positions(maze, width, height);
        
        // Place items
        for(int i = 0; i < items_count && !valid_positions.empty(); i++) {
            int pos_index = utils::get_random_int(0, valid_positions.size() - 1);
            int x = valid_positions[pos_index].first;
            int y = valid_positions[pos_index].second;
            maze[y][x] = 'P';  // Mark items with 'I'
            valid_positions.erase(valid_positions.begin() + pos_index);
        }

        // Place minotaur if we have valid positions left
        if(!valid_positions.empty()) {
            int pos_index = utils::get_random_int(0, valid_positions.size() - 1);
            int x = valid_positions[pos_index].first;
            int y = valid_positions[pos_index].second;
            maze[y][x] = 'M';  // Mark minotaur with 'M'
            this->minotaur_x = x;
            this->minotaur_y = y;
        }

        this->player_x = entrance;
        this->player_y = 1;
        this->maze = maze;
    }
}