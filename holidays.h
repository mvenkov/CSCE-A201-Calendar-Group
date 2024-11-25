/*********************************************
Description: Header file to provide Holidays to calendar.
Version: 1.0
*********************************************/

#ifndef HOLIDAYS_H
#define HOLIDAYS_H

#include <string>
#include <vector>

using namespace std;

struct Holiday {
    string name;
    int month;
    int day;
    bool isFixed;
    int weekNumber;
    int weekday;
};

vector<Holiday> getUSFederalHolidays() {
    return {
        {"New Year's Day", 1, 1, true, 0, 0},
        {"Martin Luther King Jr. Day", 1, 0, false, 3, 1},
        {"Washington's Birthday", 2, 0, false, 3, 1},
        {"Memorial Day", 5, 0, false, -1, 1},
        {"Juneteenth", 6, 19, true, 0, 0},
        {"Independence Day", 7, 4, true, 0, 0},
        {"Labor Day", 9, 0, false, 1, 1},
        {"Columbus Day", 10, 0, false, 2, 1},
        {"Veterans Day", 11, 11, true, 0, 0},
        {"Thanksgiving Day", 11, 0, false, 4, 4},
        {"Christmas Day", 12, 25, true, 0, 0}
    };
}

#endif
