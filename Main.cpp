#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include "Card.h"
#include "Define.h"
#include "PlayerFunctions.h"

void dealerAces() {
    int temp = dealerPoints + 10;
    if (temp < 22 && temp >16) {
        dealerPoints += 10;
        dealerAce = false;
        dealerAceRan = true;
        endRound(false);
    }
    if (dealerPoints > 22) endRound(false);
    else if (dealerPoints < 17) stand();
}
void insurance() {
    insured = true;
    int temp;
    int tempAmount = betAmount / 2;
    wait(1);
    cout << "\nHow Much Would You Like To Bet (Max " << tempAmount << " Or 0 To Cancel)?: ";
    cin >> temp;
    if (temp > credits) {
        cout << "\n**You Do Not Have Enough Credits**" << endl;
        insurance();
    }
    if (temp <= tempAmount && temp != 0) {
        sideBet = temp;
        credits -= sideBet;
        wait(1);
        cout << "\n******Player Insures With A Side Bet Of $" << sideBet << "******" << endl;
        if (splitted) splitOptionsFirst();
        else options();
    }
    if (temp == 0) options();
    else if (temp > tempAmount) {
        wait(1);
        cout << "\nInvalid Entry" << endl;
        insurance();
    }
}
void dDown() {
    int temp = betAmount * 2;
    if (betAmount > credits) {
        cout << "\n**You Do Not Have Enough To Double Down**" << endl;
        options();
    }
    else {
        credits -= betAmount;
        betAmount = temp;
        wait(1);
        cout << "\n******Player Doubles Down******" << endl;
        wait(1);
        cout << "\n******Bet Is Now $" << betAmount << "******" << endl;
        wait(1);
        cout << "\n******Player Gets One More Card And Then Stands******" << endl;
        deckCount++;
        cout << "\nPlayer Cards" << endl;
        cout << left << setw(15) << setfill('-') << "-" << endl;
        for (int i = 0; i < pCard.size(); i++) {
            wait(1);
            cout << pCard[i].toString() << endl;
        }
        wait(1);
        cout << "*" << deck[deckCount].toString() << endl;
        cout << endl;
        if (deck[deckCount].toName() == "Ace of ") playerAcePoints += 1;
        pCard.push_back(deck[deckCount]);
        playerPoints += deck[deckCount].getValue();
        deckCount++;
        string temp;
        if (playerAcePoints > 0) {
            cout << "Would You Like To Alter The Value Of One Of Your Aces Before The Hand Stands (Y/N)?: ";
            cin >> temp;
        }
        if (temp == "Y") aces();
        cout << "******Player Must Stand With " << playerPoints << "******" << endl;
        stand();
    }
}
void endRound(bool natural) {
    wait(1);
    if (natural) {
        cout << "\n******You have a natural! You Get 1.5x Your Bet******" << endl;
        credits += betAmount * 1.5;
        bet();
    }
    else if (!natural){
        if (dealerPoints < 22 && dealerPoints > playerPoints) {
            cout << "\n******Dealer Stands. The House Wins With " << dealerPoints << "******" << endl;
            bet();
        }
        if (playerPoints < 22 && playerPoints > dealerPoints) {
            cout << "\n******Dealer Must Stand. You Win With " << playerPoints << "******" << endl;
            credits += betAmount * 2;
            bet();
        }
        if (dealerPoints > 21) {
            cout << "\n******Dealer Is Busted. You Win With " << playerPoints << "******" << endl;
            credits += betAmount * 2;
            bet();
        }
        else if (dealerPoints == playerPoints) {
            cout << "\n******Stand-Off Your Bet Of $" << betAmount << " Returns To You******" << endl;
            credits += betAmount;
            bet();
        }
    }
}
void reset() {
    deckCount = 0;
    playerPoints = 0;
    dealerPoints = 0;
    playerAcePoints = 0;
    sideBet = 0;
    dealerAce = false;
    dealerAceRan = false;
    splitt = false;
    insure = false;
    down = false;
    dSplitt = false;
    dInsure = false;
    dubDown = false;
    stood = false;
    splitted = false;
    pCard.clear();
    dCard.clear();
    sCard.clear();
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
    wait(1);
    exit(0);
}