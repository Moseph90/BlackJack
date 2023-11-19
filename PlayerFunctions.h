#include <ctime>
#include <cstdlib>
using namespace std;

void bet() {
    if (credits <= 0) cashOut();
    wait(1);
    reset();
    shuffle();
    if (credits <= 0) {
        cout << "\nYou do not have any more credit to play with" << endl;
        wait(1);
        cashOut();
    }
    cout << "\nYou have $" << credits << " in credit. Place your bet (must be between 2 and 500). Input 0 to cash out: ";
    cin >> betAmount;

    if (betAmount >= 2 && betAmount <= 500) {
        int temp = credits - betAmount;
        if (temp >= 0) {
            credits -= betAmount;
            menu();
        }
        else {
            wait(1);
            cout << "\nYou do not have enough credits to bet that much" << endl;
            bet();
        }
    }
    if (betAmount < 2 || betAmount > 500){
        if (betAmount == 0) cashOut();
        else {
            wait(1);
            cout << "\nInvalid entry. Please choose a number between 2 and 500 that does not exceed your credit" << endl;
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
    cout << "Welcome to Moseph's Blackjack Game." << endl;
    wait(1);
    cout << "Would you like to skip the tutorial (Y/N)?: ";
    cin >> start;
    if (start == "N") {
        wait(1);
        cout << "\nYou may change the value of any Aces you have in your hand, simply input 'ACE' any time after you make your bet" << endl;
        wait(5);
        cout << "You can wait until you're about to Stand, or you can do it early, or you can leave it as 1" << endl;
        wait(4);
        cout << "Once you change the value of an Ace, you cannot change it back, so be careful" << endl;
        wait(4);
        cout << "Naturals will automatically be counted, but other than that, be sure to change your Ace(s) before you stand!" << endl;
        wait(5);
        cout << "You can only Spllit or Double Down during your first turn, you cannot do both (eg. if you have two 5's)" << endl;
        wait(5);
        cout << "If you can Insure, you may choose to do so at any time before you stand. Feel free to complete your turn before deciding" << endl;
        wait(5);
        cout << "Options are case sensitive, please keep your CAPS lock on. Input any key to start: ";
        cin >> start;
        bet();
    }
        else bet();
}
void menu() {
    wait(1);
    string deal;
    cout << "\nCredit remaining: $" << credits << "\nInput D to deal the cards: ";
    cin >> deal;
    if (deal == "D") firstDeal();
    else {
        cout << "\nInvalid Entry" << endl;
        menu();
    }
}
void firstDeal() {
    cout << left << setw(20) << setfill(' ') << "\nPlayer Cards" << setw(20) << setfill(' ') << "Dealer Cards" << endl;
    cout << left << setw(40) << setfill('-') << "-" << endl;
    wait(1);
    cout << left << setw(20) << setfill(' ') << deck[deckCount].toString();
    playerPoints += deck[deckCount].getValue();
    if (deck[deckCount].toName() == "Ace of ") playerAcePoints += 1;
    pCard.push_back(deck[deckCount]);
    deckCount++;
    wait(1);
    cout << left << setw(20) << setfill(' ') << deck[deckCount].toString() << endl;
    dealerPoints += deck[deckCount].getValue();
    if (deck[deckCount].toName() == "Ace of ") dealerAce = true;
    dCard.push_back(deck[deckCount]);
    deckCount++;
    wait(1);
    cout << left << setw(20) << setfill(' ') << deck[deckCount].toString();
    playerPoints += deck[deckCount].getValue();
    if (deck[deckCount].toName() == "Ace of ") playerAcePoints += 1;
    pCard.push_back(deck[deckCount]);
    deckCount++;
    wait(1);
    cout << left << setw(20) << setfill(' ') << "Face Down" << endl;
    dealerPoints += deck[deckCount].getValue();
    if (deck[deckCount].toName() == "Ace of ") dealerAce = true;
    dCard.push_back(deck[deckCount]);
    deckCount++;

    int val = pCard[0].getValue() + pCard[1].getValue();
    if (dCard[0].toName() == "Ace of ") {
        insure = true;
        dInsure = true;
    }
    if (val == 9 || val == 10 || val == 11) {
        down = true;
        dubDown = true;
    }
    if (pCard[0].toName() == pCard[1].toName()) {
        splitt = true;
        dSplitt = true;
    }
    if (pCard[0].toName() == "Ace of " && pCard[1].getValue() == 10) endRound(true);
    if (pCard[1].toName() == "Ace of " && pCard[0].getValue() == 10) endRound(true);

    options();
}
void options() {
    wait(1);
    string input;
    cout << endl;
    cout << left << setw(15) << setfill(' ') << "Options" << setw(10) << setfill(' ') << "Input" << endl;
    cout << left << setw(20) << setfill('-') << "-" << endl;
    wait(1);
    cout << left << setw(15) << setfill(' ') << "Hit" << setw(10) << setfill(' ') << "H" << endl;
    wait(1);
    cout << left << setw(15) << setfill(' ') << "Stand" << setw(10) << setfill(' ') << "ST" << endl;
    if (insure && dInsure) {
        wait(1);
        cout << left << setw(15) << setfill(' ') << "Insure" << setw(10) << setfill(' ') << "IN" << endl;
        dInsure = !dInsure;
    }
    if (splitt && dSplitt) {
        wait(1);
        cout << left << setw(15) << setfill(' ') << "Split" << setw(10) << setfill(' ') << "SP" << endl;
        dSplitt = !dSplitt;
    }
    if (down && dubDown) {
        wait(1);
        cout << left << setw(15) << setfill(' ') << "Double Down" << setw(10) << setfill(' ') << "DD" << endl;
        dubDown = !dubDown;
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
    else if (input == "SP" && splitt) {
        splitt = false;
        down = false;
        split();
    }
    else if (input == "IN" && insure) {
        insure = false;
        splitt = false;
        down = false;
        insurance();
    }
    else if (input == "DD" && down) {
        insure = false;
        down = false;
        splitt = false;
        stood = true;
        dDown();
    }
    else if (input == "ACE") {
        down = false;
        splitt = false;
        aces();
        options();
    }
    else {
        wait(1);
        cout << "\nInvalid Entry" << endl;
        options();
    }
}
void hit() {
    wait(1);
    cout << "\n******Player Hits******" << endl;
    wait(1);
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
    if (playerPoints > 21) {
        wait(1);
        cout << "\n******You're busted******" << endl;
        if (!splitted) bet();
        else if (splitted) splitOptionsSecond();
    }
    if (!splitted) options();
    else splitOptionsFirst();
}
void aces() {
    wait(1);
    string ace;
    if (playerAcePoints != 0) {
        if (playerAcePoints == 1) ace = " Ace, ";
        else ace = " Aces, ";
        cout << "\nYou have " << playerAcePoints << ace << "Would you like to make one of them equal 11? (Y/N): ";
        cin >> ace;
        wait(1);
        if (ace == "Y") {
            playerPoints += 10;
            playerAcePoints--;
            cout << "\nOne Ace is now worth 11 points" << endl;
        }
    }
    else cout << "\nYou have no Aces to alter" << endl;
    if (playerPoints > 21) endRound(false);
}
void stand() {
    wait(1);
    if (stood) {
        stood = false;
        cout << "\nDealer Cards" << endl;
        cout << left << setw(15) << setfill('-') << "-" << endl;
        wait(1);
        cout << dCard[0].toString() << endl;
        wait(1);
        cout << "*" << dCard[1].toString() << endl;
        if (dCard[0].toName() == "Ace of " && dCard[1].getValue() == 10 && insured) {
            wait(1);
            cout << "\n******Dealer's Second Card Is Worth 10. Player Wins The Insurance******" << endl;
            credits += sideBet;
            cout << "\n******Credit: $" << credits << "******" << endl;
        }
        if (dealerAce && !dealerAceRan) dealerAces();
        if (dealerPoints > 16) endRound(false);
    }

    if (dealerPoints < 17 && dealerPoints < playerPoints) {
        wait(1);
        cout << "\n******Dealer Hits******\n" << endl;
        wait(1);
        cout << left << setw(20) << setfill(' ') << "Dealer Cards" << endl;
        cout << left << setw(20) << setfill('-') << "-" << endl;
        for (int i = 0; i < dCard.size(); i++) {
            wait(1);
            cout << dCard[i].toString() << endl;
        }
        wait(1);
        cout << "*" << deck[deckCount].toString() << endl;
        dCard.push_back(deck[deckCount]);
        dealerPoints += deck[deckCount].getValue();
        deckCount++;
        if (deck[deckCount].toName() == "Ace of ") dealerAce = true;
    }
    if (dealerAce && !dealerAceRan) dealerAces();
    if (dealerPoints >= 17 || dealerPoints > playerPoints) endRound(false);
    else if (dealerPoints < 17 && dealerPoints < playerPoints) stand();
}