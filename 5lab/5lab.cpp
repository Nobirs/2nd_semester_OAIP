#include <iostream>
#include <fstream>
#include <iomanip>
#include <Windows.h>
#include <filesystem>
#include <vector>


#include "Employee.h"
#include "inputFunctions.h"

using namespace std;
namespace fs = std::filesystem;


string readLine(string prompt) {
    cout << prompt;
    string buffer;
    getline(cin, buffer);
    return buffer;
}

void createFile(string fileName) {
    if (fs::exists(fileName)) {
        int choice = inputYesNo("Файл уже существует. Перезаписать его[y/n]?");
        if (choice == 1) {
            fstream* file = new fstream(fileName, ios::out);
            if (file->is_open()) {
                cout << "File was created. " << endl;
                file->close();
            }
            else {
                cout << "[ERROR] Fail to create file..." << endl;
            }
            delete file;
        }
    }
}


void printFile(string fileName) {
    if (!fs::exists(fileName)) {
        cout << "[ERROR] Файл не существует." << endl;
    }
    else {
        fstream file(fileName, ios::in);
        if (file.is_open()) {
            Employee e;
            cout << "Содержимое файла:" << endl;
            while (file >> e) {
                e.printEmployee();
            }
            file.close();
        }
        else {
            cout << "[ERROR] File not opened" << endl;
        }
    }
    return;
}

void addToFile(string fileName) {
    if (!fs::exists(fileName)) {
        cout << "[ERROR] Файл не существует." << endl;
    }
    else {
        fstream file(fileName, ios::app);
        if (file.is_open()) {
            Employee e;
            e.fullName = readLine("Full name: ");
            e.employeeId = inputInt("Employee Id:", 0, INT_MAX, true);
            e.hoursWorked = inputInt("Hours worked: ", 0, INT_MAX, true);
            e.hourlyRate = inputDouble("Hourly rate: ", 0, INT_MAX, true);
            e.calculateSalary();
            file << e;
            file.close();
        }
        else {
            cout << "[ERROR] File not opened" << endl;
        }
    }
    return;
}




// Функция для разделения массива на подмассивы и определения опорного элемента
int partition(vector<Employee>& arr, int low, int high) {
    Employee pivot = arr[high];  // Опорный элемент
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].getSalary() < pivot.getSalary()) {
            i++;
            Employee temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    Employee temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

// Функция для сортировки массива методом быстрой сортировки
void quickSort(vector<Employee>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  // Индекс опорного элемента

        quickSort(arr, low, pi - 1);  // Рекурсивная сортировка элементов меньше опорного
        quickSort(arr, pi + 1, high);  // Рекурсивная сортировка элементов больше опорного
    }
}

bool compareStrings(string str1, string str2)
{
    if (str1.length() != str2.length()) return false;
    for (int i = 0; i < str1.length(); i++)
    {
        if (std::toupper(str1[i]) != std::toupper(str2[i])) {
            return false;
        }
    }
    return true;
}


void linearSearch(string fileName) {
    if (!fs::exists(fileName)) {
        cout << "[ERROR] Файл не существует." << endl;
    }
    else {
        fstream file(fileName, ios::in);
        if (file.is_open()) {
            Employee e;
            string nameToFind = readLine("Input name to find: ");
            bool wasFound = false;
            while (file >> e) {
                if (compareStrings(e.getFullName(), nameToFind)) {
                    cout << "Совпадение найдено:" << endl;
                    e.printEmployee();
                    wasFound = true;
                }
            }
            if(!wasFound) cout << "Совпадений не найдено..." << endl;
            file.close();
        }
    }
}


void printArray(vector<Employee>& arr) {
    for (auto e : arr) {
        e.printEmployee();
    }
}


void selectionSort(string fileName) {
    if (!fs::exists(fileName)) {
        cout << "[ERROR] Файл не существует." << endl;
    }
    else {
        fstream file(fileName, ios::in);
        if (file.is_open()) {
            vector<Employee> arr;
            Employee e;
            while (file >> e) {
                if (e.getEmployeeId() != -1) arr.push_back(e);
                else break;
            }
            if (arr.size() == 0)
            {
                cout << "Файл пустой!" << endl;
                return;
            }
            cout << "--------------Before---------------";
            printArray(arr);
            // ------------Sort----------------------
            for (int i = 0; i < arr.size() - 1; i++) {
                int minIndex = i;
                for (int j = i + 1; j < arr.size(); j++) {
                    if (arr[j].getSalary() < arr[minIndex].getSalary()) {
                        minIndex = j;
                    }
                }
                Employee temp = arr[i];
                arr[i] = arr[minIndex];
                arr[minIndex] = temp;
            }
            // --------------------------------------
            cout << "-------------After----------------";
            printArray(arr);

            file.close();
            // Open file to write--------------------
            file.open(fileName, ios::out);
            // -------Print to file------------------
            if(file.is_open())
            {
                for (auto e : arr) {
                    file << e;
                }
            }
            file.close();
        }
    }
}


