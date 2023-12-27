#include "Game.h"
#include "GameObject.h"
#include "TextureManager.h"

//First Scene
GameObject* logo;
GameObject* bg;
GameObject* button;

//Second Scene BackGround
GameObject* bg2;

//Second Scene Buttons
GameObject* hit;
GameObject* stand;
GameObject* dDown;

//Second Scene Chips

SDL_Event Game::event;

Game::Game() {}
Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags{ 0 };
	if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialized..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) std::cout << "Window Created..." << std::endl;

		renderer = SDL_CreateRenderer(window, -1, 0);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		if (renderer) std::cout << "Renderer Created..." << std::endl;
		isRunning = true;
	}
	else isRunning = false;
	
	TTF_Init();
	if (TTF_Init() < 0) std::cout << "TTF Error: " << TTF_GetError() << std::endl;

	Cards();
	Text();
	Chips();
	Shuffle();
	startTime = SDL_GetTicks();

	bg = new GameObject("images/BG-1080.png", renderer, false);
	logo = new GameObject("images/LOGO-1080.png", renderer, false);
	button = new GameObject("images/BUTTONS-1080.png", renderer, false);
	bg2 = new GameObject("images/TABLE-1080.png", renderer, false);
	hit = new GameObject("images/BUTTONS-1080.png", renderer, false);
	stand = new GameObject("images/BUTTONS-1080.png", renderer, false);
	dDown = new GameObject("images/BUTTONS-1080.png", renderer, false);
}
void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	if (firstScene) {
		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEBUTTONUP:
			playButton();
		default:
			break;
		}
	}
	else {
		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEBUTTONUP:
			if (bett && !deal) {
				MouseUpBet();
				std::cout << "Bett is true, mouse up working" << std::endl;
			}
			if (!deal) {
				MouseUpDeal();
				std::cout << "Deal is false, mouse up working" << std::endl;
			}
			if (deal) {
				MouseUpButtons();
			}
			break;
		}
	}
}
void Game::update() {
	handleEvents();
	bg->Update(1024, 768);
	//getMouseState();
	if (firstScene) {
		logo->Update(53, 205, 918, 357);
		button->Update(0, 0, 123.5, 54, 455, 600, 123.5, 54);
	}
	else {
		bg2->Update(1024, 658);
		hit->Update(123.5, 0, 123.5, 54, 50, 50, 123.5, 54);
		stand->Update(247, 0, 123.5, 54, 50, 150, 123.5, 54);
		dDown->Update(494, 0, 123.5, 54, 50, 250, 123.5, 54);
		faceDownCard->SetPosition(900, 50);
		if (stood && dealerAce) Ace(&dealerPoints);
		UpdateBetText();
		UpdateCreditText();
		TextPositions();
		ChipsPosition();
		VectorPositions();
		if (updateDealer) UpdateDealerCards();
	}
}
void Game::render() {
	SDL_RenderClear(renderer);
	bg->Render();
	if (firstScene) {
		logo->Render();
		button->Render();
	}
	else {
		bg2->Render();
		hit->Render();
		stand->Render();
		dDown->Render();
		faceDownCard->Render();
		//if (!faceUp && dCards.size() > 0) 
		TextRender();
		ChipsRender();
		VectorRender();
	}
	SDL_RenderPresent(renderer);
}
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();
	std::cout << "Game Cleaned..." << std::endl;
}