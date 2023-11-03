#include "cell.h"
#include "grid.h"
#include "gameObject.h"
#include "window.h"
#include <SDL.h>

Cell::Cell() : value(0) {}

Cell::Cell(int x, int y, int width, int height, SDL_Color color, Window* window) : GameObject(x, y, width, height, color, window)
{
    this->value = 0;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

int Cell::getValue() const {
    return value;
}

void Cell::setValue(int value) {
    this->value = value;
}

SDL_Texture* Cell::getImage() {
    return image;
}

void Cell::setImage(SDL_Texture* img) {
    image = img;
}


