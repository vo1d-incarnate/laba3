#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

struct University {
    int id;              // уникальный ID
    string professor;    // преподаватель
    string kafedra;      // кафедра
    string subject;      // предмет
    int hours;           // количество часов
    int experience;      // опыт работы
    float stavka;        // ставка
};

University* universities = nullptr; // динамический массив
int arraySize = 0;                  // текущее количество элементов
int arrayCapacity = 0;              // ёмкость массива

void push_back(University university) {
    if (arraySize >= arrayCapacity) {
        arrayCapacity = (arrayCapacity == 0) ? 1 : arrayCapacity * 2;
        University* newUniversities = new University[arrayCapacity];
        for (int i = 0; i < arraySize; i++) {
            newUniversities[i] = universities[i];
        }
        delete[] universities;
        universities = newUniversities;
    }
    universities[arraySize++] = university;
}

void freeMemory() {
    delete[] universities;
    universities = nullptr;
    arraySize = 0;
    arrayCapacity = 0;
}

bool readDataFromFile(const string &filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        do {
            cout << '\n' << "Press the Enter key to continue.";
        } while (cin.get() != '\n');
        return false;
    }

    University university;
    while (file >> university.id) {
        file.ignore();
        getline(file, university.professor);
        getline(file, university.kafedra);
        getline(file, university.subject);
        file >> university.hours >> university.experience >> university.stavka;
        file.ignore();
        push_back(university);
    }
    file.close();
    return true;
}

void displayAllHours() {
    system("clear");
    int sum = 0;
    for (int i = 0; i < arraySize; i++) {
        sum += universities[i].hours;
    }
    cout << "Всего " << sum << " учебных часов" << endl;
    do {} while (cin.get() != '\n');
}

void displayAllStavka() {
    system("clear");
    int sum = 0;
    for (int i = 0; i < arraySize; i++) {
        if (universities[i].stavka >= 1.0) {
            sum ++;
        }
    }
    cout << "Всего " << sum << " полных ставок" << endl;
    do {} while (cin.get() != '\n');
}

void displayData() {
    system("clear");
    int widths[7] = {5, 25, 25, 25, 10, 15, 10};
    cout << "+";
    for (const auto& width : widths) {
        cout << setfill('-') << setw(width) << "" << "+";
    }
    cout << setfill(' ') << "\n";
    string headers[7] = {"ID", "Professor", "Kafedra", "Subject", "Hours", "Experience", "Stavka"};
    cout << "|";
    for (size_t i = 0; i < 7; i++) {
        cout << setw(widths[i]) << headers[i] << "|";
    }
    cout << "\n";

    cout << "+";
    for (const auto& width : widths) {
        cout << setfill('-') << setw(width) << "" << "+";
    }
    cout << setfill(' ') << "\n";
    for (int i = 0; i < arraySize; i++) {
        const auto& university = universities[i];
        cout << "|";
        cout << setw(widths[0]) << university.id << "|"
             << setw(widths[1]) << university.professor << "|"
             << setw(widths[2]) << university.kafedra << "|"
             << setw(widths[3]) << university.subject << "|"
             << setw(widths[4]) << university.hours << "|"
             << setw(widths[5]) << university.experience << "|"
             << setw(widths[6]) << university.stavka << "|\n";
        cout << "+";
        for (const auto& width : widths) {
            cout << setfill('-') << setw(width) << "" << "+";
        }
        cout << setfill(' ') << "\n";
    }

    do {

    } while (cin.get() != '\n');
}



