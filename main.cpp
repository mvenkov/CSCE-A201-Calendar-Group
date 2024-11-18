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
#include <vector> // Add this line
#include "holidays.h"

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

int getDayOfWeek(int y, int m, int d) {
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m < 3;
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

bool isHoliday(int year, int month, int day, const vector<Holiday>& holidays) {
    for (const auto& holiday : holidays) {
        if (holiday.isFixed) {
            if (holiday.month == month && holiday.day == day) {
                return true;
            }
        } else {
            int weekday = getDayOfWeek(year, month, 1);
            int targetDay = 1 + (holiday.weekNumber - 1) * 7 + (holiday.weekday - weekday + 7) % 7;
            
            if (holiday.weekNumber == -1) {
                int lastDay = (month == 2) ? (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0) ? 29 : 28) : 
                              (month == 4 || month == 6 || month == 9 || month == 11) ? 30 : 31;
                targetDay = lastDay - (getDayOfWeek(year, month, lastDay) - holiday.weekday + 7) % 7;
            }
            
            if (holiday.month == month && day == targetDay) {
                return true;
            }
        }
    }
    return false;
}

void printCalendar(int year) {
    int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    int mDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    string monthList[] = {"January", "February", "March", "April", "May", "June", "July", 
                          "August", "September", "October", "November", "December"};

    vector<Holiday> holidays = getUSFederalHolidays();

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
            if (isHoliday(year, i + 1, j, holidays)) {
                cout << "\033[1;31m"; // Set text color to red for holidays
            }
            cout << setw(4) << j;
            if (isHoliday(year, i + 1, j, holidays)) {
                cout << "\033[0m"; // Reset text color
            }
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
