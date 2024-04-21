#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <regex>
#include <Windows.h>
#include "stack.h"

using namespace std;

#define DEFAULT_PROMPT ">>>"


void printSeparator() {
	cout << endl << "--------------------------------------------------" << endl;
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
			if (checkBetween && (value >= from) && (value <= to)) return value;
		}
		cerr << "неправильно, попробуйте ещё..." << endl;
	}
}


string inputYesNo(string prompt) {
	static const regex re(R"((да|нет|Да|Нет))"s);
	while (true) {
		string input;
		smatch match;
		cout << prompt;
		getline(cin, input);
		if (regex_match(input, match, re))
		{
			return input;
		}
		else
		{
			cerr << "неправильно, попробуйте ещё..." << endl;
		}
	}
}


bool mainMenu() {
	string choice = inputYesNo("запустить программу[да/нет]? ");
	if (choice == "да" or choice == "Да") {
		return true;
	}
	else return false;
	/*switch (choice) {
	case 'д': return true;
	case 'н': return false;
	default: return false;*/
	//}
}

void printMenu() {
	printSeparator();
	cout << "меню:" << endl;
	cout << "1.создать стек" << endl;
	cout << "2.добавить элемент(push)" << endl;
	cout << "3.вывести стек" << endl;
	cout << "4.сортировка" << endl;
	cout << "5.разделить на четные и нечетные" << endl;
	cout << "6.удалить элемент(pop)" << endl;
	cout << "7.выйти" << endl;
	//cout << ">>> ";
}


void sortMenu() {
	cout << "как сортировать: " << endl;
	cout << "1.по адресу" << endl;
	cout << "2.по значению" << endl;
	//cout << ">>> ";
}

void fillStackByRandomNumbers(Stack* s) {
	int numbers = inputInt("сколько чисел: ", 1, 1000, true);
	for (int i = 0; i < numbers; i++) {
		s->push(rand() % 100);
	}
}

Stack* createNewStack() {
	Stack* s = new Stack();
	string choice = inputYesNo("заполнить случайно[да/нет]?");
	if (choice == "да" or choice == "Да") {
		fillStackByRandomNumbers(s);
		printStack(s);
	}
	return s;
}


void pushToStack(Stack* s) {
	int value = inputInt("число: ");
	s->push(value);
}


void sortStack(Stack* myStack) {
	cout << endl << "было: ";
	printStack(myStack);
	sortMenu();
	int choice = inputInt(DEFAULT_PROMPT, 1, 2, true);
	switch (choice) {
	case 1: myStack->sortByPointers(); break;
	case 2: myStack->sortByValues(); break;
	default: cout << "неправильный ввод" << endl;
	}
	cout << endl << "стало: ";
	printStack(myStack);
}

void popElement(Stack* myStack) {
	if (myStack->getLength() < 1) {
		cout << endl << "стек пустой..." << endl;
	}
	else {
		cout << endl << "вернуло: " << myStack->pop() << endl;
	}
}



int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "привет" << endl;
	srand(time(NULL));
	while (mainMenu()) {
		Stack* myStack = new Stack();
		Stack odd, even, newStack;
		int stop = false;
		while (!stop) {
			printMenu();

			int choice = inputInt(DEFAULT_PROMPT, 1, 7, true);

			switch (choice) {
			case 1: myStack = createNewStack();  break;
			case 2: pushToStack(myStack); break; // DONE
			case 3: printStack(myStack); break; // DONE
			case 4: sortStack(myStack); break; // DONE
			case 5:
			{
				int len = myStack->getLength();
				for (int i = 0; i < len; i++) {
					int val = myStack->pop();
					if (val % 2 == 0) even.push(val);
					else odd.push(val);
					newStack.push(val);
				}
				myStack = &newStack;
				cout << "четные:" << endl;
				printStack(&even);
				cout << "нечетные:" << endl;
				printStack(&odd);
				cout << "исходный стек:" << endl;
				printStack(myStack);
				break;
			}
			case 6: popElement(myStack); break;
			case 7: stop = true; break;
			}
		}
	}


	return 0;
}