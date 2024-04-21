#pragma once
#include <string>
#include <tuple>
#include <vector>
#include <stdexcept>

using std::string;
using std::tuple;
using std::vector;

template<typename T>
struct StackElem {
    T value;
    StackElem* next;
};

template<typename T>
class Stack {
private:
    int length;
    StackElem<T>* first;

public:
    Stack() : length(0), first(nullptr) {}
    ~Stack() { clear(); }

    void push(T value) {
        StackElem<T>* elem = new StackElem<T>();
        elem->value = value;
        elem->next = first;
        first = elem;
        length++;
    }
    T top() const {
        return first->value;
    }
    T pop() {
        T value;
        if (first) {
            value = first->value;
            StackElem<T>* elem = first;
            first = first->next;
            delete elem;
            length--;
        }
        return value;
    }
    int clear() {
        while (first != nullptr) {
            StackElem<T>* current = first;
            first = first->next;
            delete current;
        }
        length = 0;
        return 0;
    }
    T* toArray() const {
        T* arr = new T[length];
        StackElem<T>* ptr = first;
        for (int i = 0; i < length; i++, ptr = ptr->next) {
            arr[i] = ptr->value;
        }
        return arr;
    }
    int getLength() const { return length; }

    void sortByPointers() {
        push(0);
        StackElem* t = nullptr, * t1, * r;
        if (first->next->next == nullptr) return;
        do {
            for (t1 = first; t1->next->next != t; t1 = t1->next)
                if (t1->next->value > t1->next->next->value) {
                    r = t1->next->next;
                    t1->next->next = r->next;
                    r->next = t1->next;
                    t1->next = r;
                }
            t = t1->next;
        } while (first->next->next != t);
        pop();
    }
    void sortByValues() {
        StackElem<T>* t = nullptr, * t1;
        T r;
        do {
            for (t1 = first; t1->next != t; t1 = t1->next)
                if (t1->value > t1->next->value) {
                    r = t1->value;
                    t1->value = t1->next->value;
                    t1->next->value = r;
                }
            t = t1;
        } while (first->next != t);
    }
};



bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Функция для выполнения операции над двумя операндами и оператором
double applyOperator(double operand1, double operand2, char op) {
    switch (op) {
    case '+': return operand1 + operand2;
    case '-': return operand1 - operand2;
    case '*': return operand1 * operand2;
    case '/': return operand1 / operand2;
    default: return 0; // Обработка ошибки
    }
}

double evaluateRPN(string expression, vector<tuple<char, double>> values) {

    Stack<double> operands;
    char token;

    for (int i = 0; i < expression.length(); i++) {
        token = expression[i];
        // Если токен - операнд, помещаем его в стек
        if (!isOperator(token)) {
            bool found = false;
            for (auto tpl : values)
            {
                if (std::get<char>(tpl) == token)
                {
                    operands.push(std::get<double>(tpl));
                    found = true;
                    break;
                }
            }
            if(!found) throw gcnew System::Exception("Operand Value missing: " + token.ToString());
        }
        else {
            // Если токен - оператор, извлекаем из стека два операнда, выполняем операцию и помещаем результат обратно в стек
            double operand2 = operands.pop();
            double operand1 = operands.pop();
            operands.push(applyOperator(operand1, operand2, token));
        }
    }

    // В конце вычислений в стеке должен остаться только один элемент - результат выражения
    return operands.pop();
}

int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

string infixToRPN(const string& inputStr) {
    Stack<char> operatorStack;
    string outputList;

    for (char input : inputStr) {
        if (isalnum(input)) {
            outputList += input;
        }
        else if (input == '(') {
            operatorStack.push(input);
        }
        else if (input == ')') {
            while (operatorStack.getLength() && operatorStack.top() != '(') {
                outputList += operatorStack.pop();
            }
            operatorStack.pop(); // remove '(' from stack
        }
        else if (isOperator(input)) {
            while (operatorStack.getLength() && getPrecedence(operatorStack.top()) >= getPrecedence(input)) {
                outputList += operatorStack.pop();
            }
            operatorStack.push(input);
        }
    }

    while (operatorStack.getLength()) {
        outputList += operatorStack.pop();
    }

    return outputList;
}