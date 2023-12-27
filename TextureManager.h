#pragma once
#include "Game.h"
#include "SDL_ttf.h"

class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);
	static SDL_Texture* LoadTextTexture(const char* fileName, SDL_Renderer* ren);
};
