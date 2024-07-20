#pragma once
#include "Game.h"

class GameObject {
public:
	GameObject(const char* textureSheet, SDL_Renderer* ren, bool isMessage);					//This creates text using TextureManager.h
	GameObject(const char* textureSheet, SDL_Renderer* ren, SDL_Rect sRect, SDL_Rect dRect);	//This creates images using TextureManager.h
	
	SDL_Rect getSRect();		//Size and location of the invisible rectangle in the png file that will get grabbed and made into an object
	SDL_Rect getDRect();

	int getDRectX();
	int getDRectY();			//All of these deal with location and size of the images in the actual game. It's useful to have these
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

	/*This object(SDL_Rect) contains.x.y.w and .h for coordinates, width and height.srcRect (Source Rect) is for deciding which pixels in the 
	image file you would like to extract. srcRect.x is the left side or the rectangle, srcRect.y is the top of it, srcRect.w is the width of 
	that triangle and srcRect.h is height. You then extract the pixels inside of that rectangle. destRect is for "Destination Rect", it is the 
	location of the image in the actual game window. It has the same extentions and it draws the same type rectangle, but I use it for
	location. These are set and then passed into the SDL_RenderCopy() function which takes SDL_Rect arguments and renders based on that
	information*/
	SDL_Rect srcRect, destRect;

	SDL_Renderer* renderer;			//SDL require a renderer object to be able to render images
};

									//******THERE'S MORE INFORMATION IN THE MAIN SOURCE FILE******