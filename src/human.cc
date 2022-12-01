#include "human.h"
#include "pieces.h"
#include <iostream>

using namespace std;

Human::Human(bool isWhite, Board* board):
    Player{isWhite, board}
{};

Human::~Human() {};

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
            board->whiteTurn = !board->whiteTurn;
            break;
        } 
    }

    ;
}

void Human::promote(int piece) {
    int x = piece % 8;
    int y = (piece-(piece % 8)) / 8;
    char row = x + 'a';
    bool isWhite = board->boardState[piece]->isWhite;

    delete board->boardState[piece];
    char newPiece;
    while (true) {
        
        std::cout << "Promote pawn at " << row << y + 1 << ". Enter desired promotion (q/n/b/r):" << endl;
        cin >> newPiece;
        if (newPiece == 'q') {
            board->boardState[piece] = new Queen(board, isWhite, piece, 'Q');
        }
        else if (newPiece == 'n') {
            board->boardState[piece] = new Knight(board, isWhite, piece, 'N');
        }
        else if (newPiece == 'b') {
            board->boardState[piece] = new Bishop(board, isWhite, piece, 'B');
        }
        else if (newPiece == 'r') {
            board->boardState[piece] = new Rook(board, isWhite, piece, 'R');
        }
        else {
            std::cout << "Invalid type. Try again" << endl;
            continue;
        }
        break;
    }
}
