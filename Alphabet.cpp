#include "Alphabet.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
Alphabet::Alphabet(char c, int list_len) {
    character = c;
    count = 0;
    probability = 0;
    total = list_len;
}

char Alphabet::get_char() {
    return character;
}

double Alphabet::get_prob() {
    return probability;
}

void Alphabet::increment() {
    count++;
    probability = (double)count / total;
    return;
}