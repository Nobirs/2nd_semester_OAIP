#pragma once
#include <iostream>
#include <string>

using std::string;
using std::ostream;
using std::istream;
using std::getline;
using std::stoi;
using std::cout;


class Employee {
private:
    string fullName;
    int employeeId;
    int hoursWorked;
    double hourlyRate;
    double salary;

public:
    Employee() : fullName("default"), employeeId(0), hoursWorked(0), hourlyRate(0.0), salary(0.0) {}

    Employee(const string& _fullName, int _employeeId, int _hoursWorked, double _hourlyRate)
        : fullName(_fullName), employeeId(_employeeId), hoursWorked(_hoursWorked), hourlyRate(_hourlyRate) {
        calculateSalary();
    }

    // Getters
    string getFullName() const { return fullName; }
    int getEmployeeId() const { return employeeId; }
    int getHoursWorked() const { return hoursWorked; }
    double getHourlyRate() const { return hourlyRate; }
    double getSalary() { 
        calculateSalary();
        return salary; }

    // Setters
    void setFullName(const string& _fullName) { fullName = _fullName; }
    void setEmployeeId(int _employeeId) { employeeId = _employeeId; }
    void setHoursWorked(int _hoursWorked) {
        hoursWorked = _hoursWorked;
        calculateSalary();
    }
    void setHourlyRate(double _hourlyRate) {
        hourlyRate = _hourlyRate;
        calculateSalary();
    }


    friend std::ostream& operator<<(std::ostream& os, const Employee& employee) {
        os << employee.fullName << "\n";
        os << employee.employeeId << "\n";
        os << employee.hoursWorked << "\n";
        os << employee.hourlyRate << "\n";
        os << employee.salary << "\n";
        return os;
    }

    friend istream& operator>>(istream& is, Employee& employee) {
        try {
            string buffer;
            getline(is, buffer);
            employee.fullName = buffer;
            buffer.clear();

            getline(is, buffer);
            employee.employeeId = stoi(buffer);
            buffer.clear();

            getline(is, buffer);
            employee.hoursWorked = stoi(buffer);
            buffer.clear();

            getline(is, buffer);
            employee.hourlyRate = stod(buffer);
            buffer.clear();

            getline(is, buffer);
            employee.salary = stod(buffer);
            buffer.clear();
        }
        catch (std::exception& e){
            std::cerr << std::endl << "Файл считан до конца..." << std::endl;
            employee = Employee();
            employee.employeeId = -1;
        }
        return is;
    }

    friend void addToFile(string fileName);

    void printEmployee() {
        cout << std::endl << "*****************************" << std::endl;
        cout << "ФИО: " << this->fullName << "\n";
        cout << "Табельный номер: " << this->employeeId << "\n";
        cout << "Проработано часов: " << this->hoursWorked << "\n";
        cout << "Почасовая ставка: " << this->hourlyRate << "\n";
        cout << "Зарплата: " << this->salary << "\n";
    }

private:
    void calculateSalary() {
        int extraHours = this->hoursWorked - 144;
        if (extraHours > 0) {
            salary = 144 * hourlyRate + extraHours * (2 * hourlyRate);
        }
        else {
            salary = hoursWorked * hourlyRate;
        }
        salary = salary * 0.88; // TOTHINK: add another field without "income tax"
    }
};
