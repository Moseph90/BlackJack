/*GameObject uses this class to help it build objects. These return SDL_Textures which it gets from the const char* argument. These are the 
images/GameFont.TTF and the file path of the image for the buttons, chips, cards etc. It returns the right textures for GameObject to 
manipulate.*/

#pragma once
#include "Game.h"
#include "SDL_ttf.h"

class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);
	static SDL_Texture* LoadTextTexture(const char* fileName, SDL_Renderer* ren);
};

											//******GO TO GAME OBJECT.H*******//