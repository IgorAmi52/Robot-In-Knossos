# Robot In Knossos

A C++ implementation of a maze escape game inspired by the ancient Greek legend of the Labyrinth of Knossos. Navigate a robot through a dynamically generated maze while avoiding the Minotaur and collecting power-ups.

## Table of Contents
- [Overview](#overview)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Maze Generation](#maze-generation)
- [Game Rules](#game-rules)
  - [Maze Elements](#maze-elements)
  - [Movement](#movement)
  - [Special Items](#special-items)
- [Command Line Arguments](#command-line-arguments)
- [Controls](#controls)
- [Technical Implementation](#technical-implementation)
- [Project Structure](#project-structure)
- [Output Files](#output-files)
- [Known Limitations](#known-limitations)

## Overview
This project implements an interactive maze game where players control a robot trying to escape from the Labyrinth of Knossos while avoiding the Minotaur. The maze is dynamically generated with various interactive elements and power-ups that affect gameplay.

## Prerequisites
- C++ compiler with C++11 support or higher
- CMake 3.10 or higher

## Installation
1. Clone the repository
```bash
git clone https://github.com/yourusername/Robot-In-Knossos.git
cd Robot-In-Knossos
```

2. Build the project using CMake
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Maze Generation
The maze is generated using Prim's algorithm, modified for maze creation:

1. Initialize the maze with walls everywhere
2. Start from a random cell and mark it as part of the maze
3. Add all neighboring walls of the current cell to a wall list
4. While there are walls in the wall list:
   - Pick a random wall from the list
   - If only one of the cells adjacent to the wall is visited:
     - Break down the wall
     - Add the unvisited cell to the maze
     - Add the neighboring walls of the new cell to the wall list
   - Remove the wall from the wall list

This ensures:
- A perfect maze with no loops
- All areas are accessible
- Random but solvable layout
- Proper path width for gameplay

After maze generation, game elements (Robot, Minotaur, items) are placed ensuring path accessibility.

## Game Rules

### Maze Elements
- `#` - Walls
- `U` - Entrance (randomly placed on the first row)
- `R` - Robot (starts one row below the entrance)
- `I` - Exit (randomly placed on the last row)
- `.` - Path (empty space)
- `M` - Minotaur (randomly placed)
- `P` - Power-up items

### Movement
- The robot can move in four directions (up, down, left, right)
- The Minotaur moves randomly each turn
- If the Minotaur gets adjacent to the robot, it will chase and attempt to catch it
- Neither the robot nor the Minotaur can pass through walls
- The Minotaur can destroy power-ups by stepping on them

### Special Items
All special effects last for 3 turns:
1. "War Fog" - Reduces visibility to a 3x3 matrix
2. "Sword" - Allows the robot to destroy the Minotaur
3. "Shield" - Provides protection from the Minotaur
4. "Hammer" - Enables wall-breaking ability

## Command Line Arguments
The program requires three arguments:
1. Width of the maze (must be larger than 15)
2. Height of the maze (must be larger than 15)
3. Number of power-up items (must be greater than 3)

Example:
```bash
./labyrinth 20 25 5
```

## Controls
- Movement keys are customizable
- 'Q' to quit the game

## Technical Implementation
- Written in C++ using object-oriented principles
- Maze generation algorithm implemented in a separate library
- Dynamic memory management for maze creation
- Inheritance used for power-ups and special effects
- Separate classes for game flow and file handling

## Project Structure
- `src/` - Source files
- `header/` - Header files


## Output Files
Upon game completion (either by winning, losing, or quitting), the program generates an output file containing:
- Final maze state
- Game outcome
- Performance metrics


## Known Limitations
- Maze dimensions must be greater than 15x15
- Minimum of 3 power-up items required
- Terminal must support ASCII characters for proper display

For more detailed information about the implementation and testing results, please refer to the documentation folder.