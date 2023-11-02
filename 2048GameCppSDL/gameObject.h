#pragma once
#include <SDL.h>

class Window;

class GameObject
{
public:
	
	GameObject(int x, int y, int width, int height, SDL_Color color, Window* window);

	void drawRectangle(SDL_Renderer* renderer);

	~GameObject();

	int x;
	int y;

	int width;
	int height;

	SDL_Color color;
};


