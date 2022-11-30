#include "human.h"
#include <iostream>

using namespace std;

Human::Human(bool isWhite, Board* board):
    Player{isWhite, board}
{};

void Human::getmove() {

    char input_c;
    int input_n;
    int start;
    int end;


    while(true) {

        // Reading starting position
        cin >> input_c;

        if(cin.fail()) {
            cerr << "Unable to read starting column. Try again." << endl;
            continue;
        }

        if (('a' <= input_c) && (input_c <= 'h')) {
            start = (input_c - 'a');     
 
        } else {
            cerr << "Invalid starting column. Try again." << endl;
            continue;
        }

        cin >> input_n;

        if(cin.fail()) {
            cerr << "Unable to read starting row. Try again." << endl;
            continue;
        }

        if ((1 <= input_n) && (input_n <= 8)) {
            start += (input_n - 1) * 8;
 
        } else {
            cerr << "Invalid starting row. Try again." << endl;
            continue;
        }

        // Reading end position

        cin >> input_c;

        if(cin.fail()) {
            cerr << "Unable to read ending column. Try again." << endl;
            continue;
        }

        if (('a' <= input_c) && (input_c <= 'h')) {
            end = (input_c - 'a');
 
        } else {
            cerr << "Invalid ending column. Try again." << endl;
            continue;
        }


        cin >> input_n;

        if(cin.fail()) {
            cerr << "Unable to read ending row. Try again." << endl;
            continue;
        }

        if ((1 <= input_n) && (input_n <= 8)) {
            end += (input_n - 1) * 8;
 
        } else {
            cerr << "Invalid starting row. Try again." << endl;
            continue;
        }


        if (this->move(start, end, this->board)) {
            break;
        } 
    }

    ;
}