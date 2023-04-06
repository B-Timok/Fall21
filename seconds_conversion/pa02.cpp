/// @file pa02.cpp
/// @author Brandon Timok
/// @date 09/16/2021
/// @brief This program converts seconds into days, hours, and minutes.

#include <iostream>

using namespace std;

int main() {
    // local constant definition(s)
    const int SECONDS_PER_DAY     = 86400;
    const int SECONDS_PER_HOUR    = 3600;
    const int SECONDS_PER_MINUTE  = 60;

    // local variable declaration(s)
    int total_seconds; // user-input total number of seconds
    int days;          // computed number of days
    int hours;         // computed number of hours
    int minutes;       // computed number of minutes
    int seconds;       // computed number of seconds

    // input phase
    // prompt the user for number of seconds
    cout << "Please enter total number of seconds: ";

    // read in total number of seconds
    cin >> total_seconds;

    // processing phase
    // compute days
    days = total_seconds / SECONDS_PER_DAY;
    total_seconds %= SECONDS_PER_DAY;

    // compute hours
    hours = total_seconds / SECONDS_PER_HOUR;
    total_seconds %= SECONDS_PER_HOUR;

    // compute minutes
    minutes = total_seconds / SECONDS_PER_MINUTE;
    total_seconds %= SECONDS_PER_MINUTE;

    // compute seconds
    seconds = total_seconds;
 
    // output phase
    // print days, hours, minutes, and seconds
    cout << days << " days " << hours << " hours " << minutes << " minutes "
         << seconds << " seconds " << endl;

    // return statement
    return 0;
}

/* EOF */
