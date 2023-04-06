/// @file pa05b.cpp
/// @author Brandon Timok
/// @date 10/14/2021
/// @brief Program that projects the growth of a bean into a beanstalk.

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() {
    // variable declaration(s)
    int return_value = 0;
    int num_days = 1;
    // double max_height = 2147.483648;
    long height = 1;
    double height_left = .000001;
    // split into two variables for each side of decimal
    // input phase

    // processing phase

    // output phase
    cout << '\n' << setw(27) << "Beanstalk Growth Projection" << endl;
    cout << '\n';
    cout << right << setw(3) << "Day" << "  " << setw(22) << "Height (m)" << endl;
    cout << "---  ----------------------" << endl;


    // int counter = 0;
    cout << fixed << showpoint << setprecision(6);


    while (num_days < 65) {
            //    cout << right << setw(28) << "**" << endl;
            // } else {
            if (num_days == 32) {
                cout << right << setw(3) << setfill(' ') << num_days
                     << "  " << setw(15) << static_cast<long>(height_left) << "."
                     << setw(6) << setfill('0') << height << " **" << endl;
                num_days++;
                height_left *= 2;
                height = (height * 2) % 1000000;
            } else {
                cout << right << setw(3) << setfill(' ')
                     << num_days << "  " << setw(15) << static_cast<long>(height_left) << "."
                     << setw(6) << setfill('0') << height << endl;
                num_days++;
                height_left *= 2;
                height = (height * 2) % 1000000;
            // }
        }
    }

    // return statement
    return return_value;
}
