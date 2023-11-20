#pragma once
#include <vector>
#include <string>
#include "Card.h"
using namespace std;

vector<Card> deck;

void menu();
void shuffle();
void hello();
void firstDeal();
void options();
void stand();
void hit();
void split();
void splitDisplay(string);
void splitOptionsFirst();
void splitEndRound();
void insurance();
void dDown();
void bet();
void aces();
void secondAces();
void endRound(bool);
void dealerAces();
void cashOut();
void reset();
void wait(int);
//void endRoundAce();

int deckCount;
int credits{ 1000 };
int playerPoints;
int secondPoints;
int dealerPoints;
int playerAcePoints;
int secondAcePoints;
int betAmount;
int secondAmount;
int sideBet;
bool dealerAce;
bool splitt;
bool insure;
bool down;
bool dubDown;
bool dInsure;
bool dSplitt;
bool dealerAceRan;
bool stood;
bool insured;
bool splitted;
bool dubAces;
bool splitNatural;
bool natty;
bool firstBusted;
bool secondBusted;

vector<Card> pCard;
vector<Card> dCard;
vector<Card> sCard;
vector<Card> tempHand;

const string Card::cardNumber[] = {
    "Ace of ", "Two of ", "Three of ", "Four of ", "Five of ", "Six of ", "Seven of ", "Eight of ", "Nine of ", "Ten of ", "Jack of ", "Queen of ", "King of "
};

const string Card::Suit[] = {
    "Hearts ", "Spades ", "Diamonds ", "Clubs "
};

const int Card::values[] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10
};

