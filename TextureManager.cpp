#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture, SDL_Renderer* ren) {
	SDL_Surface* tmpSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	return tex;
}
SDL_Texture* TextureManager::LoadTextTexture(const char* message, SDL_Renderer* ren) {
	SDL_Color color = { 255, 255, 255, 255 };
	TTF_Font* font = TTF_OpenFont("images/GameFont.TTF", 24);
	SDL_Surface* sMessage = TTF_RenderText_Solid(font, message, color);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, sMessage);
	SDL_FreeSurface(sMessage);

	return tex;
}