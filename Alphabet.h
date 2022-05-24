#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Alphabet {
public:
    Alphabet(char c, int list_len);
    char get_char();
    double get_prob();
    void increment();
private:
    char character;
    int count;
    double probability;
    int total;
};