#pragma once
#include <ctime>
#include <cstdlib>
#include "Card.h"
#include "Define.res"

void shuffle() {
    srand(time(0));

    for (int i = 0; i < 52; i++) {
        Card temp = deck[i];
        int index = rand() % 51;
        deck[i] = deck[index];
        deck[index] = temp;
    }
}
