#include "gameObject.h"
#include "window.h"

#include <iostream>

class Window;

GameObject::GameObject() {
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	color = { 0, 0, 0, 0 };
}

GameObject::GameObject(int x, int y, int width, int height, SDL_Color color, Window* window) {

	this->x = x;
	this->y = y;

	this->width = width;
	this->height = height;

	this->color = color;

	(*window).gameObjects.push_back(this);

}

void GameObject::drawRectangle(SDL_Renderer* renderer) {

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_Rect rectangle = { x, y, width, height};
	SDL_RenderFillRect(renderer, &rectangle);

}

void GameObject::setPos(int x, int y) {
	this->x = x;
	this->y = y;
}

void GameObject::setSize(int width, int height) {
	this->width = width;
	this->height = height;
}

void GameObject::setColor(SDL_Color color) {
	this->color = color;
}

void GameObject::setWindow(Window* window) {
	this->window = window;
}

GameObject::~GameObject() {
}