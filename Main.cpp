#include <iostream>
#include <iomanip>
#include "Card.h"
#include "Define.h"
#include "PlayerFunctions.h"

void dealerHit() {

}
void dealerAces() {
    if (dealerPoints + 10 <= 21)
        dealerPoints += 10;
    else endRound();
}
void split() {

}
void insurance() {

}
void dDown() {

}
void bust() {

}
void Deal() {

}
void endRound() {

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

    shuffle();
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