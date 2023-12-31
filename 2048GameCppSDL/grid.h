#pragma once

#include <vector>
#include <random>
#include <SDL.h>

#include "cell.h"
#include "window.h"

class Grid {

public:

    Grid(Window* window);

    void initializeGrid(std::mt19937& rng, Window* window);

    SDL_Texture* selectTexture(int value, Window* window);

    void printGrid();

    void displayGrid(Window* window);

    int movement(int dir);

    void newNumber(std::mt19937& rng);

    int checkWin();

    int checkLose();

    ~Grid();

private:

    int verticalMovement(int dir);

    int horizontalMovement(int dir);

    int gridSize;
    Cell** gridArray;

};