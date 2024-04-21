#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <regex>
#include <Windows.h>


#include "list.h"

using namespace std;

#define DEFAULT_PROMPT ">>>"


void printSeparator() {
	cout << endl << "--------------------------------------------------" << endl;
}

void printList(LinkedList* l) {
	printSeparator();
	if (l->length != 0) {
		for (int i = 0; i < l->length; i++) {
			cout << *(l->getAt(i)) << " ";
		}
		cout << endl;
	}
	else {
		cout << "Is empty" << endl;
	}
	printSeparator();
}

void printReverseList(LinkedList* l) {
	printSeparator();
	if (l->length != 0) {
		for (int i = l->length - 1; i >= 0; i--) {
			cout << *(l->getAt(i)) << " ";
		}
		cout << endl;
	}
	else {
		cout << "Is empty" << endl;
	}
	printSeparator();
}

int inputInt(string prompt, int from = INT_MIN, int to = INT_MAX, bool checkBetween = false) {
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
	cout << "1.Create New LinkedList" << endl;
	cout << "2.Add element at the begin of LinkedList" << endl;
	cout << "3.Add element at the end of LinkedList" << endl;
	cout << "4.Pop element from the begin of LinkedList" << endl;
	cout << "5.Pop element from the end of LinkedList" << endl;
	cout << "6.Print LinkedList from begin to end" << endl;
	cout << "7.Print LinkedList from end to begin" << endl;
	cout << "8.Task: swap min and max value in LinkedList" << endl;
	cout << "9.Exit program" << endl;
	//cout << ">>> ";
}

void fillListByRandomNumbers(LinkedList* s) {
	int numbers = inputInt("How many random Numbers: ", 1, 1000, true);
	for (int i = 0; i < numbers; i++) {
		s->push_back(rand() % 100);
	}
}

LinkedList* createNewList() {
	LinkedList* s = new LinkedList();
	char choice = inputYesNo("Fill by random numbers[y/n]?");
	switch (choice) {
	case 'y':
		fillListByRandomNumbers(s);
		printList(s);
		break;
	case 'n': break;
	default: break;
	}
	return s;
}

void pushBackLinkedList(LinkedList* s) {
	int value = inputInt("New number: ");
	s->push_back(value);
	printList(s);
}

void pushFrontLinkedList(LinkedList* s) {
	int value = inputInt("New number: ");
	s->push_front(value);
	printList(s);
}

void popBackElement(LinkedList* list) {
	if (list->length < 1) {
		cout << endl << "LinkedList is empty..." << endl;
	}
	else {
		cout << endl << "Returned value: " << *(list->pop_back()) << endl;
		printList(list);
	}
}

void popFrontElement(LinkedList* list) {
	if (list->length < 1) {
		cout << endl << "LinkedList is empty..." << endl;
	}
	else {
		cout << endl << "Returned value: " << *(list->pop_front()) << endl;
		printList(list);
	}
}


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	while (mainMenu()) {
		LinkedList* list = new LinkedList();
		cout << endl << "Default LinkedList was created..." << endl;
		int value = 0;
		bool stop = false;
		while (!stop) {
			printMenu();

			int choice = inputInt(DEFAULT_PROMPT, 1, 9, true);

			switch (choice) {
			case 1: list = createNewList();  break;
			case 2: pushFrontLinkedList(list); break; // DONE
			case 3: pushBackLinkedList(list); break; // DONE
			case 4: popFrontElement(list); break;
			case 5: popBackElement(list); break;
			case 6: printList(list); break;
			case 7: printReverseList(list); break;
			case 8: list->swapMinMax(); printList(list); break;
			case 9: stop = true; break;
			}
		}
	}


	return 0;
}