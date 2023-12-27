#include "Game.h"
#include "GameObject.h"

void Game::getMouseState() {
	int mouseX, mouseY;
	Uint32 mosueState = SDL_GetMouseState(&mouseX, &mouseY);
	std::cout << "Mouse Position.x = " << mouseX << std::endl;
	std::cout << "Mouse Position.y = " << mouseY << std::endl;
}
void Game::playButton() {
	int mouseX, mouseY;
	Uint32 mosueState = SDL_GetMouseState(&mouseX, &mouseY);
	if (mouseX > 454 && mouseX < 579 && mouseY > 599 && mouseY < 655) {
		firstScene = false;
		bettM = true;
		bett = true;
	}
}
void Game::Text() {
	betMessage = new GameObject("Place Your Bet, Click The Deck To Deal Each Card", renderer, true);
	dealtMessage = new GameObject("Now Choose An Option From The Left", renderer, true);
	betAmount = new GameObject("Current Bet: ", renderer, true);
	credit = new GameObject("Total Credit: ", renderer, true);
	notEnoughMoney = new GameObject("You Don't Have Enough Credit", renderer, true);
	betBeforeDeal = new GameObject("Please Bet Before Dealing", renderer, true);
	bustedMessage = new GameObject("You're Busted, Make Another Bet", renderer, true);
	dealerBusted = new GameObject("Dealer Is Busted, Make Another Bet", renderer, true);
	standOffMessage = new GameObject("Stand Off, Make Another Bet", renderer, true);
	youWinMessage = new GameObject("You Win, Make Another Bet", renderer, true);
	houseWinsMessage = new GameObject("The House Wins, Make Another Bet", renderer, true);
	playerStandsMessage = new GameObject("Player Stands, Dealer's Turn", renderer, true);
}
void Game::TextRender() {
	if (bettM) betMessage->Render();
	if (deal) dealtMessage->Render();
	if (notEnough) notEnoughMoney->Render();
	if (busted) bustedMessage->Render();
	if (makeBet) betBeforeDeal->Render();
	if (dealerBust) dealerBusted->Render();
	if (standOff) standOffMessage->Render();
	if (youWin) youWinMessage->Render();
	if (houseWins) houseWinsMessage->Render();
	if (playerStands) playerStandsMessage->Render();
	betAmount->Render();
	credit->Render();
	betText[0].Render();
	creditText[0].Render();
}
void Game::TextPositions() {
	betMessage->Update(232, 40, 550, 50);
	dealtMessage->Update(232, 40, 550, 50);
	betBeforeDeal->Update(232, 40, 550, 50);
	bustedMessage->Update(232, 40, 550, 50);
	dealerBusted->Update(232, 40, 550, 50);
	standOffMessage->Update(232, 40, 550, 50);
	youWinMessage->Update(232, 40, 550, 50);
	houseWinsMessage->Update(232, 40, 550, 50);
	playerStandsMessage->Update(232, 40, 550, 50);
	betAmount->Update(700, 300, 200, 30);
	credit->Update(700, 350, 200, 30);
	notEnoughMoney->Update(232, 40, 550, 50);
	creditText[0].Update(creditText[0].getDRectX(), creditText[0].getDRectY(), creditText[0].getDRectW(), creditText[0].getDRectH());
	betText[0].Update(betText[0].getDRectX(), betText[0].getDRectY(), betText[0].getDRectW(), betText[0].getDRectH());
}
void Game::VectorPositions() {
	if (!dCards.empty() && faceUp)
		for (int i = 0; i < dCards.size(); i++) dCards[i].SetPosition(xPos[i], dealerYpos);
	if (!dCards.empty() && !faceUp) {
		dCards[0].SetPosition(xPos[0], dealerYpos);
		faceDownCard2->SetPosition(xPos[1], dealerYpos);
	}
	if (!pCards.empty())
		for (int i = 0; i < pCards.size(); i++) pCards[i].SetPosition(xPos[i], playerYpos);
}
void Game::VectorRender() {
	if (!dCards.empty() && faceUp)
		for (int i = 0; i < dCards.size(); i++) dCards[i].Render();
	if (!dCards.empty() && !faceUp) {
		dCards[0].Render();
		if (dCards.size() > 1) faceDownCard2->Render();
	}
	if (!pCards.empty()) 
		for (int i = 0; i < pCards.size(); i++) pCards[i].Render();
}
void Game::Cards() {
	int counter{ 0 };
	int every13{ 0 };
	for (int row = 0; row < 6; row++) {
		for (int column = 0; column < 9; column++) {
			SDL_Rect tempSrc;
			SDL_Rect tempD;
			tempSrc.x = column * 112.5;
			tempSrc.y = row * 159.5;
			tempSrc.w = 112.5;
			tempSrc.h = 159.5;
			tempD.x = 0;
			tempD.y = 0;
			tempD.w = 112.5;
			tempD.h = 159.5;
			if (every13 > 12) every13 = 0;
			if (counter > 1) {
				GameObject card("images/CARDS-1080.png", renderer, tempSrc, tempD);
				card.setValue(GameObject::values[every13]);
				deck.push_back(card); 
				every13++;
			}
			counter++;
		}
	}
	SDL_Rect tempSrc;
	SDL_Rect tempD;
	tempSrc.x = 0;
	tempSrc.y = 0;
	tempSrc.w = 113;
	tempSrc.h = 159;
	tempD.x = 0;
	tempD.y = 0;
	tempD.w = 113;
	tempD.h = 160;
	faceDownCard = new GameObject("images/CARDS-1080.png", renderer, tempSrc, tempD);
	faceDownCard2 = new GameObject("images/CARDS-1080.png", renderer, tempSrc, tempD);
}
void Game::Chips() {
	five = new GameObject("images/5s.png", renderer, false);
	ten = new GameObject("images/10s.png", renderer, false);
	twentyFive = new GameObject("images/25s.png", renderer, false);
	fifty = new GameObject("images/50s.png", renderer, false);
	hundred = new GameObject("images/100s.png", renderer, false);
	fiveHundred = new GameObject("images/500s.png", renderer, false);
	thousand = new GameObject("images/1000s.png", renderer, false);
	fiveThousand = new GameObject("images/5000s.png", renderer, false);
	tenThousand = new GameObject("images/10000s.png", renderer, false);
	five->setValue(5);
	ten->setValue(10);
	twentyFive->setValue(25);
	fifty->setValue(50);
	hundred->setValue(100);
	fiveHundred->setValue(500);
	thousand->setValue(1000);
	fiveThousand->setValue(5000);
	tenThousand->setValue(10000);
}
void Game::ChipsRender() {
	five->Render();
	ten->Render();
	twentyFive->Render();
	fifty->Render();
	hundred->Render(); 
	fiveHundred->Render();
	thousand->Render();
	fiveThousand->Render();
	tenThousand->Render();
}
void Game::ChipsPosition() {
	five->Update(219, 660, 60, 60);
	ten->Update(289, 660, 60, 60);
	twentyFive->Update(359, 660, 60, 60);
	fifty->Update(429, 660, 60, 60);
	hundred->Update(499, 660, 60, 60);
	fiveHundred->Update(569, 660, 60, 60);
	thousand->Update(639, 660, 60, 60);
	fiveThousand->Update(709, 660, 60, 60);
	tenThousand->Update(779, 660, 60, 60);
}