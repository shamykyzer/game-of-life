// src/Game.cpp
#include "Game.h"
#include <cstdlib>
#include <ctime>

Game::Game(int width, int height, int cellSize)
    : width(width), height(height), cellSize(cellSize), generation(0), grid(height, std::vector<uint8_t>(width, 0)) {
    InitWindow(width * cellSize, height * cellSize, "Conway's Game of Life");
    SetTargetFPS(10); // Adjust the FPS as needed
}

Game::~Game() {
    CloseWindow();
}

void Game::initializeRandom() {
    srand(static_cast<unsigned>(time(nullptr)));
    for (auto& row : grid)
        for (auto& cell : row)
            cell = rand() % 2;
}

void Game::run() {
    while (!WindowShouldClose()) {
        update();

        BeginDrawing();
        ClearBackground(BLACK);
        draw();
        EndDrawing();
    }
}

void Game::update() {
    std::vector<std::vector<uint8_t>> newGrid = grid;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int neighbors = countNeighbors(x, y);
            if (grid[y][x]) {
                newGrid[y][x] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
            } else {
                newGrid[y][x] = (neighbors == 3) ? 1 : 0;
            }
        }
    }
    grid = newGrid;
    ++generation;
}

int Game::countNeighbors(int x, int y) const {
    int count = 0;
    for (int j = -1; j <= 1; ++j) {
        for (int i = -1; i <= 1; ++i) {
            if (i == 0 && j == 0)
                continue;
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < width && ny >= 0 && ny < height)
                count += grid[ny][nx];
        }
    }
    return count;
}

void Game::draw() const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (grid[y][x]) {
                DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, WHITE);
            } else {
                DrawRectangleLines(x * cellSize, y * cellSize, cellSize, cellSize, DARKGRAY);
            }
        }
    }
    DrawText(TextFormat("Generation: %d", generation), 10, 10, 20, GREEN);
}
