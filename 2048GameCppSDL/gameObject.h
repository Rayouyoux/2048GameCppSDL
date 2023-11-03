#pragma once
#include <SDL.h>

class Window;

class GameObject
{
public:
	
	GameObject();
	GameObject(int x, int y, int width, int height, SDL_Color color, Window* window);

	void drawRectangle(SDL_Renderer* renderer);
	void setPos(int x, int y);
	void setSize(int width, int height);
	void setColor(SDL_Color color);
	void setWindow(Window* window);

	~GameObject();

	int x;
	int y;

	int width;
	int height;

	SDL_Color color;
	Window* window;
};


