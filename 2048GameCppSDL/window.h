#pragma once
#include <SDL.h>
#include <vector>

using namespace std;

class GameObject;

class Window
{
public:

	Window();

	void display();

	void close();

	vector<GameObject*> gameObjects;

	SDL_Window* window;

	SDL_Renderer* renderer;

	~Window();

private:

};
