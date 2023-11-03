#include "grid.h"
#include "gameObject.h"
#include "window.h"
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <map>
#include <string>
#include <SDL.h>


/*
PUBLIC METHODS
*/

// Constructor
Grid::Grid(Window* window) {
    gridSize = 4;
    gridArray = new Cell * [4];
    for (int i = 0; i < 4; i++) {
        gridArray[i] = new Cell[4];
    }
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            gridArray[i][j].setPos(20+220*i, 20+220*j);
            gridArray[i][j].setSize(200, 200);
            gridArray[i][j].setWindow(window);
            (*window).gameObjects.push_back(&gridArray[i][j]);
        }
    }
}

// Destructor
Grid::~Grid() {
    for (int i = 0; i < gridSize; i++) {
        delete[] gridArray[i];
    }
    delete[] gridArray;
}

// Initializes a game grid
void Grid::initializeGrid(std::mt19937& rng, Window* window) {
    SDL_Surface* surface0 = SDL_LoadBMP("Img/0.bmp");
    if (!surface0) {
        std::cerr << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture0 = SDL_CreateTextureFromSurface(window->renderer, surface0);
    if (!texture0) {
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface0);
        return;
    }


    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            gridArray[i][j].setImage(texture0);
        }
    }

    // Now initialize your grid with images
    newNumber(rng);
    newNumber(rng);
}

SDL_Texture* Grid::selectTexture(int value, Window* window) {SDL_Surface* surface0 = SDL_LoadBMP("Img/0.bmp");
    SDL_Surface* surface2 = SDL_LoadBMP("Img/2.bmp");
    SDL_Surface* surface4 = SDL_LoadBMP("Img/4.bmp");
    SDL_Surface* surface8 = SDL_LoadBMP("Img/8.bmp");
    SDL_Surface* surface16 = SDL_LoadBMP("Img/16.bmp");
    SDL_Surface* surface32 = SDL_LoadBMP("Img/32.bmp");
    SDL_Surface* surface64 = SDL_LoadBMP("Img/64.bmp");
    SDL_Surface* surface128 = SDL_LoadBMP("Img/128.bmp");
    SDL_Surface* surface256 = SDL_LoadBMP("Img/256.bmp");
    SDL_Surface* surface512 = SDL_LoadBMP("Img/512.bmp");
    SDL_Surface* surface1024 = SDL_LoadBMP("Img/1024.bmp");
    SDL_Surface* surface2048 = SDL_LoadBMP("Img/2048.bmp");

    SDL_Texture* texture0 = SDL_CreateTextureFromSurface(window->renderer, surface0);
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(window->renderer, surface2);
    SDL_Texture* texture4 = SDL_CreateTextureFromSurface(window->renderer, surface4);
    SDL_Texture* texture8 = SDL_CreateTextureFromSurface(window->renderer, surface8);
    SDL_Texture* texture16 = SDL_CreateTextureFromSurface(window->renderer, surface16);
    SDL_Texture* texture32 = SDL_CreateTextureFromSurface(window->renderer, surface32);
    SDL_Texture* texture64 = SDL_CreateTextureFromSurface(window->renderer, surface64);
    SDL_Texture* texture128 = SDL_CreateTextureFromSurface(window->renderer, surface128);
    SDL_Texture* texture256 = SDL_CreateTextureFromSurface(window->renderer, surface256);
    SDL_Texture* texture512 = SDL_CreateTextureFromSurface(window->renderer, surface512);
    SDL_Texture* texture1024 = SDL_CreateTextureFromSurface(window->renderer, surface1024);
    SDL_Texture* texture2048 = SDL_CreateTextureFromSurface(window->renderer, surface2048);
    SDL_Texture* texture;

    switch (value) {
    case 2:
        texture = texture2;  // Light gray background
        break;
    case 4:
        texture = texture4;  // Light gray background
        break;
    case 8:
        texture = texture8;  // Light gray background
        break;
    case 16:
        texture = texture16;  // Light gray background
        break;
    case 32:
        texture = texture32;  // Light gray background
        break;
    case 64:
        texture = texture64;  // Light gray background
        break;
    case 128:
        texture = texture128;  // Light gray background
        break;
    case 256:
        texture = texture256;  // Light gray background
        break;
    case 512:
        texture = texture512;  // Light gray background
        break;
    case 1024:
        texture = texture1024;  // Light gray background
        break;
    case 2048:
        texture = texture2048;  // Light gray background
        break;
    default:
        texture = texture0;  // Light gray background
    }

    return texture;
}

void Grid::printGrid() {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            int value = gridArray[i][j].getValue();
            std::cout << value;
        }
        std::cout << std::endl;
    }
    std::cout << "-----------" << std::endl;
}

