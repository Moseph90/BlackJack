#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include "Card.h"
#include "Define.h"
#include "PlayerFunctions.h"

void dealerHit() {

}
void dealerAces() {
    int temp = dealerPoints + 10;
    if (temp < 22 && temp >16) {
        dealerPoints += 10;
        dealerAce = false;
        dealerAceRan = true;
        endRound(false);
    }
    if (temp > 22) endRound(false);
    else if (temp < 17) stand();
}
void split() {

}
void insurance() {

}
void dDown() {

}
void endRound(bool natural) {
    wait(2);
    if (natural) {
        cout << "\n******You have a natural! You get 1.5x your bet******" << endl;
        credits += betAmount * 1.5;
        bet();
    }
    else {
        if (dealerPoints < 22 && dealerPoints > playerPoints) {
            cout << "\n******The House Wins With " << dealerPoints << " Points******" << endl;
            bet();
        }
        if (playerPoints < 22 && playerPoints > dealerPoints) {
            cout << "\n******You Win With " << playerPoints << " Points******" << endl;
            credits += betAmount * 2;
            bet();
        }
        if (dealerPoints > 21) {
            cout << "\n******You Win With " << playerPoints << " Points******" << endl;
            credits += betAmount * 2;
            bet();
        }
        if (dealerPoints == playerPoints) {
            cout << "\nStand-Off your bet of $" << betAmount << " returns to you" << dealerPoints << endl;
            credits += betAmount;
            bet();
        }
        if (credits <= 0) cashOut();
    }
}
void reset() {
    deckCount = 0;
    playerPoints = 0;
    dealerPoints = 0;
    playerAcePoints = 0;
    dealerAce = false;
    dealerAceRan = false;
    splitt = false;
    insure = false;
    down = false;
    dSplitt = false;
    dInsure = false;
    dubDown = false;
    stood = false;
    pCard.clear();
    dCard.clear();
}
void wait(int seconds) {
    this_thread::sleep_for(chrono::seconds(seconds));
}

int main() {
    for (int suit = 0; suit < 4; suit++) {

    for (int cardNum = 0; cardNum < 13; cardNum++) {
        Card card;
        card.setSuit(Card::Suit[suit]);
        card.setNumber(Card::cardNumber[cardNum]);
        card.setValue(Card::values[cardNum]);
        deck.push_back(card);
        }
    }

    hello();


    /*cout << "Cards before shuffle:\n" << endl;

    for (int b = 0; b < deck.size(); b++)
    cout << left << setw(2) << setfill('.') << b + 1 << ".." << setw(20) << setfill('.') << deck[b].toString() << deck[b].getValue() << endl;

    shuffle();

    cout << "\nCards after shuffle:\n" << endl;

    for (int a = 0; a < deck.size(); a++)
    cout << left << setw(2) << setfill('.') << a + 1 << ".." << setw(20) << setfill('.') << deck[a].toString() << deck[a].getValue() << endl; */
    return 0;
}

void cashOut() {
    cout << "\nYou cash out with $" << credits << ". Thanks for playing\n" << endl;
    exit(0);
}