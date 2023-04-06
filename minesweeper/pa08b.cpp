/// @file pa08b.cpp
/// @author Brandon Timok
/// @date 11/30/2021
/// @brief labels a minesweeper grid with corresponding numbers that touch each bomb.


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>

using namespace std;

const int max_size = 102;

void print_bombs(char table[max_size][max_size], 
                 int i, int j, int num_rows, int num_cols);

int main() {
    // variable declaration(s)
    int num_rows;
    int num_cols;
    int field_num = 1;
    char table[max_size][max_size];

    // input phase
    while ((cin >> num_rows >> num_cols) 
           && !(num_rows == 0 && num_cols == 0)) {
        if (field_num > 1) {
            cout << '\n';
        }
        cout << "Field #" << field_num << ":" << endl;

        for (int i = 0; i < num_rows; ++i) {
            for (int j = 0; j < num_cols; ++j) {
                cin >> table[i][j];
            }
        }

        for (int i = 0; i < num_rows; ++i) {
            for (int j = 0; j < num_cols; ++j) {
               print_bombs(table, i, j, num_rows, num_cols);
            }
            cout << endl;
        }
        ++field_num;
    }
    return 0;
}

void print_bombs(char table[max_size][max_size], 
                 int i, int j, int num_rows, int num_cols) {
    int num_bombs;

    if (table[i][j] == '*') {
        cout << '*';
    } else if (table[i][j] == '.') {
        num_bombs = 0;
        if (i > 0 && table[i-1][j] == '*') {
            num_bombs += 1;
        }
        if ((i > 0 && j > 0) && table[i-1][j-1] == '*') {
            num_bombs += 1;
        }
        if (j > 0 && table[i][j-1] == '*') {
            num_bombs += 1;
        }
        if (((i < num_rows - 1) && j > 0)
            && table[i+1][j-1] == '*') {
            num_bombs += 1;
        }
        if ((i < num_rows - 1) && table[i+1][j] == '*') {
            num_bombs += 1;
        }
        if (((i < num_rows - 1) && (j < num_cols - 1)) 
            && table[i+1][j+1] == '*') {
            num_bombs += 1;
        }
        if ((j < num_cols - 1) && table[i][j+1] == '*') {
            num_bombs += 1;
        }
        if ((i > 0 && (j < num_cols - 1)) 
            && table[i-1][j+1] == '*') {
            num_bombs += 1;
        }
        cout << num_bombs;
    }
}
