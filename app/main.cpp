// src/main.cpp

#include "Game.h"

int main() {
    // Define the size of each cell in pixels
    const int CELL_SIZE = 10;  // Adjust as needed for your screen size

    // Define the number of cells horizontally and vertically
    const int WIDTH = 100;     // Number of cells along the x-axis
    const int HEIGHT = 80;     // Number of cells along the y-axis

    // Create a Game object with specified dimensions
    Game game(WIDTH, HEIGHT, CELL_SIZE);

    // Initialize the grid with a random state
    game.initializeRandom();

    // Run the game loop
    game.run();

    return 0;
}
