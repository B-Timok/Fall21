/// @file pa04.cpp
/// @author Brandon Timok
/// @date 10/01/2021
/// @brief Program to convert a specific date to its corresponding day of the week.

#include <iostream>

using namespace std;

int main() {
    // variable declaration(s)

    int return_value = 0;
    int year;
    int month;
    int day;
    int weekday = 0;
    char slash0;
    char slash1;
    bool not_valid = true;

    // input phase
    cout << "Please enter a date (month/day/year): ";
    cin  >> month >> slash0 >> day >> slash1 >> year;

    // processing phase
    {
        not_valid = !(year >= 1753) || !(1 <= month && month <= 12) ||
                    !(1 <= day && day <= 31) || !(slash0 == '/') ||
                    !(slash1 == '/') || (cin.fail());

        if (not_valid) {
            cout << "Error: invalid date" << endl;
            return_value = 0;

            //  if month == 01
            //  then month = 13
            //  if month == 02
            //  then month = 14


        } else if (month == 1) {
            month = 13;
            year = year - 1;
        }

        if (month == 2) {
            month = 14;
            year = year - 1;
        }

        weekday = (day + (13 * (month + 1)) / 5 + year + year / 4 -
                   year / 100 + year / 400 + 5) % 7;


        // output phase
        switch (weekday) {
            case 0:
                cout << "This day will be a Monday" << endl;
                break;

            case 1:
                cout << "This day will be a Tuesday" << endl;
                break;

            case 2:
                cout << "This day will be a Wednesday" << endl;
                break;

            case 3:
                cout << "This day will be a Thursday" << endl;
                break;

            case 4:
                cout << "This day will be a Friday" << endl;
                break;

            case 5:
                cout << "This day will be a Saturday" << endl;
                break;

            case 6:
                cout << "This day will be a Sunday" << endl;
                break;

        }

    return_value = 0;

    }

    // return statement
    return return_value = not_valid ? 1 : 0;
}
