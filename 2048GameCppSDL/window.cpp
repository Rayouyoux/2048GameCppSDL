#include "window.h"
#include "gameObject.h"

#include <SDL.h>

#include <iostream>

Window::Window() {

    if (0 != SDL_Init(SDL_INIT_EVERYTHING))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        close();
    }

    window = SDL_CreateWindow("2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        480, 480, SDL_WINDOW_SHOWN);

    if (NULL == window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        close();
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (NULL == renderer)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        close();
    }

    SDL_RaiseWindow(window);
    SDL_Color background = { 187,173,160,255 };
    GameObject* screen = new GameObject(0, 0, 480, 480, background, this);

}

void Window::display() {
    SDL_RenderClear(renderer);
    for (int i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->drawRectangle(renderer);
    }
    SDL_RenderPresent(renderer);
}


void Window::close() {

    if (NULL != window)
        SDL_DestroyWindow(window);
    if (NULL != renderer)
        SDL_DestroyRenderer(renderer);
    SDL_Quit();

}

Window::~Window() {
    close();
}