#include <iostream>
#include <list>
#include <vector>
#include <iterator>
#include <Windows.h>

#include "input.h"

using std::istream;
using std::ostream;
using std::string;
using std::vector;
using std::list;
using std::cout;
using std::endl;


struct Product
{
    string name;
    double price;
    string date;

    friend istream& operator>>(istream& is, Product& p)
    {
        cout << "Name: ";
        std::getline(cin, p.name);
        p.price = inputDouble("Price: ", 0, MAXINT, true);
        p.date = inputDate("Date: ");
        return is;
    }

    friend ostream& operator<<(ostream& os, Product& p)
    {
        os << "--------------------------" << endl;
        os << "Name: " << p.name << endl;
        os << "Price: " << p.price << endl;
        os << "Date: " << p.date << endl;
        return os;
    }
};


class ProductHashTable {
private:
    vector<list<Product>> table;
    int size;

    int hashFunction(double key) {
        // Простейшая хеш-функция для демонстрации
        return static_cast<int>(key) % size;
    }

public:
    ProductHashTable(int tableSize) : size(tableSize) {
        table.resize(size);
    }

    void insert(const Product& product) {
        int index = hashFunction(product.price);
        table[index].push_back(product);
    }

    bool search(double price, vector<Product>& foundProducts) {
        int index = hashFunction(price);
        bool wasFound = false;
        for (const auto& product : table[index]) {
            if (product.price == price) {
                foundProducts.push_back(product);
                wasFound = true;
            }
        }
        return wasFound;
    }

    void remove(double price) {
        int index = hashFunction(price);
        auto& products = table[index];
        for (auto it = products.begin(); it != products.end(); ++it) {
            if (it->price == price) {
                products.erase(it);
                return;
            }
        }
    }

    void display() {
        for (int i = 0; i < size; ++i) {
            cout << "Bucket " << i << ":" << endl;
            for (auto& product : table[i]) {
                cout << product;
            }
        }
    }
};


class HashTable {
private:
    vector<list<int>> table;
    int size;

    int hashFunction(int key) {
        return key % size;
    }

public:
    HashTable(int tableSize) : size(tableSize) {
        table.resize(size);
    }

    void insert(int key) {
        int index = hashFunction(key);
        table[index].push_back(key);
    }

    bool search(int key) {
        int index = hashFunction(key);
        for (int element : table[index]) {
            if (element == key) {
                return true;
            }
        }
        return false;
    }

    void remove(int key) {
        int index = hashFunction(key);
        table[index].remove(key);
    }

    void display() {
        for (int i = 0; i < size; ++i) {
            cout << "Bucket " << i << ": ";
            for (int element : table[i]) {
                cout << element << " ";
            }
            cout << endl;
        }
    }
};

template<typename T>
void printArray(vector<T> arr, int size)
{
    if (size == 0)
    {
        cout << "Array is empty!" << endl;
        return;
    }
    cout << "---------------------------------------------" << endl;
    cout << "Array: " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << "arr[" + std::to_string(i) + "] = " << arr[i] << endl;
    }
    cout << "---------------------------------------------" << endl;
}


