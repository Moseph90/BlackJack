#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <vector>
#include <string>

class GameObject;

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }
	static SDL_Event event;

	void getMouseState();
	void playButton();
	void Cards();
	void Text();
	void TextRender();
	void TextPositions();
	void VectorPositions();
	void VectorRender();
	void Chips();
	void ChipsRender();
	void ChipsPosition();
	void MouseUpBet();
	void MouseUpDeal();
	void MouseUpButtons();
	void ResetTriggers();
	void UpdateBetText();
	void UpdateCreditText();
	void UpdateDealerCards();
	void EndGame(bool natural);
	void Shuffle();
	void ResetRound();
	void Ace(int* points);

private:
	std::vector<GameObject> deck;
	std::vector<GameObject> pCards;
	std::vector<GameObject> dCards;
	std::vector<GameObject> betText;
	std::vector<GameObject> creditText;
	int betTextAmount;
	int creditTextAmount = 50000;
	int dealCounter;
	int deckCounter;
	int playerPoints;
	int dealerPoints;

	GameObject* faceDownCard;
	GameObject* faceDownCard2;

	bool isRunning;
	bool firstScene = true;

	SDL_Window* window;
	SDL_Renderer* renderer;

	//Chips
	GameObject* five;
	GameObject* ten;
	GameObject* twentyFive;
	GameObject* fifty;
	GameObject* hundred;
	GameObject* fiveHundred;
	GameObject* thousand;
	GameObject* fiveThousand;
	GameObject* tenThousand;

	//Text Objects
	GameObject* credit;
	GameObject* betAmount;
	GameObject* betMessage;
	GameObject* dealtMessage;
	GameObject* notEnoughMoney;
	GameObject* betBeforeDeal;
	GameObject* bustedMessage;
	GameObject* dealerBusted;
	GameObject* standOffMessage;
	GameObject* youWinMessage;
	GameObject* houseWinsMessage;
	GameObject* playerStandsMessage;

	//Game Triggers
	bool bett = false;
	bool bettM = false;
	bool deal = false;
	bool ddownn = false;
	bool ddowned = false;
	bool notEnough = false;
	bool stood = false;
	bool busted = false;
	bool makeBet = false;
	bool dealerBust = false;
	bool standOff = false;
	bool youWin = false;
	bool houseWins = false;
	bool playerStands = false;
	bool updateDealer = false;
	bool faceUp = false;
	bool dealerAce = false;
	bool playerAce = false;

	//X Coordinates For Card Placement
	int xPos[6] = {300, 360, 420, 480, 540, 600};
	int playerYpos = 400;
	int dealerYpos = 120;

	//Time Management
	Uint32 startTime;
	Uint32 delayTime = 1500;
};
