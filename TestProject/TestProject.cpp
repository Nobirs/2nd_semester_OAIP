#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <limits>
#include <regex>

using namespace std;

struct Schedule
{
    string searchKey;
    string number;
    string plain;
    string destination;
    string time;
};

void File(const Schedule flights[], int count, const string& filename)
{
    ofstream file(filename);
    if (!file)
    {
        cout << "не получилось открыть фйдл;(" << endl;
        return;
    }
    else
    {
        if (file.is_open())
        {
            for (int i = 0; i < count; i++)
            {
                file << "номер рейса: " << flights[i].number << endl;
                file << "самолет: " << flights[i].plain << endl;
                file << "пункт назначения: " << flights[i].destination << endl;
                file << "время отправки: " << flights[i].time << endl;
            }
            file.close();
            cout << "данные записаны в файл" << endl;
        }
    }
}

void viewFile()
{
    ifstream file("flights.txt");
    if (file)
    {
        string line;
        while (getline(file, line))
        {
            cout << line << endl;
        }
        file.close();
    }
    else
    {
        cout << "не получилось открыть фйдл;(" << endl;
    }
}

void add(Schedule flights[], int& count)
{
    if (count >= 100)
    {
        cout << "колличество рейсов привышено" << endl;
        return;
    }

    Schedule flight;
    cout << "введите номер рейса: ";
    cin >> flight.number;
    cout << "введите вид самолета: ";
    cin >> flight.plain;
    cout << "введите пункт назначения: ";
    cin >> flight.destination;
    transform(flight.destination.begin(), flight.destination.end(), flight.destination.begin(), std::tolower);

    //cout << "введите время отпраки(часы:минуты): ";
    string timeString;
    //cin >> timeString;

    regex timeRegex("\\d{2}:\\d{2}");

    while (true) {
        cout << "введите время отправки (часы:минуты): ";
        string timeString;
        cin >> timeString;

        if (!regex_match(timeString, timeRegex)) {
            cout << "время введено неправильно. Повторите попытку." << endl;
            continue;
        }

        int hours = stoi(timeString.substr(0, 2));
        int minutes = stoi(timeString.substr(3, 2));

        if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59) {
            cout << "время введено неправильно. Повторите попытку." << endl;
            continue;
        }

        break;
    }
    cout << "\n\n";

    flight.time = timeString;

    flights[count] = flight;
    count++;

    cout << "рейс добавлен!" << endl;
}

void linearSearch(const Schedule flights[], int count, const string& destination)
{

    bool found = false;

    cout << "результаты поиска \"" << destination << "\":" << endl;

    for (int i = 0; i < count; i++)
    {
        if (flights[i].destination == destination)
        {
            cout << "номер рейса: " << flights[i].number << endl;
            cout << "вид самолета: " << flights[i].plain << endl;
            cout << "пункт назначения: " << flights[i].destination << endl;
            cout << "время отправки: " << flights[i].time << endl;
            cout << endl;
            found = true;
        }
    }

    if (!found)
    {
        cout << "рейсы не найдены" << endl;
    }
}

void selectionSort(Schedule flights[], int count)
{
    if (count <= 1)
    {
        cout << "слишком мало рейсов для сортировки" << endl;
        return;
    }
    for (int i = 0; i < count - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < count; j++)
        {
            if (flights[j].destination < flights[minIndex].destination)
            {
                minIndex = j;
            }
        }
        Schedule temp = flights[minIndex];
        flights[minIndex] = flights[i];
        flights[i] = temp;
    }
    cout << "массив рейсов отсортирован методом прямого выбора " << endl;
}

int binarySearch(const Schedule flights[], const int count, const string& searchKey)
{
    if (searchKey.empty())
    {
        cout << "ключ поиска не введен" << endl;
        return -1;
    }
    int left = 0;
    int right = count - 1;

    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (flights[mid].destination == searchKey)
        {
            return mid;
        }
        else if (flights[mid].destination < searchKey)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return -1;
}

void viewFlightsByDestination(Schedule flights[], int count, const string& destination)
{
    bool found = false;

    cout << "рейсы в пункт назначения \"" << destination << "\":" << endl;

    for (int i = 0; i < count; i++)
    {
        if (flights[i].destination == destination)
        {
            found = true;
            cout << "пункт назначения: " << flights[i].destination << endl;
            cout << "время отпраки: " << flights[i].time << endl;
        }
    }

    if (!found)
        cout << "нет рейсов в ваш пункт назначения." << endl;
}

