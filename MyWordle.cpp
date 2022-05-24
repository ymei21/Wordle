// MyWordle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "Word.h"
#include "Alphabet.h"
#include "Wordle.h"
using namespace std;

vector<Alphabet> probability_process(vector<string>& word_list, int position) {
    int list_len = word_list.size();
    vector<Alphabet> alphabets;
    for (char i = 97; i < 123; i++) {
        Alphabet alphabet = Alphabet(i, list_len);
        alphabets.push_back(alphabet);
    }

    for (string& str : word_list) {
        int index = (int)str[position] - 97;
        alphabets[index].increment();
    }
    return alphabets;
}

vector<Word> words_process(vector<string>& word_list, vector<vector<Alphabet>> alphabets_prob_position) {
    vector<Word> words;
    for (string& str : word_list) {
        Word word = Word(str, alphabets_prob_position);
        words.push_back(word);
    }
    return words;
}

vector<string> keep_correct_char_pos(char target_c, int target_p, vector<string> word_list) {
    vector<string> updated_list;
    for (string& str : word_list) {
        if (str[target_p] == target_c) {
            updated_list.push_back(str);
        }
    }
    return updated_list;
}

vector<string> keep_correct_char(char target_c, int target_p, vector<string> word_list) {
    vector<string> updated_list;
    for (string& str : word_list) {
        if (str.find(target_c) != -1 && str.find(target_c) != target_p) {
            updated_list.push_back(str);
        }
    }
    return updated_list;
}

vector<string> elimate_wrong_char(char target_c, vector<string> word_list) {
    vector<string> updated_list;
    for (string& str : word_list) {
        if (str.find(target_c) == -1) {
            updated_list.push_back(str);
        }
    }
    return updated_list;
}

void play_game(vector<string> word_list) {
    Wordle wordle(word_list);
    cout << wordle.get_answer() << endl;

    while (wordle.get_turns() < 6 && wordle.end() == false) {
        cout << "Turn " << wordle.get_turns() << endl;
        wordle.play();
        vector<Report> result = wordle.get_result();
        for (Report& ele : result) {
            cout << ele.value << " ";
        }
        cout << endl;

        for (Report& ele : result) {
            cout << ele.character << endl;
            if (ele.value == 1) {
                word_list = keep_correct_char_pos(ele.character, ele.pos, word_list);
                cout << word_list.size() << endl;
            }
            else if (ele.value == 0) {
                word_list = keep_correct_char(ele.character, ele.pos, word_list);
                cout << word_list.size() << endl;
            }
            else if (ele.value == -1) {
                word_list = elimate_wrong_char(ele.character, word_list);
                cout << word_list.size() << endl;
            }
        }

        vector<vector<Alphabet>> alphabets_prob_position;
        for (int p = 0; p < 5; p++) {
            vector<Alphabet> alphabets_prob = probability_process(word_list, p);
            alphabets_prob_position.push_back(alphabets_prob);
        }
        vector<Word> words = words_process(word_list, alphabets_prob_position);
        sort(words.begin(), words.end());
        int size = 10;
        if (words.size() < size) {
            size = words.size();
        }
        for (int i = 0; i < size; i++) {
            cout << words[i].get_word() << " " << words[i].get_priority() << endl;
        }

    }
    
}

bool auto_play_game(vector<string> word_list, vector<Word> words, int index) {
    Wordle wordle(word_list, index);
    //cout << wordle.get_answer() << " ";

    while (wordle.get_turns() < 6 && wordle.end() == false) {
        //cout << "Turn " << wordle.get_turns() << endl;
        wordle.auto_play(words[0].get_word());
        vector<Report> result = wordle.get_result();

        for (Report& ele : result) {
            if (ele.value == 1) {
                word_list = keep_correct_char_pos(ele.character, ele.pos, word_list);
                //cout << word_list.size() << endl;
            }
            else if (ele.value == 0) {
                word_list = keep_correct_char(ele.character, ele.pos, word_list);
                //cout << word_list.size() << endl;
            }
            else if (ele.value == -1) {
                word_list = elimate_wrong_char(ele.character, word_list);
                //cout << word_list.size() << endl;
            }
        }

        vector<vector<Alphabet>> alphabets_prob_position;
        for (int p = 0; p < 5; p++) {
            vector<Alphabet> alphabets_prob = probability_process(word_list, p);
            alphabets_prob_position.push_back(alphabets_prob);
        }
        words = words_process(word_list, alphabets_prob_position);
        sort(words.begin(), words.end());

    }

    if (wordle.end()) {
        //cout << "Guess correctly" << endl;
        return true;
    }
    else {
        //cout << "Guess failed" << endl;
        return false;
    }
    return false;
}

int main()
{
    vector<string> word_list;
    ifstream file;
    string line;
    file.open("wordle_list_new.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            word_list.push_back(line);
        }
        file.close();
    }

    vector<vector<Alphabet>> alphabets_prob_position;
    for (int p = 0; p < 5; p++) {
        vector<Alphabet> alphabets_prob = probability_process(word_list, p);
        alphabets_prob_position.push_back(alphabets_prob);
    }
    vector<Word> words = words_process(word_list, alphabets_prob_position);
    sort(words.begin(), words.end());

    int size = word_list.size();
    //size = 250;
    
    
    int success = 0;
    for (int i = 0; i < size; i++) {
        if (auto_play_game(word_list, words, i)) {
            success++;
        }
    }
    
    cout << "Successful rate = " << (double)success / size << endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
