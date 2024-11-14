/*********************************************
Description: A calendar program.
Version: 1.0
*********************************************/

#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <string>
#include <limits>
#include <algorithm>

using namespace std;

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

char getChar() {
    char ch;
    cin >> ch;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return tolower(ch);
}

void printCalendar(int year) {
    int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    int mDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    string monthList[] = {"January", "February", "March", "April", "May", "June", "July", 
                          "August", "September", "October", "November", "December"};

    cout << " ----------------------------------\n";
    cout << "              Calendar - " << year << "\n";
    cout << " ----------------------------------\n\n";

    int days;
    int current;

    int y = year - 1;
    current = (y + y/4 - y/100 + y/400 + t[0] + 1) % 7;

    for (int i = 0; i < 12; i++) {
        if (i == 1) {
            if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
                days = 29;
            else
                days = mDays[i];
        } else {
            days = mDays[i];
        }

        cout << "\n ------------" << monthList[i] << "-------------\n";
        cout << " Sun Mon Tue Wed Thu Fri Sat\n";

        int k;
        for (k = 0; k < current; k++)
            cout << "    ";

        for (int j = 1; j <= days; j++) {
            cout << setw(4) << j;
            if (++k > 6) {
                k = 0;
                cout << "\n";
            }
        }
        if (k)
            cout << "\n";

        current = k;
    }
}

int main() {
    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);
    struct tm *parts = localtime(&now_c);

    int year = 1900 + parts->tm_year;
    char option;

    do {
        clearScreen();
        printCalendar(year);

        cout << "\n\nPress:\n";
        cout << "- n for next year\n";
        cout << "- p for previous year\n";
        cout << "- e to exit\n";
        
        option = getChar();
        
        switch(option) {
            case 'n':
                year++;
                break;
            case 'p':
                year--;
                break;
            case 'e':
                break;
            default:
                cout << "Invalid option. Please try again.\n";
                cin.get(); // Wait for user to press enter
        }
    } while(option != 'e');

    return 0;
}
