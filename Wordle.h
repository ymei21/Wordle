#pragma once
#include "Word.h"
#include "Report.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;
class Wordle
{
public:
	Wordle(vector<string> word_list);
	Wordle(vector<string> word_list, int index);
	void play();
	void auto_play(string in);
	string get_answer();
	int get_turns();
	bool end();
	vector<Report> get_result();
private:
	int turns;
	string answer;
	string player_input;
	vector<Report> result;
	void set_input(string input);
	void process();
};