int partition(Schedule flights[], int low, int high)
{
    string pivot = flights[high].destination;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (flights[j].destination < pivot)
        {
            i++;
            swap(flights[i], flights[j]);
        }
        else if (flights[j].destination == pivot && flights[j].time < flights[high].time)
        {
            i++;
            swap(flights[i], flights[j]);
        }
    }

    swap(flights[i + 1], flights[high]);
    return i + 1;
}

void quickSort(Schedule flights[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(flights, low, high);

        quickSort(flights, low, pi - 1);
        quickSort(flights, pi + 1, high);
    }
}

void quickSortWrapper(Schedule flights[], int count)
{
    if (count <= 1)
    {
        cout << "слишком мало рейсов для сортировки" << endl;
        return;
    }

    quickSort(flights, 0, count - 1);

    cout << "массив рейсов отсортирован методом QuickSort." << endl;
}

int main()
{
    setlocale(0, "rus");
    Schedule flights[100];
    int count = 0;
    while (1)
    {

        int q, m;
        cout << "введите номер:" << endl
            << "1 - запуск" << endl
            << "2 - выход" << endl;
        while (!(cin >> q) || cin.peek() != '\n')
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "неверный ввод" << endl;
            cout << "введите номер" << endl;
        }
        switch (q)
        {
        case 1:
            while (1)
            {
                cout << "1. добавить рейс" << endl;
                cout << "2. записать данные в файл" << endl;
                cout << "3. читать данные из файла" << endl;
                cout << "4. двоичный поиск" << endl;
                cout << "5. сортировка массива методами прямого выбора в порядке убывания и запись в файл с отсортированный массив" << endl;
                cout << "6. сортировка QuickSort в порядке возрастания" << endl;
                cout << "7. линейный поиск" << endl;
                cout << "8. выход" << endl;
                cout << "введите выбор: ";

                while (!(cin >> m) || cin.peek() != '\n')
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "неверный ввод " << endl;
                    cout << "Введите номер " << endl;
                }
                switch (m)
                {
                case 1:
                    cout << "введите данные рейса" << endl;
                    add(flights, count);
                    break;
                case 2:
                    File(flights, count, "flights.txt");
                    break;
                case 3:
                    viewFile();
                    break;
                case 4:
                    if (count > 0)
                    {
                        string destination;
                        cout << "введите пункт назначения для двоичного поиска: ";
                        cin >> destination;
                        if (destination.empty())
                        {
                            cout << "вы не ввели пункт назначения" << endl;
                            return 0;
                        }
                        int result = binarySearch(flights, count, destination);
                        viewFlightsByDestination(flights, count, destination);
                        if (result != -1)
                        {
                            cout << "найдено " << endl;
                        }
                        else
                        {
                            cout << "не найдено" << endl;
                        }
                    }
                    else
                    {
                        cout << "нет данных о рейсах" << endl;
                    }
                    break;
                case 5:
                    if (count > 0)
                    {
                        string destination;
                        cout << "\n\nвведите пункт назначения: ";
                        cin >> destination;
                        if (destination.empty())
                        {
                            cout << "вы не ввели пункт назначения" << endl;
                            return 0;
                        }
                        selectionSort(flights, count);
                        viewFlightsByDestination(flights, count, destination);
                        string filename = "sorted_flights.txt";
                        File(flights, count, filename);
                    }
                    else
                    {
                        cout << "нет данных о рейсах" << endl;
                    }
                    break;
                case 6:
                    if (count > 0)
                    {
                        string destination;
                        cout << "введите пункт назначения: ";
                        cin >> destination;
                        if (destination.empty())
                        {
                            cout << "вы не ввели пункт назначения" << endl;
                            return 0;
                        }
                        quickSortWrapper(flights, count);
                        viewFlightsByDestination(flights, count, destination);
                    }
                    else
                    {
                        cout << "нет данных о рейсах" << endl;
                    }
                    break;
                case 7:
                    if (count > 0)
                    {
                        string destination;
                        cout << "введите пункт назначения: ";
                        cin >> destination;
                        if (destination.empty())
                        {
                            cout << "вы не ввели пункт назначения" << endl;
                            return 0;
                        }
                        transform(destination.begin(), destination.end(), destination.begin(), ::tolower);
                        linearSearch(flights, count, destination);
                    }
                    else
                    {
                        cout << "недостаточно данных для поиска" << endl;
                        cout << "/n";
                    }
                    break;
                case 8:
                    return 0;
                default:
                    cout << "неверный ввод" << endl;
                    break;
                }
            };
            break;
        case 2:
            return 0;
            break;
        default:
            cout << "неверный ввод" << endl;
            break;
        }
    }

    return 0;
}
