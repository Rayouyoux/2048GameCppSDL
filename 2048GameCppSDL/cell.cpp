#include "cell.h"
#include "grid.h"
#include "gameObject.h"
#include "window.h"

Cell::Cell() : value(0) {}

Cell::Cell(int x, int y, int widht, int height, SDL_Color color, Window* window) : GameObject(x, y, width, height, color, window)
{
    this->value = 0;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->color = color;
}

int Cell::getValue() const {
    return value;
}

void Cell::setValue(int value) {
    this->value = value;
}

void Cell::setPos(int x, int y) {
    this->x = x;
    this->y = y;
}

void Cell::setSize(int width, int height) {
    this->width = width;
    this->height = height;
}

void Cell::setColor(SDL_Color color) {
    this->color = color;
}