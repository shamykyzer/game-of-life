// src/Game.cpp

#include "Game.h"
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

// Define the heights of the UI areas
const int TOP_UI_HEIGHT = 30;      // Height for the generation and speed display at the top
const int BOTTOM_UI_HEIGHT = 30;   // Height for the controls guide at the bottom

// Constructor initializes the game parameters and sets up the window
Game::Game(int width, int height, int cellSize)
    : width(width), height(height), cellSize(cellSize), generation(0),
      grid(height, std::vector<uint8_t>(width, 0)),
      isPaused(false), updateInterval(100), lastUpdateTime(0.0) {

    // Calculate window dimensions, adding space for top and bottom UI areas
    int windowWidth = width * cellSize;
    int windowHeight = TOP_UI_HEIGHT + (height * cellSize) + BOTTOM_UI_HEIGHT;

    // Initialize the window with the calculated dimensions
    InitWindow(windowWidth, windowHeight, "Conway's Game of Life");

    // Set the target FPS for smooth rendering
    SetTargetFPS(60);
}

// Destructor closes the window when the game ends
Game::~Game() {
    CloseWindow();
}

// Initializes the grid with a random state
void Game::initializeRandom() {
    // Seed the random number generator with the current time
    srand(static_cast<unsigned>(time(nullptr)));

    // Iterate over each cell in the grid
    for (auto& row : grid)
        for (auto& cell : row)
            cell = rand() % 2;  // Assign a random value of 0 or 1
}

// Starts the main game loop
void Game::run() {
    while (!WindowShouldClose()) {  // Loop until the window is closed
        handleInput();  // Process user input

        // Get the current time in milliseconds
        double currentTime = GetTime() * 1000.0;

        // Update the grid if the simulation is not paused and enough time has elapsed
        if (!isPaused && (currentTime - lastUpdateTime >= updateInterval)) {
            update();               // Update the grid to the next generation
            lastUpdateTime = currentTime;  // Update the last update time
        }

        // Begin drawing the frame
        BeginDrawing();
        ClearBackground(BLACK);  // Clear the screen with a black background
        draw();                  // Render the grid and UI elements
        EndDrawing();            // Finish drawing the frame
    }
}

// Handles user input for controlling the simulation
void Game::handleInput() {
    // Pause or resume the simulation when the Spacebar is pressed
    if (IsKeyPressed(KEY_SPACE)) {
        isPaused = !isPaused;
    }

    // Increase the simulation speed when the Up Arrow is pressed
    if (IsKeyPressed(KEY_UP)) {
        if (updateInterval > 10) updateInterval -= 10;  // Decrease the interval
    }

    // Decrease the simulation speed when the Down Arrow is pressed
    if (IsKeyPressed(KEY_DOWN)) {
        if (updateInterval < 1000) updateInterval += 10;  // Increase the interval
    }

    // Reset the simulation when the 'R' key is pressed
    if (IsKeyPressed(KEY_R)) {
        reset();
    }

    // Toggle the state of a cell when the left mouse button is clicked
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        // Get the mouse position
        Vector2 mousePosition = GetMousePosition();
        int x = mousePosition.x / cellSize;

        // Adjust for the top UI height
        int topTextY = 5;
        int textHeight = 20;
        float cellStartY = topTextY + textHeight + 5;

        // Calculate the cell coordinates based on the mouse position
        int y = (mousePosition.y - cellStartY) / cellSize;

        // Check if the coordinates are within the grid boundaries
        if (x >= 0 && x < width && y >= 0 && y < height) {
            grid[y][x] = !grid[y][x];  // Toggle the cell state
        }
    }
}

// Resets the simulation to a new random state
void Game::reset() {
    generation = 0;    // Reset the generation count
    initializeRandom();  // Reinitialize the grid with a random state
}

// Updates the grid to the next generation based on the Game of Life rules
void Game::update() {
    // Create a copy of the current grid to store the next generation
    std::vector<std::vector<uint8_t>> newGrid = grid;

    // Iterate over each cell in the grid
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int neighbors = countNeighbors(x, y);  // Count alive neighbors

            // Apply the Game of Life rules
            if (grid[y][x]) {
                // Any live cell with two or three live neighbors survives
                newGrid[y][x] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
            } else {
                // Any dead cell with exactly three live neighbors becomes a live cell
                newGrid[y][x] = (neighbors == 3) ? 1 : 0;
            }
        }
    }

    grid = newGrid;  // Update the grid with the new generation
    ++generation;    // Increment the generation count
}

// Counts the number of alive neighbors for a given cell
int Game::countNeighbors(int x, int y) const {
    int count = 0;

    // Iterate over the 3x3 neighborhood around the cell
    for (int j = -1; j <= 1; ++j) {
        for (int i = -1; i <= 1; ++i) {
            // Skip the cell itself
            if (i == 0 && j == 0)
                continue;

            int nx = x + i;  // Neighbor's x-coordinate
            int ny = y + j;  // Neighbor's y-coordinate

            // Check if the neighbor is within the grid boundaries
            if (nx >= 0 && nx < width && ny >= 0 && ny < height)
                count += grid[ny][nx];  // Add the neighbor's state to the count
        }
    }

    return count;  // Return the total count of alive neighbors
}

// Renders the grid and UI elements on the screen
void Game::draw() const {
    // 1. Draw the top UI (Generation and Speed)
    int topTextY = 5;  // Small margin from the top
    int textHeight = 20;  // Font size is 20

    // Draw generation and speed indicators
    DrawText(TextFormat("Generation: %d", generation), 10, topTextY, textHeight, GREEN);
    DrawText(TextFormat("Speed: %.1f updates/sec", 1000.0f / updateInterval), 500, topTextY, textHeight, GREEN);

    // Calculate the starting Y position for drawing cells
    float cellStartY = topTextY + textHeight + 5;  // 5 pixels margin below text

    // Adjusted border thickness
    float borderThickness = 0.5f;

    // 2. Draw the cells
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Define the rectangle representing the cell
            Rectangle cell = {
                static_cast<float>(x * cellSize),
                cellStartY + static_cast<float>(y * cellSize),
                static_cast<float>(cellSize),
                static_cast<float>(cellSize)
            };

            if (grid[y][x]) {
                // Draw a filled rectangle for alive cells
                DrawRectangleRec(cell, WHITE);
            } else {
                // Draw an outline for dead cells with thinner lines
                DrawRectangleLinesEx(cell, borderThickness, DARKGRAY);
            }
        }
    }

    // 3. Draw the bottom UI (Controls Guide)
    int bottomTextY = TOP_UI_HEIGHT + (height * cellSize) + 5;  // Slight margin from the cells

    // Draw controls instructions
    DrawText("Controls: SPACE - Pause/Resume | UP/DOWN - Speed | R - Reset | CLICK - Toggle Cell",
             10, bottomTextY, 20, GREEN);
}
