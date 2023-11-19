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
void splitDisplay();
void splitOptionsFirst();
void splitOptionsSecond();
void splitEndRound();
void insurance();
void dDown();
void bet();
void aces();
void endRound(bool);
void dealerAces();
void cashOut();
void reset();
void wait(int);

int deckCount;
int credits{ 1000 };
int playerPoints;
int dealerPoints;
int playerAcePoints;
int betAmount;
int sideBet;
int hand;
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
bool secondSplit;

vector<Card> pCard;
vector<Card> dCard;
vector<Card> sCard;

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
    splitted = true;
    secondSplit = true;
    sCard.push_back(pCard[1]);
    pCard.erase(pCard.begin() + 1);
    cout << "\n******Player Splits******" << endl;
    splitDisplay();
}
void splitDisplay() {
    cout << left << setw(20) << setfill(' ') << "\nFirst Hand" << setw(20) << setfill(' ') << "Second Hand" << endl;
    cout << left << setw(15) << setfill('-') << "-" << endl;
    wait(1);
    if (pCard.size() > sCard.size() || pCard.size() == sCard.size()) {
        for (int i = 0; i < pCard.size(); i++) {
            cout << left << setw(20) << setfill(' ') << pCard[i].toString();
            wait(1);
            if (i < sCard.size()) cout << left << setw(20) << setfill(' ') << sCard[i].toString() << endl;
            else cout << endl;
        }
    }
    else if (pCard.size() < sCard.size()) {
        for (int i = 0; i < sCard.size(); i++) {
            if (i < pCard.size()) {
                cout << left << setw(20) << setfill(' ') << pCard[i].toString();
                wait(1);
                cout << left << setw(20) << setfill(' ') << sCard[i].toString() << endl;
            }
            else {
                cout << left << setw(40) << setfill(' ') << sCard[i].toString() << endl;
            }
        }
    }
    if (splitt) splitOptionsFirst();
    if (!splitt && secondSplit) splitOptionsSecond();
}
void splitOptionsFirst() {
    wait(1);
    string input;
    if (hand == 0) cout << "\n**For The Fist Hand**" << endl;
    wait(1);
    cout << left << setw(15) << setfill(' ') << "Options" << setw(10) << setfill(' ') << "Input" << endl;
    cout << left << setw(20) << setfill('-') << "-" << endl;
    wait(1);
    cout << left << setw(15) << setfill(' ') << "Hit" << setw(10) << setfill(' ') << "H" << endl;
    wait(1);
    cout << left << setw(15) << setfill(' ') << "Stand" << setw(10) << setfill(' ') << "ST" << endl;
    if (insure && dInsure && hand == 0) {
        wait(1);
        cout << left << setw(15) << setfill(' ') << "Insure" << setw(10) << setfill(' ') << "IN" << endl;
        dInsure = !dInsure;
    }
    cout << "\nInput: ";
    cin >> input;
    if (input == "H") hit();
    else if (input == "ST") {
        stood = true;
        splitt = false;
        down = false;
        wait(1);
        cout << "\n******You stand with " << playerPoints << "******" << endl;
        stand();
    }
    else if (input == "IN" && insure && hand == 0) {
        insure = false;
        splitt = false;
        down = false;
        insurance();
    }
    else if (input == "ACE") {
        down = false;
        splitt = false;
        aces();
        splitOptionsFirst();
    }
    else {
        wait(1);
        cout << "\nInvalid Entry" << endl;
        splitOptionsFirst();
    }
}
void splitOptionsSecond() {
}