void editData(int id) {
    bool isEnd0 = false;
    bool isEnd1 = false;
    bool isEnd2 = false;
    bool isEnd3 = false;
    int countSuccess = 0;


    system("clear");
    for (int i = 0; i < arraySize; i++) {
        countSuccess = 0;
            if (universities[i].id == id) {
                system("clear");
                cout << "Введите нового преподавателя: ";
                getline(cin, universities[i].professor);
                system("clear");
                cout << "Введите новую кафедру: ";
                getline(cin, universities[i].kafedra);
                system("clear");
                cout << "Введите новый предмет: ";
                getline(cin, universities[i].subject);
                while(!isEnd1) {
                    system("clear");
                   cout << "Введите новое количество часов: ";
                    cin >> universities[i].hours;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        system("clear");
                        cout << "Некорректный ввод." << endl;
                        do {
                            cout << '\n' << "Press the Enter key to continue.";
                        } while (cin.get() != '\n');
                    } else {
                        countSuccess++;
                        isEnd1 = true;
                    }
                }
                while(!isEnd2) {
                    system("clear");
                    cout << "Введите новый опыт работы: ";
                    cin >> universities[i].experience;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        system("clear");
                        cout << "Некорректный ввод." << endl;
                        do {
                            cout << '\n' << "Press the Enter key to continue.";
                        } while (cin.get() != '\n');
                    } else {
                        countSuccess++;
                        isEnd2 = true;
                    }
                }
                while(!isEnd3) {
                    system("clear");
                  cout << "Введите новую ставку: ";
                cin >> universities[i].stavka;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("clear");
                    cout << "Некорректный ввод." << endl;
                    do {
                        cout << '\n' << "Press the Enter key to continue.";
                    } while (cin.get() != '\n');
                } else {
                    countSuccess++;
                    isEnd3 = true;
                }
                }

                cin.ignore();
                if (countSuccess == 3) {
                    return;



                }

            }






    }
    cout << "Запись с ID " << id << " не найдена." << endl;
    do {
        cout << '\n' << "Press the Enter key to continue.";
    } while (cin.get() != '\n');
}

void saveDataToFile(const string &filename) {
    ofstream file(filename);
    if (!file) {
        system("clear");
        cerr << "Ошибка открытия файла для записи: " << filename << endl;
        do {
            cout << '\n' << "Press the Enter key to continue.";
        } while (cin.get() != '\n');
        return;
    }

    for (int i = 0; i < arraySize; i++) {
        const auto& university = universities[i];
        file << university.id << endl
             << university.professor << endl
             << university.kafedra << endl
             << university.subject << endl
             << university.hours << endl
             << university.experience << endl
             << university.stavka << endl;
    }
    file.close();
}

int main() {
    system("clear");
    string filename;
    bool isFile = false;
    while (!isFile) {
        cout << "Введите имя файла для чтения данных: ";
        cin >> filename;
        cin.ignore();
        if (readDataFromFile(filename)) {
            isFile = true;
        }
        system("clear");
    }

    int choice;

    while (true) {
        system("clear");
        cout << "\nМеню:\n";
        cout << "1. Просмотр данных\n";
        cout << "2. Редактирование данных\n";
        cout << "3. Сохранение данных в новый файл\n";
        cout << "4. Вывести сумму часов всех преподавателей\n";
        cout << "5. Вывести количество преподавателей на полноц ставке\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("clear");
            cout << "Некорректный ввод." << endl;
            do {
                cout << '\n' << "Press the Enter key to continue.";
            } while (cin.get() != '\n');
            continue;
        }
        if (choice == 1) {
            displayData();
            do {
                cout << '\n' << "Press the Enter key to continue.";
            } while (cin.get() != '\n');
        } else if (choice == 2) {
            int id;
            system("clear");
            cout << "Введите ID записи для редактирования: ";
            cin >> id;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("clear");
                cout << "Некорректный ввод." << endl;
                do {
                    cout << '\n' << "Press the Enter key to continue.";
                } while (cin.get() != '\n');
                continue;
            }
            cin.ignore();
            editData(id);
            do {
                cout << '\n' << "Press the Enter key to continue.";
            } while (cin.get() != '\n');
        } else if (choice == 3) {
            system("clear");
            string newFilename;
            cout << "Введите имя нового файла: ";
            cin >> newFilename;
            cin.ignore();
            saveDataToFile(newFilename);
            do {
                cout << '\n' << "Press the Enter key to continue.";
            } while (cin.get() != '\n');
        } else if (choice == 4) {
            displayAllHours();
            do {
                cout << '\n' << "Press the Enter key to continue.";
            } while (cin.get() != '\n');
        } else if (choice == 5) {
            displayAllStavka();
            do {
                cout << '\n' << "Press the Enter key to continue.";
            } while (cin.get() != '\n');
        } else if (choice == 0) {
            system("clear");
            cout << "Выход из программы." << endl;
            freeMemory();
            do {
                cout << '\n' << "Press the Enter key to continue.";
            } while (cin.get() != '\n');
            return 0;
        } else {
            cout << "Некорректный выбор. Пожалуйста, попробуйте еще раз." << endl;
            do {
                cout << '\n' << "Press the Enter key to continue.";
            } while (cin.get() != '\n');
        }
    }

    return 0;
}
