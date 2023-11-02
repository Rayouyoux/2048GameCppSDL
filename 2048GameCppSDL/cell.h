#pragma once

#include "GameObject.h"

#include "SDL_pixels.h"

class Window;

class Cell : public GameObject 
{

public:

    Cell();
    Cell(int x, int y, int widht, int height, SDL_Color color, Window* window);

    int getValue() const;
    void setValue(int value);
    void setPos(int x, int y);
    void setSize(int width, int height);
    void setColor(SDL_Color color);

private:

    int value;

};