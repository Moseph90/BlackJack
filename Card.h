#pragma once
#include<string>
#include<vector>
using namespace std;

class Card {
public:
    string suit;
    string number;
    int cardValue;

    static const string cardNumber[];
    static const string Suit[];
    static const int values[];

    void setSuit(string actualSuit) {
        suit = actualSuit;
    }
    void setNumber(string actualNumber) {
        number = actualNumber;
    }
    void setValue(int val) {
        cardValue = val;
    }
    int getValue() {
        return cardValue;
    }
    string toString() {
        return number + suit;
    }
};