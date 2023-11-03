#include "grid.h"
#include "window.h"
#include "gameObject.h"

#include <iostream>
#include <random>
#include <SDL.h>

#undef main
int main() {

	std::mt19937 rng(std::random_device{}());

	Window* window = new Window();
	Grid gameGrid(window);

	gameGrid.initializeGrid(rng, window);
	int isRunning = 1;
	int move = -1;

	SDL_Event event;
	SDL_bool quit = SDL_FALSE;

	gameGrid.displayGrid(window);
	window->display();
	while (isRunning) {
		while (SDL_PollEvent(&event)) {

			move = -1;

			if (event.type == SDL_QUIT) {
				quit = SDL_TRUE;
				delete window;
			}

			else if (event.type == SDL_KEYDOWN)
			{

				if (event.key.keysym.sym == SDLK_UP) {
					move = 2;
				}
				else if (event.key.keysym.sym == SDLK_DOWN) {
					move = 3;
				}
				else if (event.key.keysym.sym == SDLK_LEFT) {
					move = 0;
				}
				else if (event.key.keysym.sym == SDLK_RIGHT) {
					move = 1;
				}

				int isMove = gameGrid.movement(move);

				if (isMove) {
					gameGrid.newNumber(rng);
				}

				if (gameGrid.checkWin() != 0) {
					std::cout << "You win!" << std::endl;
					isRunning = 0;
					window->close();
				}

				else if (gameGrid.checkLose() != 0) {
					std::cout << "You lose!" << std::endl;
					isRunning = 0;
					window->close();
				}

				gameGrid.displayGrid(window);
				window->display();
				
			}
		}
	}

	window->close();
	return 0;

}