void split() {
    if (credits >= betAmount) {
        splitted = true;
        sCard.push_back(pCard[1]);
        pCard.erase(pCard.begin() + 1);
        pCard.push_back(deck[deckCount]);
        playerPoints -= playerPoints / 2;
        secondPoints = playerPoints;
        playerPoints += deck[deckCount].getValue();
        if (deck[deckCount].toName() == "Ace of ") playerAcePoints++;
        deckCount++;
        secondAmount = betAmount;
        credits -= secondAmount;
        if (sCard[0].toName() == "Ace of ") secondAcePoints++;
        cout << "\n******Player Splits******" << endl;
        wait(1);
        cout << "\n**The Bet Amount Of $" << secondAmount << " Is Added To The Second Hand**" << endl;
        
        cout << "\nFirst Hand" << endl;
        cout << "---------------" << endl;
        cout << pCard[0].toString() << endl;
        cout << "*" << pCard[1].toString() << endl;
        if (pCard[0].toName() == "Ace of " && pCard[1].getValue() == 10) {
            cout << "***You Got A Natural. Because You Split, The Bet Amount Of $" << betAmount << " Returns To You***" << endl;
            credits += betAmount;
            natty = true;
            splitDisplay("\n**Second Hand**"); 
        }
        options();
    }
    else {
        wait(1);
        cout << "\n**You Do Not Have Enough Credit To Place The Required Bet For Splitting**" << endl;
        options();
    }
}
void splitDisplay(string player) {
    wait(1);
    cout << player << endl;
    cout << left << setw(15) << setfill('-') << "-" << endl;
    wait(1);
    for (int i = 0; i < sCard.size(); i++) {
        cout << sCard[i].toString() << endl;
    }
    wait(1);
    cout << "*" << deck[deckCount].toString() << endl;
    sCard.push_back(deck[deckCount]);
    secondPoints += deck[deckCount].getValue();
    if (deck[deckCount].toName() == "Ace of ") secondAcePoints++;
    deckCount++;
    if (sCard[0].toName() == "Ace of " && sCard[1].getValue() != 10) stand();
    if (sCard[0].toName() == "Ace of " && sCard[1].getValue() == 10) {
        splitNatural = true;
        stood = true;
        if (natty || firstBusted) splitEndRound();
        else endRound(false);
    }
    if (sCard[1].toName() == "Ace of " && sCard[0].getValue() == 10) {
        splitNatural = true;
        stood = true;
        if (natty || firstBusted) splitEndRound();
        else endRound(false);
    }
    if (secondPoints > 21) {
        cout << "\n******You're Busted******" << endl;
        secondBusted = true;
        if (firstBusted || natty) bet();
        else {
            stood = true;
            stand();
        }
    }
    splitOptionsFirst();
}
void splitOptionsFirst() {
    wait(1);
    string input;
    cout << endl;
    cout << left << setw(15) << setfill(' ') << "Options" << setw(10) << setfill(' ') << "Input" << endl;
    cout << left << setw(20) << setfill('-') << "-" << endl;
    wait(1);
    cout << left << setw(15) << setfill(' ') << "Hit" << setw(10) << setfill(' ') << "H" << endl;
    cout << left << setw(15) << setfill(' ') << "Stand" << setw(10) << setfill(' ') << "ST" << endl;
    cout << "\nInput: ";
    cin >> input;
    if (input == "H") splitDisplay("\n******Player Hits******\n \n**Second Hand**");
    else if (input == "ST") {
        wait(1);
        cout << "\n******You Stand With " << secondPoints << "******" << endl;
        stood = true;
        stand();
    }
    else if (input == "ACE") {
        secondAces();
        splitOptionsFirst();
    }
    else {
        wait(1);
        cout << "\nInvalid Entry" << endl;
        splitOptionsFirst();
    }
}
void secondAces() {
    wait(1);
    string ace;
    if (secondAcePoints != 0) {
        if (secondAcePoints == 1) ace = " Ace, ";
        else ace = " Aces, ";
        cout << "\nYou have " << secondAcePoints << ace << "Would you like to make one of them equal 11? (Y/N): ";
        cin >> ace;
        wait(1);
        if (ace == "Y") {
            secondPoints += 10;
            secondAcePoints--;
            cout << "\n**One Ace is now worth 11 points**" << endl;
            }
        if (secondPoints > 21) {
            cout << "\n******You're Busted******" << endl;
            secondPoints = 0;
            if (natty || firstBusted) bet();
            else stand();
        }
    }
    else cout << "\nYou Have No Aces To Alter" << endl;
}
void splitEndRound() {
    wait(1);
    if (splitNatural) {
        cout << "\n******You Have a Natural! Because You Split Your Hand, Your Bet Is Returned To You******" << endl;
        credits += secondAmount;
        bet();
    }
    else if (!splitNatural && !secondBusted) {
        if (dealerPoints < 22 && dealerPoints > secondPoints) {
            cout << "\n******Dealer Stands. The House Wins With " << dealerPoints << "******" << endl;
            bet();
        }
        if (secondPoints < 22 && secondPoints > dealerPoints) {
            cout << "\n******Dealer Must Stand. You Win With " << secondPoints << "******" << endl;
            credits += secondAmount * 2;
            bet();
        }
        if (dealerPoints > 21) {
            cout << "\n******Dealer Is Busted. You Win With " << secondPoints << "******" << endl;
            credits += secondAmount * 2;
            bet();
        }
        else if (dealerPoints == secondPoints) {
            cout << "\n******Stand-Off Your Bet Of $" << secondAmount << " Returns To You******" << endl;
            credits += secondAmount;
            bet();
        }
    }
    else {
        cout << "\n***Second Hand Is Busted***" << endl;
        bet();
    }
}
/*void endRoundAce() {
    splitted = true;
    wait(1);
    cout << "\n**Player Has Two Aces And Splits **" << endl;
    wait(1);
    cout << "\n**Player May Only Draw One Card And Stand**" << endl;
    cout << endl;
    wait(1);
    cout << left << setw(20) << setfill(' ') << "First Hand" << setw(20) << setfill(' ') << "Second Hand" << endl;
    cout << left << setw(40) << setfill('-') << endl;
    wait(1);
    cout << left << setw(20) << setfill(' ') << pCard[0].toString() << setw(20) << setfill(' ') << pCard[1].toString() << endl;
    cout << left << setw(20) << setfill(' ') << deck[deckCount].toString() << setw(20) << setfill(' ') << deck[deckCount + 1].toString() << endl;

    playerPoints -= playerPoints / 2;
    secondPoints += playerPoints;
    playerPoints += deck[deckCount].getValue();
    secondPoints += deck[deckCount].getValue();
    if (pCard[0].toName() == "Ace of " && deck[deckCount].getValue() == 10) {
        cout << "\n***You Have A Natural. Becuase You Split, Your Bet Of $" << secondAmount << " Is Returned To You***" << endl;
        credits += betAmount;
    }
    if (deck[deckCount].toName() == "Ace of " && pCard[0].getValue() == 10) {
        cout << "\n***You Have A Natural On Your First Hand. Becuase You Split, Your Bet Of $" << secondAmount << " Is Returned To You***" << endl;
        credits += betAmount;
    }
    if (pCard[1].toName() == "Ace of " && deck[deckCount + 1].getValue() == 10) {
        cout << "\n***You Have A Natural On Your Second Hand. Becuase You Split, Your Bet Of $" << secondAmount << " Is Returned To You***" << endl;
        credits += betAmount;
    }
    if (deck[deckCount + 1].getValue() == 10 && pCard[1].toName() == "Ace of ") {
        cout << "\n***You Have A Natural. Becuase You Split, Your Bet Of $" << secondAmount << " Is Returned To You***" << endl;
        credits += betAmount;
    }
    stand();
}*/