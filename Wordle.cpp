#include "Wordle.h"
#include "Word.h"
#include "Report.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;
Wordle::Wordle(vector<string> word_list) {
	srand(time(0));
	int index = rand() % word_list.size();
	answer = word_list[index];
}

Wordle::Wordle(vector<string> word_list, int index) {
	answer = word_list[index];
}

void Wordle::set_input(string input) {
	player_input = input;
	return;
}

string Wordle::get_answer() {
	return answer;
}

int Wordle::get_turns() {
	return turns;
}

vector<Report> Wordle::get_result() {
	return result;
}

bool Wordle::end() {
	if (turns == 0) {
		return false;
	}
	for (Report& ele : result) {
		if (ele.value != 1) {
			return false;
		}
	}
	return true;
}

void Wordle::process() {
	vector<int> compare{-1,-1,-1,-1,-1};
	for (int i = 0; i < 5; i++) {
		if (player_input[i] == answer[i]) {
			compare[i] = 1;
		}
		else {
			for (int j = 0; j < 5; j++) {
				if (player_input[i] == answer[j] && i != j) {
					compare[i] = 0;
				}
			}
		}
	}
	vector<Report> re;
	for (int i = 0; i < 5; i++) {
		Report report(player_input[i], compare[i], i);
		re.push_back(report);
	}
	result = re;
	return;
}

void Wordle::play() {
	string in;
	cout << "Please enter 5 letters word:" << endl;
	cin >> in;
	while (in.size() != 5) {
		cout << "Please enter 5 letters word:" << endl;
		cin >> in;
	}
	set_input(in);
	process();
	turns++;
}

void Wordle::auto_play(string in) {
	set_input(in);
	process();
	turns++;
}