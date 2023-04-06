/// @file pa05.cpp
/// @author Brandon Timok
/// @date 10/08/2021
/// @brief This program prints out a calendar month depending on what month
/// and year is input.

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    // local constant definitions
    const int JAN =  1;
    const int FEB =  2;
    const int MAR =  3;
    const int APR =  4;
    const int MAY =  5;
    const int JUN =  6;
    const int JUL =  7;
    const int AUG =  8;
    const int SEP =  9;
    const int OCT = 10;
    const int NOV = 11;
    const int DEC = 12;

    // global variable declaration(s)
    int month;
    int year;
    int return_value = 0;
    int num_days;
    int first_day;
    int width;
    string month_name;

    bool is_leap_year = false;
    bool valid = false;

    // input phase - input int m and int y
        cout << "Enter a month and year (example: 04 2023): ";
        cin >> month >> year;
        valid = !(cin.fail() || month < 1 || month > 12 || year <= 1752);

        if (valid == false) {
            cout << "Error: invalid date" << endl;
            return_value = 1;
        }

        else if (valid == true) {

        if (year % 4 != 0) {
            is_leap_year = false;
        } else if (year % 100 != 0) {
            is_leap_year = true;
        } else if (year % 400 != 0) {
            is_leap_year = false;
        } else {
            is_leap_year = true;
        }

        return_value = is_leap_year ? 1 : 0;

        // determine month name
         switch (month) {
            case JAN: month_name = "January"   ; break;
            case FEB: month_name = "February"  ; break;
            case MAR: month_name = "March"     ; break;
            case APR: month_name = "April"     ; break;
            case MAY: month_name = "May"       ; break;
            case JUN: month_name = "June"      ; break;
            case JUL: month_name = "July"      ; break;
            case AUG: month_name = "August"    ; break;
            case SEP: month_name = "September" ; break;
            case OCT: month_name = "October"   ; break;
            case NOV: month_name = "November"  ; break;
            case DEC: month_name = "December"  ; break;
            default:  month_name = "Unknown"   ; break;
        }
        cout << month_name << ' ' << year << endl;
        cout << "Mo" << ' ' << "Tu" << ' ' << "We" << ' ' << "Th" << ' '
             << "Fr" << ' ' << "Sa" << ' ' << "Su" << endl;

        // processing phase
        // calculate amount of days in a given month
        switch (month) {
            case  4:
            case  6:
            case  9:
            case 11:
                num_days = 30;
                break;

            case 2:
                num_days = 28 + (is_leap_year ? 1 : 0);
                break;

            default:
                num_days = 31;
                break;
        }

        if (month == 1 || month == 2) {
            month += 12;
            --year;
        }


        // calculate what day 1st of the month is
         first_day = (1 + (13 * (month + 1)) / 5 + year + year / 4 -
                      year / 100 + year / 400 + 5) % 7;

        // position 1st day of month with math of width
        if (first_day == 0) {
            width = 2;
        } else {
            width = 2 + first_day * 3;
        }

        int column = 6;
        const int NORM_WIDTH = 3;
        const int FIRST_WIDTH = 2;

        column = (1 + (13 * (month + 1)) / 5 + year + year / 4 -
                      year / 100 + year / 400 + 5) % 7;

        cout << right;

        if (column == 0) {
            cout << setw(FIRST_WIDTH) << 1;
        } else if (column == 6) {
            cout << setw(FIRST_WIDTH + column * NORM_WIDTH) << 1 << '\n';
        } else {
            cout << setw(FIRST_WIDTH + column * NORM_WIDTH) << 1;
        }

            column = (column + 1) % 7;

        for (int i = 2; i <= num_days; i++) {
            if (column % 7 == 6) {
                cout << setw(NORM_WIDTH) << i << '\n';
            } else if (i == num_days && column % 7 == 0) {
                cout << setw(FIRST_WIDTH) << i << '\n';
            } else if (i == num_days) {
                cout << setw(NORM_WIDTH) << i << '\n';
            } else if (column % 7 == 0) {
                cout << setw(FIRST_WIDTH) << i;
            } else {
                cout << setw(NORM_WIDTH) << i;
            }

            column = (column + 1) % 7;
            }
        }

    // return statement
    return return_value;
}
