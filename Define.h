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
void Deal();
void bust();
void options();
void stand();
void hit();
void split();
void insurance();
void dDown();
void bet();
void aces();
void endRound();
void dealerHit();
void dealerAces();

int deckCount;
int credits{ 1000 };
int playerPoints;
int dealerPoints;
int playerAcePoints;
int dealerAcePoints;
int rounds;
float betAmount;
bool splitt;
bool insure;
bool down;
bool delt;

vector<Card> pCard;
vector<Card> dCard;

const string Card::cardNumber[] = {
    "Ace of ", "Two of ", "Three of ", "Four of ", "Five of ", "Six of ", "Seven of ", "Eight of ", "Nine of ", "Ten of ", "Jack of ", "Queen of ", "King of "
};

const string Card::Suit[] = {
    "Hearts ", "Spades ", "Diamonds ", "Clubs "
};

const int Card::values[] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10
};