vector<Employee> vectorFromFile(string fileName) {
    vector<Employee> arr;
    if (!fs::exists(fileName)) {
        cout << "[ERROR] Файл не существует." << endl;
    }
    else {
        fstream file(fileName, ios::in);
        if (file.is_open()) {
            Employee e;
            while (file >> e) {
                if (e.getEmployeeId() != -1) arr.push_back(e);
                else break;
            }
            file.close();
        }
    }
    return arr;
}

void vectorToFile(vector<Employee>& arr, string fileName) {
    if (!fs::exists(fileName)) {
        cout << "[ERROR] Файл не существует." << endl;
    }
    else {
        fstream file(fileName, ios::out);
        if (file.is_open()) {
            for (auto e : arr)
            {
                file << e;
            }
            file.close();
        }
        else cout << "[ERROR] Can't open a file..." << endl;
    }
}


void quickSort(string fileName) {
    vector<Employee> arr = vectorFromFile(fileName);
    if (arr.size() == 0)
    {
        cout << "Нет данных для сортировки!" << endl;
        return;
    }
    cout << std::endl << "-----------------Before--------------" << std::endl;
    printArray(arr);
    quickSort(arr, 0, arr.size() - 1);
    cout << std::endl << "-----------------After---------------" << std::endl;
    printArray(arr);
    vectorToFile(arr, fileName);
    return;
}


int binarySearchRecursive(vector<Employee>& arr, int low, int high, double target) {
    if (low <= high) {
        int mid = low + (high - low) / 2;

        // Если элемент найден, возвращаем его индекс
        if (arr[mid].getSalary() == target) {
            return mid;
        }
        // Если искомый элемент меньше значения в середине массива, ищем в левой половине
        else if (arr[mid].getSalary() > target) {
            return binarySearchRecursive(arr, low, mid - 1, target);
        }
        // Иначе ищем в правой половине
        else {
            return binarySearchRecursive(arr, mid + 1, high, target);
        }
    }

    // Если элемент не найден, возвращаем -1
    return -1;
}

void binarySearch(string fileName) {
    double salary = inputDouble("Input salary to find: ", 0, INT_MAX, true);
    vector<Employee> arr = vectorFromFile(fileName);
    if (arr.size() == 0)
    {
        cout << "Файл пустой!" << endl;
        return;
    }
    quickSort(arr, 0, arr.size() - 1);
    int index = binarySearchRecursive(arr, 0, arr.size() - 1, salary);
    if (index == -1) {
        cout << endl << "Employee not found" << endl;
        return;
    }
    else {
        cout << endl << "Employee was found: " << endl;
        arr[index].printEmployee();
        return;
    }
}


int printMenu() {
    cout << "**************************************************" << endl;
    cout << "*                   Меню                         *" << endl;
    cout << "**************************************************" << endl;
    cout << "* 1. Создание файла                              *" << endl;
    cout << "* 2. Просмотр файла                              *" << endl;
    cout << "* 3. Добавление в файл                           *" << endl;
    cout << "* 4. Линейный поиск                              *" << endl;
    cout << "* 5. Сортировка (прямой выбор)                   *" << endl;
    cout << "* 6. Сортировка (QuickSort)                      *" << endl;
    cout << "* 7. Двоичный поиск                              *" << endl;
    cout << "* 8. Зарплаты                                    *" << endl;
    cout << "* 9. Выход                                       *" << endl;
    cout << "**************************************************" << endl;
    int choice = inputInt("Выберите пункт меню: ", 1, 9, true);
    return choice;
}

void printSalary(string fileName) {
    vector<Employee> arr = vectorFromFile(fileName);
    if (!arr.empty())
    {
        for (auto emp : arr)
        {
            cout << emp.getFullName() << " -> " << emp.getSalary() << endl;
        }
    }
    else
    {
        cout << "Файл пустой!" << endl;
    }

}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string fileName = "employees.txt";
    //vector<Employee> employees;

    while (inputYesNo("Do you wanna start program[y/n]?")) {
        bool flag = true;
        while (flag) {
            switch (printMenu()) {
            case 1: createFile(fileName); break;
            case 2: printFile(fileName); break;
            case 3: addToFile(fileName); break;
            case 4: linearSearch(fileName); break;
            case 5: selectionSort(fileName); break;
            case 6: quickSort(fileName); break;
            case 7: binarySearch(fileName); break;
            case 8: printSalary(fileName); break;
            case 9: flag = false; break;
            }
        }
    }
    

    return 0;
}