void Grid::displayGrid(Window* window) {
    SDL_Surface* surfaceGridBackground = SDL_LoadBMP("Img/gridBackground.bmp");
    SDL_Texture* textureGridBackground = SDL_CreateTextureFromSurface(window->renderer, surfaceGridBackground);
    SDL_Rect backRect;
    backRect.x = 10;
    backRect.y = 10;
    backRect.w = 1000;
    backRect.h = 1000;
    SDL_RenderCopy(window->renderer, textureGridBackground, NULL, NULL);
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            gridArray[i][j].setImage(selectTexture(gridArray[i][j].getValue(), window));
            SDL_Texture* tileTexture = gridArray[i][j].getImage(); 
            if (tileTexture) {
                SDL_Rect destRect;
                destRect.x = 490 + 235 * i;
                destRect.y = 70 + 235 * j;
                destRect.w = 210;
                destRect.h = 210;
                SDL_RenderCopy(window->renderer, tileTexture, NULL, &destRect);
                SDL_DestroyTexture(tileTexture);
            }
        }
    }
    SDL_DestroyTexture(textureGridBackground);

}

// Choses which movement to execute based on the chosen direction
int Grid::movement(int dir) {
    return dir <= 1 ? verticalMovement(dir) : horizontalMovement(dir);
}

// Generates a new random number in a random available position in the grid
void Grid::newNumber(std::mt19937& rng) {

    std::uniform_int_distribution<int> isFour(0, 9);
    int placeFour = isFour(rng);

    std::vector<std::pair<int, int>> emptyCells;

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (gridArray[i][j].getValue() == 0) {
                emptyCells.push_back(std::make_pair(i, j));
            }
        }
    }

    if (!emptyCells.empty()) {
        std::uniform_int_distribution<std::size_t> dist(0, emptyCells.size() - 1);
        std::size_t randomIndex = dist(rng);

        std::pair<int, int> randomCoordinates = emptyCells[randomIndex];

        gridArray[randomCoordinates.first][randomCoordinates.second].setValue(placeFour == 9 ? 4 : 2);
    }
}

// Verifies if the grid containes a Cell with 2048 Value
int Grid::checkWin() {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (gridArray[i][j].getValue() == 2048) {
                return 1;
            }
        }
    }
    return 0;
}

// Checks if no movements are possible
int Grid::checkLose() {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 1; j < gridSize; j++) {
            if (gridArray[i][j].getValue() == gridArray[i][j - 1].getValue()) {
                return 0;
            }
            if (gridArray[j][i].getValue() == gridArray[j - 1][i].getValue()) {
                return 0;
            }

        }
    }
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (gridArray[i][j].getValue() == 0) {
                return 0;
            }
        }
    }
    return 1;
}


/*
PRIVATE METHODS
*/


// Vertical movement and merging
int Grid::verticalMovement(int dir) {
    int k;
    int m;
    int t;
    int isMove = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 1; j < gridSize; j++) {
            t = dir == 0 ? j : -j + (gridSize - 1);
            k = dir == 0 ? 1 : -1;
            m = k;
            if (gridArray[t][i].getValue() != 0) {
                while (gridArray[t - k][i].getValue() == 0) {
                    gridArray[t - k][i].setValue(gridArray[t - k + m][i].getValue());
                    gridArray[t - k + m][i].setValue(0);
                    isMove = 1;
                    k = dir == 0 ? k + 1 : k - 1;
                    if (t - k < 0 || t - k >= gridSize) {
                        break;
                    }
                }
                if (t - k >= 0 && t - k < gridSize) {
                    if (gridArray[t - k][i].getValue() == gridArray[t - k + m][i].getValue()) {
                        gridArray[t - k][i].setValue((gridArray[t - k][i].getValue()) * 2);
                        gridArray[t - k + m][i].setValue(0);
                        isMove = 1;
                    }
                }
            }
        }
    }
    return isMove;
}

// Horizontal movement and merging
int Grid::horizontalMovement(int dir) {
    int k;
    int m;
    int t;
    int isMove = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 1; j < gridSize; j++) {
            t = dir == 2 ? j : -j + (gridSize - 1);
            k = dir == 2 ? 1 : -1;
            m = k;
            if (gridArray[i][t].getValue() != 0) {
                while (gridArray[i][t - k].getValue() == 0) {
                    gridArray[i][t - k].setValue(gridArray[i][t - k + m].getValue());
                    gridArray[i][t - k + m].setValue(0);
                    isMove = 1;
                    k = dir == 2 ? k + 1 : k - 1;
                    if (t - k < 0 || t - k >= gridSize) {
                        break;
                    }
                }
                if (t - k >= 0 && t - k < gridSize) {
                    if (gridArray[i][t - k].getValue() == gridArray[i][t - k + m].getValue()) {
                        gridArray[i][t - k].setValue((gridArray[i][t - k].getValue()) * 2);
                        gridArray[i][t - k + m].setValue(0);
                        isMove = 1;
                    }
                }
            }
        }
    }
    return isMove;
}