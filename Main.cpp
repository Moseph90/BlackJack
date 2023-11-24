#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include "Card.h"
#include "Define.h"
#include "PlayerFunctions.h"

void dealerAces() {
    int temp = dealerPoints + 10;
    if (temp < 22 && temp > 16) {
        dealerPoints += 10;
        dealerAce = false;
        dealerAceRan = true;
        endRound(false);
    }
    if (temp > max(playerPoints, secondPoints) && temp < 22) {
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
        if (!splitted) {
            cout << "\n******You Have A Natural! You Get 1.5x Your Bet******" << endl;
            credits += betAmount * 1.5;
            bet();
        }
        if (splitted) {
            cout << "\n******You Have a Natural! Because You Split Your Hand, Your Bet Is Returned To You******" << endl;
            credits += betAmount;
            splitEndRound();
        }
    }
    else if (!natural && !natty) {
        if (playerPoints > 21 && dealerPoints < 22) {
            cout << "\n******You Hand Is Busted. The House Wins The Hand******" << endl;
            if (splitted) splitEndRound();
            else bet();
        }
        if (dealerPoints < 22 && dealerPoints > playerPoints) {
            cout << "\n******Dealer Stands. The House Wins The Hand With " << dealerPoints << "******" << endl;
            if (splitted) splitEndRound();
            else bet();
        }
        if (playerPoints < 22 && playerPoints > dealerPoints) {
            cout << "\n******Dealer Must Stand. You Win The Hand With " << playerPoints << "******" << endl;
            credits += betAmount * 2;
            if (splitted) splitEndRound();
            else bet();
        }
        if (dealerPoints > 21 && playerPoints < 22) {
            cout << "\n******Dealer Is Busted. You Win The Hand With " << playerPoints << "******" << endl;
            credits += betAmount * 2;
            if (splitted) splitEndRound();
            else bet();
        }
        if (dealerPoints > 21 && playerPoints > 21) {
            cout << "\n*****Dealer Hand And Player Hand Are Busted*****" << endl;
            if (splitted) splitEndRound();
            else bet();
        }
        else if (dealerPoints == playerPoints) {
            cout << "\n******Stand-Off On The Hand. Your Bet Of $" << betAmount << " Returns To You******" << endl;
            credits += betAmount;
            if (splitted) splitEndRound();
            else bet();
        }
    }
    if (firstBusted){
        cout << "\n***First Hand Is Busted***" << endl;
        splitEndRound();
    }
    if (natty) {
        cout << "\n***You're First Hand Is A Natural. The Bet Amount Of $" << betAmount << " Is Returned To You***" << endl;
        credits += secondAmount;
        splitEndRound();
    }
}
void reset() {
    deckCount = 0;
    playerPoints = 0;
    dealerPoints = 0;
    secondPoints = 0;
    playerAcePoints = 0;
    secondAcePoints = 0;
    sideBet = 0;
    betAmount = 0;
    secondAmount = 0;
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
    dubAces = false;
    splitNatural = false;
    firstBusted = false;
    secondBusted = false;
    natty = false;
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
        if (cardNum == 2 && suit == 1) tempHand.push_back(card); //Change cardNum to 0 on this line to give the player an Ace or 9, 10, 11, 12 for a 10/face card.
        if (cardNum == 2 && suit == 3) tempHand.push_back(card); //Change cardNum to 0 on this line to give the player an Ace or 9, 10, 11, 12 for a 10/face card.
        }
    }
    hello();

    return 0;
}

void cashOut() {
    cout << "\nYou cash out with $" << credits << ". Thanks for playing\n" << endl;
    wait(1);
    exit(0);
}