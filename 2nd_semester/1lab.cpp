#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <Windows.h>

using namespace std;

int step = 0;

float sinFunc(float x) {
    return 7.0 * pow(sin(x), 2);
}

double round_to(double value, double precision = 1.0)
{
    return std::round(value / precision) * precision;
}

bool correctDoubleStr(string &str) {
    int digits = 0;
    int dots = 0;
    for (int i = 0; i < str.length(); i++) {
        if (isdigit(str[i])) {
            digits++;
        }
        else if (str[i] == '.' || str[i] == ',') {
            if (str[i] == ',') str[i] = '.';
            dots++;
            if (dots > 1) {
                return false;
            }
        }
    }
    if (digits + dots == str.length()) {
        return true;
    }
    else  return false;

}

float inputDouble(string &str) {
    float epsilon;
    bool successInput = false;
    while (!successInput) {
        cout << "Enter epsilon(<1): "; 
        cin >> str;
        if (str.length() > 0 and correctDoubleStr(str)) {
            epsilon = stof(str);
            if (epsilon > 1) {
                cout << "Incorrect epsilon ->" << str << endl;
                continue;
            }
            successInput = true;
        }
        else {
            cout << "Incorrect epsilon ->" << str << endl;
        }
    }
    cout << "Epsilon: " << epsilon << endl;
    return epsilon;
}

vector<float> noRecursiveBisectionMethod(float begin, float end, float eps, float delt) {
    float diff = end - begin;
    while (round_to(diff, eps) > eps) {
        float x = (end + begin) / 2;
        float x1 = (begin + end - delt) / 2.0;
        float x2 = (begin + end + delt) / 2.0;
        if (sinFunc(x1) < sinFunc(x2)) {
            end = x;
        }
        else
        {
            begin = x;
        }
        diff = end - begin;
        cout << "a: " << begin << " b: " << end << endl;
    }

    float x = (end + begin) / 2;
    vector<float> result = { x, sinFunc(x) };
    return result;
}


vector<float> bisectionMethod(float begin, float end, float eps, float delt) {
    float diff = end - begin;
    if (round_to(diff, eps / 10) <= eps) {
        float x = (end + begin) / 2.0;
        vector<float> result = { x, sinFunc(x) };
        return result;
    }
    else {
        float x = (end + begin) / 2.0;
        float x1 = (begin + end - delt) / 2.0;
        float x2 = (begin + end + delt) / 2.0;
        step++;
        cout << "Step: " << step << "  Func(x1) = " << sinFunc(x1) << " Func(x2) = " << sinFunc(x2) << " begin: " << begin << " end: " << end << endl;
        if (sinFunc(x1) < sinFunc(x2)) return bisectionMethod(begin, x, eps, delt);
        else return bisectionMethod(x, end, eps, delt);
    }
}



int lab1()
{
    int min = 2, max = 6;
    float epsilon = 0.001;
    string str;
    vector<float> result;
    epsilon = inputDouble(str);

    cout << "Choose method:\n1.recursive\n2.no recursive\n>>";
    int choice = 0;
    cin >> choice;
    switch (choice) {
        case 1: result = bisectionMethod(min, max, epsilon, epsilon); break;
        case 2: result = noRecursiveBisectionMethod(min, max, epsilon, epsilon); break;
        default: cout << "Incorrect input";
    }
    cout << "Result: " << result[0] << " -> " << result[1] << endl;
    return 0;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    while (true) {
        cout << endl << "Выполнить программу(y/n):";
        char answer;
        cin >> answer;
        switch (answer) {
        case 'y': lab1(); break;
        case 'n': return 0;
        }
    }
}
