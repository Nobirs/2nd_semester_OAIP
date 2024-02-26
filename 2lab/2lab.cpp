#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <regex>
#include <string_view>

#include "Stack.h"

using namespace std;

#define DEFAULT_PROMPT ">>>"


void printSeparator() {
	cout << endl << "--------------------------------------------------" << endl;
}


int inputInt(string prompt, int from=INT_MIN, int to=INT_MAX, bool checkBetween=false) {
	static const regex re(R"(^-?[0-9]+)"s);
	while (true) {
		string input;
		smatch match;
		cout << prompt;
		getline(cin, input);
		string_view input_view(input);
		if (regex_match(input, match, re)) 
		{
			int value = stoi(input);
			if (checkBetween and (value >= from) and (value <= to)) return value;
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
		string_view input_view(input);
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


bool mainMenu() {
	char choice = inputYesNo("Do you want to start program[y/n]? ");
	switch (choice) {
		case 'y': return true;
		case 'n': return false;
		default: return false;
	}
}

void printMenu() {
	printSeparator();
	cout << "Menu:" << endl;
	cout << "1.Create New Stack" << endl;
	cout << "2.Add element to Stack" << endl;
	cout << "3.Print Stack" << endl;
	cout << "4.Sort Stack" << endl;
	cout << "5.Task: swap min and max value in Stack" << endl;
	cout << "6.Pop element from stack" << endl;
	cout << "7.Exit program" << endl;
	//cout << ">>> ";
}


void sortMenu() {
	cout << "Sort type: " << endl;
	cout << "1.Sort by address" << endl;
	cout << "2.Sort by value" << endl;
	//cout << ">>> ";
}

void fillStackByRandomNumbers(Stack* s) {
	int numbers = inputInt("How many random Numbers: ", 1, 1000, true);
	for (int i = 0; i < numbers; i++) {
		s->push(rand() % 100);
	}
}

Stack* createNewStack() {
	Stack* s = new Stack();
	char choice = inputYesNo("Fill by random numbers[y/n]?");
	switch (choice) {
		case 'y': fillStackByRandomNumbers(s); break;
		case 'n': break;
		default: break;
	}
	return s;
}


void pushToStack(Stack* s) {
	int value = inputInt("New number: ");
	s->push(value);
}

void printStack(Stack* s) {
	int* arr = s->toArray();
	printSeparator();
	for (int i = 0; i < s->getLength(); i++) {
		cout << arr[i] << " ";
	}
	printSeparator();
	cout << endl;
}


void sortStack(Stack* myStack) {
	cout << endl << "Before: ";
	printStack(myStack);
	sortMenu();
	int choice = inputInt(DEFAULT_PROMPT, 1, 2, true);
	switch (choice) {
		case 1: myStack->sortByPointers(); break;
		case 2: myStack->sortByValues(); break;
		default: cout << "Incorrect choice" << endl;
	}
	cout << endl << "After: ";
	printStack(myStack);
}

void popElement(Stack *myStack) {
	if (myStack->getLength() < 1) {
		cout << endl << "Stack is empty..." << endl;
	}
	else {
		cout << endl <<  "Returned value: " << myStack->pop() << endl;
	}
}



int main() {
	srand(time(NULL));
	if (mainMenu()) {
		Stack *myStack = new Stack();
		cout << endl << "Default stack was created..." << endl;
		int value = 0;
		while (true) {
			printMenu();

			int choice = inputInt(DEFAULT_PROMPT, 1, 7, true);

			switch (choice) {
			case 1: myStack = createNewStack();  break;
			case 2: pushToStack(myStack); break; // DONE
			case 3: printStack(myStack); break; // DONE
			case 4: sortStack(myStack); break; // DONE
			case 5: myStack->swapValues(myStack->findMin(), myStack->findMax()); break; // DONE
			case 6: popElement(myStack); break;
			case 7: return 0;
			}
		}
	}


	return 0;
}