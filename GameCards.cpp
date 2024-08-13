#include "Game.h"
#include "GameObject.h"

void Game::MouseUpDeal() {
	faceUp = false;
	int mouseX, mouseY;
	Uint32 mosueState = SDL_GetMouseState(&mouseX, &mouseY);
	if (mouseX > faceDownCard->getDRectX() && mouseX < (faceDownCard->getDRectX() + faceDownCard->getDRectW())
		&& mouseY > faceDownCard->getDRectY() && mouseY < (faceDownCard->getDRectY() + faceDownCard->getDRectH())) {
		if (betTextAmount > 1) {
			dealCounter++;
			switch (dealCounter) {
			case 1:
				ResetTriggers();
				//clickAgainMessage = true;
				pCards.push_back(deck[deckCounter]);
				playerPoints += deck[deckCounter].getValue();
				if (deck[deckCounter].getValue() == 1) playerAce = true;
				deckCounter++;
				break;
			case 2:
				ResetTriggers();
				dCards.push_back(deck[deckCounter]);
				dealerPoints += deck[deckCounter].getValue();
				if (deck[deckCounter].getValue() == 1) dealerAce = true;
				deckCounter++;
				break;
			case 3:
				ResetTriggers();
				pCards.push_back(deck[deckCounter]);
				playerPoints += deck[deckCounter].getValue();
				if (deck[deckCounter].getValue() == 1) playerAce = true;
				deckCounter++;
				if (pCards[0].getValue() == 1 && pCards[1].getValue() == 10)
					EndGame(true);
				if (pCards[0].getValue() == 10 && pCards[1].getValue() == 1)
					EndGame(true);
				break;
			case 4:
				ResetTriggers();
				//buttonMessage
				dCards.push_back(deck[deckCounter]);
				dealerPoints += deck[deckCounter].getValue();
				if (deck[deckCounter].getValue() == 1) dealerAce = true;
				deckCounter++;
				deal = true;
				break;
			}
		}
		else {
			ResetTriggers();
			bett = true;
			makeBet = true;
		}
	}
}
void Game::MouseUpButtons() {
	//This one is for hit
	int mouseX, mouseY;
	Uint32 mosueState = SDL_GetMouseState(&mouseX, &mouseY);
	if (mouseX > 49 && mouseX < 174 && mouseY > 49 && mouseY < 105) {
		if (playerPoints < 21) {
			pCards.push_back(deck[deckCounter]);
			playerPoints += deck[deckCounter].getValue();
			if (deck[deckCounter].getValue() == 1) playerAce = true;
			deckCounter++;
			std::cout << "Hit Button Is Working when player has less than 21" << std::endl;
			if (playerPoints > 21) {
				ResetTriggers();
				busted = true;
				ResetRound();
			}
		}
	}
	//This one is for stand
	if (mouseX > 49 && mouseX < 174 && mouseY > 149 && mouseY < 205) {
		if (playerAce) {
			playerAce = false;
			if (playerPoints + 10 < 22) 
				playerPoints += 10;
		}
		stood = true;
		ResetTriggers();
		faceUp = true;
		playerStands = true;
		if (!dealerAce) updateDealer = true;
		else Ace(&dealerPoints);
	}
}
void Game::EndGame(bool natural) {
	ResetTriggers();
	if (!natural) {
		if (playerPoints == dealerPoints) {
			standOff = true;
			creditTextAmount += betTextAmount;
		}
		else if (playerPoints > dealerPoints || dealerPoints > 21) {
			youWin = true;
			creditTextAmount += (betTextAmount * 2);
		}
		else if (playerPoints < dealerPoints || dealerPoints < 22) houseWins = true;
	}
	else {
		youWin = true;
		playerPoints += (betTextAmount / 2);
	}

	ResetRound();
}
void Game::UpdateDealerCards() {
	Uint32 elapsedTime = SDL_GetTicks() - startTime;

	if (elapsedTime >= delayTime && updateDealer) {
		if (dealerPoints < 17 && dealerPoints < playerPoints) {
			dCards.push_back(deck[deckCounter]);
			dealerPoints += deck[deckCounter].getValue();
			if (deck[deckCounter].getValue() == 1) dealerAce = true;
			deckCounter++;
			std::cout << "Timer is working" << std::endl;
		}
		else {
			ResetTriggers();
			EndGame(false);
		}
		startTime = SDL_GetTicks();
	}
}
void Game::Shuffle() {
	srand(time(0));

	for (int i = 0; i < 52; i++) {
		GameObject temp = deck[i];
		int index = rand() % 51;
		deck[i] = deck[index];
		deck[index] = temp;
	}
}
void Game::Ace(int* points) {
	int temp = *points + 10;
	if (temp + 10 <= 21) {
		if (temp > playerPoints || temp > 16) {
			updateDealer = false;
			dealerAce = false;
			*points += 10;
			EndGame(false);
		}
	}
	else updateDealer = true;
}
void Game::ResetRound() {
	Shuffle();
	stood = false;
	bett = true;
	betTextAmount = 0;
	playerPoints = 0;
	dealerPoints = 0;
	deckCounter = 0;
	dealCounter = 0;
}