void task1()
{
    int n = inputInt("Введите размер массива[n>0]: ", 0, MAXINT, true);
    if (n == 0)
    {
        cout << "Нечего вводить - нечего делать.";
        return;
    }
    else
    {
        vector<int> arr;
        int shouldRand = inputInt("Заполнить рандомно[1-да/2-нет]? ", 1, 2, true);
        if (shouldRand)
        {
            for (int i = 0; i < n; i++)
            {
                int number = rand() % (54000 - 24000) + 30000;
                arr.push_back(number);
            }
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                int number = inputInt("Введите число из заданного диапазона(24000-54000) -> ", 24000, 54000, true);
                arr.push_back(number);
            }
        }

        vector<int> copy_arr = arr;
        int M = inputInt("Введите размер Hash-таблицы: ", 1, MAXINT, true);

        HashTable table(M);
        shouldRand = inputInt("Заполнить рандомно из массива[1-да/2-нет]? ", 1, 2, true);
        if (shouldRand)
        {
            for (int i = 0; i < M; i++)
            {
                int number = rand() % copy_arr.size();
                table.insert(copy_arr[number]);
                copy_arr.erase(copy_arr.begin() + number);
            }
        }
        else
        {
            while (M > 0)
            {
                printArray<int>(copy_arr, copy_arr.size());
                int index = inputInt("Индекс элемента, который будет добавлен в хеш-таблицу: ", 0, copy_arr.size() - 1, true);
                table.insert(copy_arr[index]);
                copy_arr.erase(copy_arr.begin() + index);
                --M;
            }
        }
        table.display();

        bool exit = false;
        while (!exit)
        {
            cout << "1. Вывести массив" << endl;
            cout << "2. Вывести хеш-таблицу" << endl;
            cout << "3. Поиск в хеш-таблице" << endl;
            cout << "4. Выход" << endl;

            int choice = inputInt(">>", 1, 4, true);
            switch (choice)
            {
            case 1: printArray<int>(arr, arr.size()); break;
            case 2: table.display(); break;
            case 3:
            {
                int element = inputInt("Введите элемент, который нужно найти: ");
                bool wasFound = table.search(element);
                if (wasFound) cout << "Элемент найден: " << element << endl;
                else cout << "Такого элемента в таблице нет" << endl;
                break;
            }
            case 4: exit = true; break;

            }
        }
    }
}


void task2()
{
    int n = inputInt("Введите размер массива[n>0]: ", 0, MAXINT, true);
    if (n == 0)
    {
        cout << "Нечего вводить - нечего делать.";
        return;
    }
    else
    {
        vector<Product> arr;
        for (int i = 0; i < n; i++)
        {
            Product p;
            cin >> p;
            arr.push_back(p);
        }
        

        vector<Product> copy_arr = arr;
        int M = inputInt("Введите размер Hash-таблицы: ", 1, MAXINT, true);

        ProductHashTable table(M);
        bool shouldRand = inputInt("Заполнить рандомно из массива[1-да/2-нет]? ", 1, 2, true);
        if (shouldRand)
        {
            for (int i = 0; i < M; i++)
            {
                int number = rand() % copy_arr.size();
                table.insert(copy_arr[number]);
            }
        }
        else
        {
            while (M > 0)
            {
                printArray<Product>(copy_arr, copy_arr.size());
                int index = inputInt("Индекс элемента, который будет добавлен в хеш-таблицу: ", 0, copy_arr.size() - 1, true);
                table.insert(copy_arr[index]);
                --M;
            }
        }
        table.display();

        bool exit = false;
        while (!exit)
        {
            cout << "1. Вывести массив" << endl;
            cout << "2. Вывести хеш-таблицу" << endl;
            cout << "3. Поиск в хеш-таблице" << endl;
            cout << "4. Выход" << endl;

            int choice = inputInt(">>", 1, 4, true);
            switch (choice)
            {
            case 1: printArray<Product>(arr, arr.size()); break;
            case 2: table.display(); break;
            case 3:
            {
                double price = inputDouble("Введите цену, по который нужно найти продукт: ");
                // TODO: find all products and display them
                vector<Product> found;
                bool wasFound = table.search(price, found);
                if (wasFound)
                {
                    cout << "Элементы найдены" << endl;
                    printArray<Product>(found, found.size());
                }
                else cout << "Таких элементов в таблице нет" << endl;
                break;
            }
            case 4: exit = true; break;

            }
        }
    }
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    while (inputYesNo("Start program[y/n]?"))
    {
        cout << "1. Task1 " << endl;
        cout << "2. Task2 " << endl;
        cout << "3. Exit " << endl;
        int choice = inputInt(">> ", 1, 3, true);
        switch (choice)
        {
        case 1: task1(); break;
        case 2: task2(); break;
        case 3: break;
        }
    }


    return 0;
}