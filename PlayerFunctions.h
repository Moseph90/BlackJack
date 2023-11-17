#include <ctime>
#include <cstdlib>
#include "Define.h"
using namespace std;

void bet() {
    cout << "\nYou have 1000 credits. How much will you bet (must be between 2 and 500)?: ";
    cin >> betAmount;

    if (betAmount >= 2 && betAmount >= 500) {
        shuffle();
        if ((credits - betAmount) >= 0) {
            credits -= betAmount;
            menu();
        }
        else {
            cout << "\nYou do not have enough credits to bet that much" << endl;
            bet();
        }
    }
    else {
        cout << "\nInvalid entry" << endl;
        bet();
    }
}

void shuffle() {
    srand(time(0));

    for (int i = 0; i < 52; i++) {
        Card temp = deck[i];
        int index = rand() % 51;
        deck[i] = deck[index];
        deck[index] = temp;
    }
}
void hello() {
    string start;
    credits = 1000;
    cout << "Welcome to Moseph's Blackjack Game. After starting the game, input 'ACE' at any time to change the value of\none of your aces. " <<
        "Options are case sensitive, please keep your CAPS lock on. Input S to start : ";
    cin >> start;
    if (start == "S") bet();
    else {
        cout << "\nInvalid Entry" << endl;
        hello();
    }
}
void menu() {
    string deal;
    cout << "\nCredits: " << credits << "\nPress D to deal the cards: ";
    cin >> deal;
    if (deal == "D" && !delt) firstDeal();
    else if (deal == "D" && delt) Deal();
    else if (deal == "ACE") {
        aces();
        menu();
    }
    else hello();
}
void firstDeal() {
    delt = true;

    cout << left << setw(20) << setfill(' ') << "\nPlayer Cards" << setw(20) << setfill(' ') << "Dealer Cards" << endl;
    cout << left << setw(40) << setfill('-') << "-" << endl;
    
    cout << left << setw(20) << setfill(' ') << deck[deckCount].toString();
    playerPoints += deck[deckCount].getValue();
    if (deck[deckCount].toName() == "Ace of ") playerAcePoints += 1;
    pCard.push_back(deck[deckCount]);
    deckCount++;

    cout << left << setw(20) << setfill(' ') << deck[deckCount].toString() << endl;
    dealerPoints += deck[deckCount].getValue();
    if (deck[deckCount].toName() == "Ace of ") dealerAcePoints += 1;
    dCard.push_back(deck[deckCount]);
    deckCount++;

    cout << left << setw(20) << setfill(' ') << deck[deckCount].toString();
    playerPoints += deck[deckCount].getValue();
    if (deck[deckCount].toName() == "Ace of ") playerAcePoints += 1;
    pCard.push_back(deck[deckCount]);
    deckCount++;

    cout << left << setw(20) << setfill(' ') << "Face Down" << endl;
    dealerPoints += deck[deckCount].getValue();
    if (deck[deckCount].toName() == "Ace of ") dealerAcePoints += 1;
    dCard.push_back(deck[deckCount]);
    deckCount++;

    int val = pCard[0].getValue() + pCard[1].getValue();
    if (dCard[0].toName() == "Ace of ") insure = true;
    if (val == 9 || val == 10 || val == 11) down = true;
    if (pCard[0].toName() == pCard[1].toName()) splitt = true;

    options();
}
void options() {
    string input;
    cout << endl;
    cout << left << setw(15) << setfill(' ') << "Action" << setw(10) << setfill(' ') << "Input" << endl;
    cout << left << setw(20) << setfill('-') << "-" << endl;
    cout << left << setw(15) << setfill(' ') << "Hit" << setw(10) << setfill(' ') << "H" << endl;
    cout << left << setw(15) << setfill(' ') << "Stand" << setw(10) << setfill(' ') << "ST" << endl;
    if (insure)
        cout << left << setw(15) << setfill(' ') << "Insure" << setw(10) << setfill(' ') << "IN" << endl;
    if (splitt) 
        cout << left << setw(15) << setfill(' ') << "Split" << setw(10) << setfill(' ') << "SP" << endl;
    if (down)
        cout << left << setw(15) << setfill(' ') << "Double Down" << setw(10) << setfill(' ') << "DD" << endl;
    cout << endl;
    cin >> input;
    if (input == "H") hit();
    else if (input == "ST") stand();
    else if (input == "SP" && splitt) {
        splitt = false;
        split();
    }
    else if (input == "IN" && insure) {
        insure = false;
        insurance();
    }
    else if (input == "DD" && down) {
        down = false;
        dDown();
    }
    else if (input == "ACE") {
        aces();
        options();
    }
    else {
        cout << "\nInvalid Entry" << endl;
        options();
    }
}
void hit() {
    rounds++;
    int temp = (deckCount / 2);
    deckCount++;
    cout << left << setw(15) << setfill(' ') << "\nPlayer Cards" << endl;
    cout << left << setw(15) << setfill('-') << "-" << endl;
    for (int i = 0; i < temp; i++)
        cout << left << setw(20) << setfill(' ') << pCard[i].toString() << endl;
    cout << left << setw(20) << setfill(' ') << deck[deckCount].toString() << endl;
    cout << endl;
    if (deck[deckCount].toName() == "Ace of ") playerAcePoints += 1;
    pCard.push_back(deck[deckCount]);
    playerPoints += deck[deckCount].getValue();
    if (playerPoints > 21) endRound();
    deckCount++;

    if (playerPoints > 21) bust();

    options();
}
void aces() {
    string ace;
    if (playerAcePoints != 0) {
        if (playerAcePoints == 1) ace = " Ace, ";
        else ace = " Aces, ";
        cout << "You have " << playerAcePoints << ace << "Would you like to make one of them equal 11? (Y/N): ";
        cin >> ace;
        if (ace == "Y") {
            playerPoints += 10;
            playerAcePoints--;
            cout << "One Ace is now worth 11 points to your total on the table\n" << endl;
        }
    }
    else cout << "\nYou have no Aces to alter" << endl;
}
void stand() {
    cout << left << setw(20) << setfill(' ') << "\nPlayer Cards" << setw(20) << setfill(' ') << "Dealer Cards" << endl;
    cout << left << setw(40) << setfill('-') << "-" << endl;
    cout << left << setw(20) << setfill(' ') << pCard[0].toString();
    cout << left << setw(20) << setfill(' ') << dCard[0].toString() << endl;
    cout << left << setw(20) << setfill(' ') << pCard[1].toString();
    cout << left << setw(20) << setfill(' ') << dCard[1].toString() << endl;
    for (int i = 0; i < pCard.size() - 2; i++) cout << left << setw(20) << setfill(' ') << pCard[i + 2].toString() << endl;

    if (dealerAcePoints > 0) {
        if (dealerPoints + (dealerAcePoints * 10) >= 17) endRound();
        else if (dealerPoints + 10 >= 17) endRound();
    }

    if (dealerPoints < 17) {
        cout << "\nDealer Hits" << endl;
        cout << left << setw(20) << setfill(' ') << "\nDealer Cards" << endl;
        cout << left << setw(20) << setfill('-') << "-" << "\n" << endl;
        if (dCard.size() > 2)
            for (int i = 2; i < dCard.size(); i++) cout << left << setw(20) << setfill(' ') << dCard[i].toString() << endl;
        cout << deck[deckCount].toString() << endl;
        dCard.push_back(deck[deckCount]);
        deckCount++;
    }
    if (dealerAcePoints > 0) {
        if (dealerPoints + (dealerAcePoints * 10) >= 17) dealerAces();
        else if (dealerPoints + 10 >= 17) dealerAces();
    }
    else if (dealerAcePoints == 0) {
        if (dealerPoints >= 17) endRound();
        stand();
    }
}