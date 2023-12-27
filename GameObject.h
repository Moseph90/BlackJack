#pragma once
#include "Game.h"

class GameObject {
public:
	GameObject(const char* textureSheet, SDL_Renderer* ren, bool isMessage);
	GameObject(const char* textureSheet, SDL_Renderer* ren, SDL_Rect sRect, SDL_Rect dRect);
	SDL_Rect getSRect();
	SDL_Rect getDRect();
	int getDRectX();
	int getDRectY();
	int getDRectW();
	int getDRectH();
	void setDRectX(int x);
	void setDRect(SDL_Rect rect);
	~GameObject();

	void SetPosition(float dx, float dy);
	void setValue(int val);
	int getValue();
	void Update(float dx, float dy, float dw, float dh);
	void Update(float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh);
	void Update(float dw, float dh);
	void Render();

	static const int values[];
private:
	int cardvalue;
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;
};