//********Here we set up the window and frame rate using SDL functions. All of the SDL specific functions are named SDL_someVariable********//

#include "SDL.h"
#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {
	const int FPS = 120;
	const int frameDelay = 1000 / FPS;
	
	Uint32 frameStart;
	int frameTime;

	game = new Game();

	//game->init() uses SDL functions and variables to create a window and initialize SDL properties.
	game->init("BlackJack", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, false);

	//This is where all of the updates happen, they begin here and are nested from here upward through the program
	while (game->running()) {
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
	}

	game->clean();

	return 0;
}