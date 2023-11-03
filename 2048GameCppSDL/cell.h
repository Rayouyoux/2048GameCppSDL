#pragma once

#include "GameObject.h"

#include "SDL_pixels.h"

class Window;

class Cell : public GameObject 
{

public:

    Cell();
    Cell(int x, int y, int width, int height, SDL_Color color, Window* window);

    int getValue() const;
    void setValue(int value);
    SDL_Texture* getImage();
    void setImage(SDL_Texture* img);

private:

    int value;
    SDL_Texture* image;

};