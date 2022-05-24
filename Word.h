#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Alphabet.h"
using namespace std;
class Word {
public:
    Word(string input, vector<vector<Alphabet>> p_list);
    string get_word();
    double get_priority();
    vector<char> get_vowels();
    vector<char> get_consonants();
    bool operator <(const Word& b) { return this->priority > b.priority; };
private:
    string word;
    double priority;
    vector<char> vowels;
    vector<char> consonants;
    void set_priority(vector<double> p);
};
