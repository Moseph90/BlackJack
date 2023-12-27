#include "GameObject.h"
#include "TextureManager.h"

const int GameObject::values[] = {
	2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 1
};

GameObject::GameObject(const char* textureSheet, SDL_Renderer* ren, bool isMessage) {
	if (isMessage) {
		renderer = ren;
		objTexture = TextureManager::LoadTextTexture(textureSheet, renderer);
	}
	else {
		renderer = ren;
		objTexture = TextureManager::LoadTexture(textureSheet, renderer);
	}
}
GameObject::GameObject(const char* textureSheet, SDL_Renderer* ren, SDL_Rect sRect, SDL_Rect dRect) {
	srcRect = sRect;
	destRect = dRect;
	renderer = ren;
	objTexture = TextureManager::LoadTexture(textureSheet, renderer);
}
GameObject::~GameObject() {}
SDL_Rect GameObject::getSRect() {
	return srcRect;
}
SDL_Rect GameObject::getDRect() {
	return destRect;
}
int GameObject::getDRectX() {
	return destRect.x;
}
int GameObject::getDRectY() {
	return destRect.y;
}
int GameObject::getDRectW() {
	return destRect.w;
}
int GameObject::getDRectH() {
	return destRect.h;
}
void GameObject::setDRectX(int x) {
	destRect.x = x;
}
void GameObject::setDRect(SDL_Rect rect) {
	destRect = rect;
}
void GameObject::setValue(int val) {
	cardvalue = val;
}
int GameObject::getValue() {
	return cardvalue;
}
void GameObject::Update(float dx, float dy, float dw, float dh) {
	destRect.x = dx;
	destRect.y = dy;
	destRect.w = dw;
	destRect.h = dh;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = dw;
	srcRect.h = dh;
}
void GameObject::Update(float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh) {
	srcRect.x = sx;
	srcRect.y = sy;
	srcRect.w = sw;
	srcRect.h = sh;
	destRect.x = dx;
	destRect.y = dy;
	destRect.w = dw;
	destRect.h = dh;
}
void GameObject::Update(float dw, float dh) {
	destRect.w = dw;
	destRect.h = dh;
	destRect.x = 0;
	destRect.y = 0;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = dw;
	srcRect.h = dh;
}
void GameObject::SetPosition(float dx, float dy) {
	destRect.x = dx;
	destRect.y = dy;
	destRect.w = destRect.w;
	srcRect.x = srcRect.x;
	srcRect.y = srcRect.y;
	srcRect.w = srcRect.w;
	srcRect.h = srcRect.h;
}
void GameObject::Render() {
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}