#include <iostream>
#include <regex>
#include "Stack.h"


using namespace std;

double inputDouble(string prompt) {
	static const regex re(R"(^-?[0-9]+(.[0-9]*)?)"s);
	while (true) {
		string input;
		smatch match;
		cout << prompt;
		getline(cin, input);
		if (regex_match(input, match, re))
		{
			double value = stod(input);
			return value;
		}
		cerr << "Incorrect input. Try again..." << endl;
	}
}


char inputYesNo(string prompt) {
	static const regex re(R"([y|n])"s);
	while (true) {
		string input;
		smatch match;
		cout << prompt;
		getline(cin, input);
		if (regex_match(input, match, re))
		{
			return input[0];
		}
		else
		{
			cerr << "Incorrect input. Try again..." << endl;
		}
	}
}


int main() {
	while(true)
	{
		char choice = inputYesNo("Do you wanna start program[y/n]?");
		switch (choice) {
		case 'y':
		{
			cout << "infix form: (a+b)*(c-d)/e\n";
			string inputForm = "(a+b)*(c-d)/e";

			string RPN = infixToRPN(inputForm);
			cout << "RPN: " << RPN << endl;
			vector<tuple<char, double>> values;
			for (char letter = 'a'; letter <= 'e'; letter++) {
				string prompt = " = ";
				prompt[0] = letter;
				double val = inputDouble(prompt);
				values.push_back({ letter, val });
			}
			cout << endl << "Result: " << evaluateRPN(RPN, values) << endl;
			break;
		}
		case 'n':
			cout << "Exit the program...";
			return 0;
		}
	}

	return 0;
}