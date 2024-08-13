#include "Game.h"
#include "GameObject.h"

void Game::MouseUpBet() {
	if (!pCards.empty()) pCards.clear();
	if (!dCards.empty()) dCards.clear();
	int mouseX, mouseY;
	Uint32 mosueState = SDL_GetMouseState(&mouseX, &mouseY);
	if (mouseX > five->getDRectX() && mouseX < (five->getDRectX() + five->getDRectW())
		&& mouseY > five->getDRectY() && mouseY < (five->getDRectY() + five->getDRectW())) {
		if ((creditTextAmount - five->getValue()) >= 0) {
			ResetTriggers();
			bett = true;
			bettM = true;
			std::cout << "5 Dollars Was Bet" << std::endl;
			betTextAmount += five->getValue();
			creditTextAmount -= five->getValue();
		}
		else {
			notEnough = true;
			bettM = false;
		}
	}
	if (mouseX > ten->getDRectX() && mouseX < (ten->getDRectX() + ten->getDRectW())
		&& mouseY > ten->getDRectY() && mouseY < (ten->getDRectY() + ten->getDRectW())) {
		if ((creditTextAmount - ten->getValue()) >= 0) {
			ResetTriggers();
			bett = true;
			bettM = true;
			std::cout << "10 Dollars Was Bet" << std::endl;
			betTextAmount += ten->getValue();
			creditTextAmount -= ten->getValue();
		}
		else {
			notEnough = true;
			bettM = false;
		}
	}
	if (mouseX > twentyFive->getDRectX() && mouseX < (twentyFive->getDRectX() + twentyFive->getDRectW())
		&& mouseY > twentyFive->getDRectY() && mouseY < (twentyFive->getDRectY() + twentyFive->getDRectW())) {
		if ((creditTextAmount - twentyFive->getValue()) >= 0) {
			ResetTriggers();
			bett = true;
			bettM = true;
			std::cout << "25 Dollars Was Bet" << std::endl;
			betTextAmount += twentyFive->getValue();
			creditTextAmount -= twentyFive->getValue();
		}
		else {
			notEnough = true;
			bettM = false;
		}
	}
	if (mouseX > fifty->getDRectX() && mouseX < (fifty->getDRectX() + fifty->getDRectW())
		&& mouseY > fifty->getDRectY() && mouseY < (fifty->getDRectY() + fifty->getDRectW())) {
		if ((creditTextAmount - fifty->getValue()) >= 0) {
			ResetTriggers();
			bett = true;
			bettM = true;
			std::cout << "50 Dollars Was Bet" << std::endl;
			betTextAmount += fifty->getValue();
			creditTextAmount -= fifty->getValue();
		}
		else {
			notEnough = true;
			bettM = false;
		}
	}
	if (mouseX > hundred->getDRectX() && mouseX < (hundred->getDRectX() + hundred->getDRectW())
		&& mouseY > hundred->getDRectY() && mouseY < (hundred->getDRectY() + hundred->getDRectW())) {
		if ((creditTextAmount - hundred->getValue()) >= 0) {
			ResetTriggers();
			bett = true;
			bettM = true;
			std::cout << "100 Dollars Was Bet" << std::endl;
			betTextAmount += hundred->getValue();
			creditTextAmount -= hundred->getValue();
		}
		else {
			notEnough = true;
			bettM = false;
		}
	}
	if (mouseX > fiveHundred->getDRectX() && mouseX < (fiveHundred->getDRectX() + fiveHundred->getDRectW())
		&& mouseY > fiveHundred->getDRectY() && mouseY < (fiveHundred->getDRectY() + fiveHundred->getDRectW())) {
		if ((creditTextAmount - fiveHundred->getValue()) >= 0) {
			ResetTriggers();
			bett = true;
			bettM = true;
			std::cout << "500 Dollars Was Bet" << std::endl;
			betTextAmount += fiveHundred->getValue();
			creditTextAmount -= fiveHundred->getValue();
		}
		else {
			notEnough = true;
			bettM = false;
		}
	}
	if (mouseX > thousand->getDRectX() && mouseX < (thousand->getDRectX() + thousand->getDRectW())
		&& mouseY > thousand->getDRectY() && mouseY < (thousand->getDRectY() + thousand->getDRectW())) {
		if ((creditTextAmount - thousand->getValue()) >= 0) {
			ResetTriggers();
			bett = true;
			bettM = true;
			std::cout << "1000 Dollars Was Bet" << std::endl;
			betTextAmount += thousand->getValue();
			creditTextAmount -= thousand->getValue();
		}
		else {
			notEnough = true;
			bettM = false;
		}
	}
	if (mouseX > fiveThousand->getDRectX() && mouseX < (fiveThousand->getDRectX() + fiveThousand->getDRectW())
		&& mouseY > fiveThousand->getDRectY() && mouseY < (fiveThousand->getDRectY() + fiveThousand->getDRectW())) {
		if ((creditTextAmount - fiveThousand->getValue()) >= 0) {
			ResetTriggers();
			bett = true;
			bettM = true;
			std::cout << "5000 Dollars Was Bet" << std::endl;
			betTextAmount += fiveThousand->getValue();
			creditTextAmount -= fiveThousand->getValue();
		}
		else {
			notEnough = true;
			bettM = false;
		}
	}
	if (mouseX > tenThousand->getDRectX() && mouseX < (tenThousand->getDRectX() + tenThousand->getDRectW())
		&& mouseY > tenThousand->getDRectY() && mouseY < (tenThousand->getDRectY() + tenThousand->getDRectW())) {
		if ((creditTextAmount - five->getValue()) >= 0) {
			ResetTriggers();
			bett = true;
			bettM = true;
			std::cout << "10000 Dollars Was Bet" << std::endl;
			betTextAmount += tenThousand->getValue();
			creditTextAmount -= tenThousand->getValue();
		}
		else {
			notEnough = true;
			bettM = false;
		}
	}
}
void Game::UpdateBetText() {
	if (!betText.empty()) betText.erase(betText.begin());
	std::string temp = std::to_string(betTextAmount);
	GameObject tempBetText(&temp[0], renderer, true);
	betText.push_back(tempBetText);

	SDL_Rect rect = betAmount->getDRect();
	rect.x += betAmount->getDRectW() + 10;
	if (betTextAmount > 999) rect.w = 100;
	else if (betTextAmount > 99) rect.w = 60;
	else rect.w = 30;
	betText[0].setDRect(rect);
}
void Game::UpdateCreditText() {
	if (!creditText.empty()) creditText.erase(creditText.begin());
	std::string temp = std::to_string(creditTextAmount);
	GameObject tempcreditText(&temp[0], renderer, true);
	creditText.push_back(tempcreditText);

	SDL_Rect rect = credit->getDRect();
	rect.x += credit->getDRectW() + 10;
	if (creditTextAmount > 999) rect.w = 100;
	else if (creditTextAmount > 99) rect.w = 60;
	else rect.w = 30;
	creditText[0].setDRect(rect);
}
void Game::ResetTriggers() {
	bett = false;
	deal = false;
	ddownn = false;
	ddowned = false;
	bettM = false;
	notEnough = false;
	busted = false;
	makeBet = false;
	dealerBust = false;
	standOff = false;
	youWin = false;
	houseWins = false;
	playerStands = false;
	updateDealer = false;
}