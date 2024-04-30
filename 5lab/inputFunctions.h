#pragma once
#include <iostream>
#include <regex>


using std::string;
using std::regex;
using std::smatch;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::getline;

using namespace std::literals::string_literals; 


inline int inputInt(string prompt, int from = INT_MIN, int to = INT_MAX, bool checkBetween = false) {
	static const regex re(R"(^-?[0-9]+)"s);
	while (true) {
		string input;
		smatch match;
		cout << prompt;
		getline(cin, input);
		if (regex_match(input, match, re))
		{
			int value = stoi(input);
			if (!checkBetween) return value;
			if (checkBetween and (value >= from) and (value <= to)) return value;
		}
		cerr << "Incorrect input. Try again..." << endl;
	}
}


inline double inputDouble(string prompt, double from = 0, double to = INT_MAX, bool checkBetween = false) {
	static const regex re(R"(^-?[0-9]+(.[0-9]*)?)"s);
	while (true) {
		string input;
		smatch match;
		cout << prompt;
		getline(cin, input);
		if (regex_match(input, match, re))
		{
			double value = stod(input);
			if (!checkBetween) return value;
			if (checkBetween and (value >= from) and (value <= to)) return value;
		}
		cerr << "Incorrect input. Try again..." << endl;
	}
}


inline char inputYesNo(string prompt) {
	static const regex re(R"((YES|Yes|yes|NO|No|no)|([Y|y|N|n]))"s);
	while (true) {
		string input;
		smatch match;
		cout << prompt;
		getline(cin, input);
		if (regex_match(input, match, re))
		{
			if (input[0] == 'y' or input[0] == 'Y') return 1;
			else return 0;
			//return input[0];
		}
		else
		{
			cerr << "Incorrect input. Try again..." << endl;
		}
	}
}
