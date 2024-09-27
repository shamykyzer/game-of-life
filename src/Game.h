// src/Game.h
#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <vector>
#include <cstdint> // For uint8_t

class Game {
public:
    Game(int width, int height, int cellSize);
    ~Game();
    void initializeRandom();
    void run();

private:
    int width;
    int height;
    int cellSize;
    int generation;
    std::vector<std::vector<uint8_t>> grid; // Changed to uint8_t

    void update();
    int countNeighbors(int x, int y) const;
    void draw() const;
};

#endif // GAME_H
