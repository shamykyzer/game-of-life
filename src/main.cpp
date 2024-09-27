// src/main.cpp
#include "Game.h"

int main() {
    const int WIDTH = 50;
    const int HEIGHT = 30;
    const int CELL_SIZE = 20;

    Game game(WIDTH, HEIGHT, CELL_SIZE);
    game.initializeRandom();
    game.run();

    return 0;
}
