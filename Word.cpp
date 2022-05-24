#include "Word.h"
#include "Alphabet.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
Word::Word(string input, vector<vector<Alphabet>> p_list) {
    vector<char> V{ 'a','e','i','o','u' };
    vector<double> P;
    word = input;
    for (char& c : input) {
        if (find(V.begin(), V.end(), c) != V.end()) {
            vowels.push_back(c);
        }
        else {
            consonants.push_back(c);
        }
        
    }
    for (int p = 0; p < 5; p++) {
        int index = (int)input[p] - 97;
        P.push_back(p_list[p][index].get_prob());
    }
    set_priority(P);
}

string Word::get_word() {
    return word;
}

void Word::set_priority(vector<double> p) {
    double result = 1;
    for (double& prob : p) {
        result = result * prob;
    }
    priority = result;
    return;
}

double Word::get_priority() {
    return priority;
}

vector<char> Word::get_vowels() {
    return vowels;
}

vector<char> Word::get_consonants() {
    return consonants;
}
