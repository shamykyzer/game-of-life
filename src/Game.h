// src/Game.h

#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <vector>
#include <cstdint>

// The Game class encapsulates the Game of Life simulation
class Game {
public:
    // Constructor to initialize the game with specified width, height, and cell size
    Game(int width, int height, int cellSize);

    // Destructor to clean up resources
    ~Game();

    // Initializes the grid with a random state
    void initializeRandom();

    // Starts the main game loop
    void run();

private:
    // Grid dimensions and cell size
    int width;
    int height;
    int cellSize;

    // Current generation count
    int generation;

    // 2D grid representing the state of each cell (alive or dead)
    std::vector<std::vector<uint8_t>> grid;

    // Simulation control variables
    bool isPaused;          // Indicates if the simulation is paused
    int updateInterval;     // Time between updates in milliseconds
    double lastUpdateTime;  // Time when the last update occurred

    // Updates the grid to the next generation
    void update();

    // Counts the number of alive neighbors for a given cell
    int countNeighbors(int x, int y) const;

    // Renders the grid and UI elements on the screen
    void draw() const;

    // Handles user input for controls
    void handleInput();

    // Resets the simulation to a new random state
    void reset();
};

#endif // GAME_H
