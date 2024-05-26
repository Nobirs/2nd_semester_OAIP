#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <regex>
#include <ctime>
#include <chrono>
#include <iomanip>



using std::string;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::regex;
using std::smatch;
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


inline int getCurrentYear() {
	time_t now = std::time(nullptr);
	std::tm timeinfo;
	localtime_s(&timeinfo, &now);
	int year = timeinfo.tm_year + 1900;
	return year;
}

inline int getCurrentMonth() {
	time_t now = std::time(nullptr);
	std::tm timeinfo;
	localtime_s(&timeinfo, &now);
	int month = timeinfo.tm_mon + 1;
	return month;
}

inline int getCurrentDay() {
	time_t now = std::time(nullptr);
	std::tm timeinfo;
	localtime_s(&timeinfo, &now);
	int day = timeinfo.tm_mday + 1;
	return day;
}

inline string inputDate(string prompt, bool beEmpty = false) {
	static const regex re("\\b(0[1-9]|1[0-9]|2[0-9]|3[01])\\.(0[1-9]|1[012])\\.(\\d{4})\\b");
	while (true)
	{
		cout << prompt;
		string str;
		smatch match;
		std::getline(cin, str);
		if (str.empty() and beEmpty) return str;
		else if (str.empty() and !beEmpty)
		{
			cout << "Ошибка. Вы ввели пустую строку!" << endl;
			continue;
		}
		else if (regex_match(str, match, re))
		{
			if (stoi(str.substr(str.length() - 4)) > getCurrentYear())
			{
				cout << "Ошибка. Введенный год больше нынешнего!" << endl;
				continue;
			}
			if (stoi(str.substr(str.length() - 4)) == getCurrentYear() and stoi(str.substr(3, 5)) > getCurrentMonth())
			{
				cout << "Ошибка. Введенный месяц больше нынешнего!" << endl;
				continue;
			}
			if ((stoi(str.substr(str.length() - 4)) == getCurrentYear() and stoi(str.substr(3, 5)) == getCurrentMonth()) and stoi(str.substr(0, 2)) > getCurrentDay())
			{
				cout << "Ошибка. Введенный день больше нынешнего!" << endl;
				continue;
			}
			return str;
		}
		cerr << "Некорректный ввод" << endl;
	}
}