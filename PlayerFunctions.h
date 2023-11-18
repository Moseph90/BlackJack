#include <ctime>
#include <cstdlib>
#include "Define.h"
using namespace std;

void bet() {
    reset();
    if (credits <= 0) {
        cout << "\nYou do not have any more credits to play with" << endl;
        cashOut();
    }
    cout << "\nYou have $" << credits << " in credit. Place your bet(must be between 2 and 500) or bet 0 to cash out : ";
    cin >> betAmount;

    if (betAmount >= 2 && betAmount <= 500 && betAmount) {
        shuffle();
        int temp = credits - betAmount;
        if (temp >= 0) {
            credits -= betAmount;
            menu();
        }
        else {
            cout << "\nYou do not have enough credits to bet that much" << endl;
            bet();
        }
    }
    if (betAmount < 2 || betAmount > 500){
        if (betAmount == 0) cashOut();
        else {
            cout << "\nInvalid entry" << endl;
            bet();
        }
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
    cout << "Welcome to Moseph's Blackjack Game. After placing a bet, input 'ACE' at any time to change the value of\none of your aces, " <<
        "Options are case sensitive, please keep your CAPS lock on. Input S to start: ";
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
    if (deal == "D") firstDeal();
    if (deal == "ACE") {
        aces();
        menu();
    }
    else hello();
}
void firstDeal() {
    cout << left << setw(20) << setfill(' ') << "\nPlayer Cards" << setw(20) << setfill(' ') << "Dealer Cards" << endl;
    cout << left << setw(40) << setfill('-') << "-" << endl;
    
    cout << left << setw(20) << setfill(' ') << deck[deckCount].toString();
    playerPoints += deck[deckCount].getValue();
    if (deck[deckCount].toName() == "Ace of ") playerAcePoints += 1;
    pCard.push_back(deck[deckCount]);
    deckCount++;

    cout << left << setw(20) << setfill(' ') << deck[deckCount].toString() << endl;
    dealerPoints += deck[deckCount].getValue();
    if (deck[deckCount].toName() == "Ace of ") dealerAce = true;
    dCard.push_back(deck[deckCount]);
    deckCount++;

    cout << left << setw(20) << setfill(' ') << deck[deckCount].toString();
    playerPoints += deck[deckCount].getValue();
    if (deck[deckCount].toName() == "Ace of ") playerAcePoints += 1;
    pCard.push_back(deck[deckCount]);
    deckCount++;

    cout << left << setw(20) << setfill(' ') << "Face Down" << endl;
    dealerPoints += deck[deckCount].getValue();
    if (deck[deckCount].toName() == "Ace of ") dealerAce = true;
    dCard.push_back(deck[deckCount]);
    deckCount++;

    int val = pCard[0].getValue() + pCard[1].getValue();
    if (dCard[0].toName() == "Ace of ") insure = true;
    if (val == 9 || val == 10 || val == 11) down = true;
    if (pCard[0].toName() == pCard[1].toName()) splitt = true;

    if (pCard[0].toName() == "Ace of " && pCard[1].getValue() == 10) endRound(true);

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
    cout << "\n\nRemember to input 'ACE' to alter the value of one of your Aces before your stand!" << endl;
    cout << endl;
    cin >> input;
    if (input == "H") hit();
    else if (input == "ST") {
        cout << "\nYou stand with " << playerPoints << endl;
        stand();
    }
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
    deckCount++;
    cout << left << setw(15) << setfill(' ') << "\nPlayer Cards" << endl;
    cout << left << setw(15) << setfill('-') << "-" << endl;
    for (int i = 0; i < pCard.size(); i++)
        cout << left << setw(20) << setfill(' ') << pCard[i].toString() << endl;
    cout << left << setw(20) << setfill(' ') << deck[deckCount].toString() << endl;
    cout << endl;
    if (deck[deckCount].toName() == "Ace of ") playerAcePoints += 1;
    pCard.push_back(deck[deckCount]);
    playerPoints += deck[deckCount].getValue();
    if (playerPoints > 21) {
        cout << "\nYou busted" << endl;
        bet();
    }
    deckCount++;

    options();
}
void aces() {
    string ace;
    if (playerAcePoints != 0) {
        if (playerAcePoints == 1) ace = " Ace, ";
        else ace = " Aces, ";
        cout << "\nYou have " << playerAcePoints << ace << "Would you like to make one of them equal 11? (Y/N): ";
        cin >> ace;
        if (ace == "Y") {
            playerPoints += 10;
            playerAcePoints--;
            cout << "\nOne Ace is now worth 11 points to your total on the table" << endl;
        }
    }
    else cout << "\nYou have no Aces to alter" << endl;
}
void stand() {
    cout << left << setw(15) << setfill(' ') << "\nDealer Cards" << endl;
    cout << left << setw(15) << setfill('-') << "-" << endl;
    for (int i = 0; i < dCard.size(); i++)
        cout << left << setw(15) << setfill(' ') << dCard[i].toString() << endl;

    if (dealerAce) dealerAces();

    if (dealerPoints < 17) {
        cout << "\nDealer Hits\n" << endl;
        cout << left << setw(20) << setfill(' ') << "Dealer Cards" << endl;
        cout << left << setw(20) << setfill('-') << "-" << endl;
        for (int i = 0; i < dCard.size(); i++)
            cout << left << setw(15) << setfill(' ') << dCard[i].toString() << endl;
        if (dCard.size() > 2)
            for (int i = 2; i < dCard.size(); i++) cout << left << setw(20) << setfill(' ') << dCard[i + 1].toString() << endl;
        cout << deck[deckCount].toString() << endl;
        dCard.push_back(deck[deckCount]);
        deckCount++;
        dealerPoints += deck[deckCount].getValue();
        if (deck[deckCount].toName() == "Ace of ") dealerAce = true;
    }
    if (dealerAce) dealerAces();
    if (dealerPoints >= 17) endRound(false);
    else stand();
}