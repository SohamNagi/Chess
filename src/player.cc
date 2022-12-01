#include "player.h"
#include "pieces.h"
#include "board.h"
#include <algorithm>
#include <iostream>

using namespace std;

Player::Player(bool isWhite, Board* board): isWhite(isWhite), board{board} {};


bool Player::move(int start, int end, Board* board) {
    // Checks if the square (represented as an index to the
    //    boardState) contains and empty.
    
    if (board->boardState[start]->isEmpty) {
        cerr << "Moving blank piece! Try again" << endl;
        return false;
    }

    // Debug

    cout << "Turn: ";
    if (board->whiteTurn) {
        cout << "White" << endl;
    } else {
        cout << "Black" << endl;
    }

    cout << "Piece: ";
    if (board->boardState[start]->isWhite) {
        cout << "White" << endl;
    } else {
        cout << "Black" << endl;
    }

    // end debug




    if (board->whiteTurn != this->isWhite) {
        cerr << "Moving opponent's piece! Try again" << endl;
        return false;
    }

    // Add exception moving your piece to a square with an existing pieces of the same colour
    // EXCEPT for castling



    // Iterators for finding the end move in the selected pieces
    //  legal moves.

    Pieces* piece = board->boardState[start];
    

    std::cout << "Legal moves prior to making the move. Count: " << piece->legalmoves.size() << std::endl;
    for (auto i: piece->legalmoves) {
        int x = i % 8;
        int y = (i-(i % 8)) / 8;
        char row = x + 'a';
        std::cout << row << y + 1 << ' ';
    }
    std::cout << ' ' << std::endl;


    if (start == end || std::find(piece->legalmoves.begin(), piece->legalmoves.end(), end) == piece->legalmoves.end()) {
        cerr << "Move is not legal!. Try again." << endl;
        return false;
    }

    if (piece->type == 'k' || piece->type == 'K' || piece->type == 'p' || piece->type == 'P' || piece->type == 'r' || piece->type == 'R') {
        piece->moved = true;
    }

    // Changes the location in the selected pieces
    //  and swaps the contents stored in the start
    //  index and end index.

    board->boardState[start]->location = end;
    board->boardState[end]->location = start;
    std::iter_swap(board->boardState.begin() + start, board->boardState.begin() + end);

    if ((end < 64 && end > 55 && board->boardState[end]->type == 'P') || (end < 8 && end >= 0 && board->boardState[end]->type == 'p')) {
        promote(end);
    }

    if (!board->boardState[start]->isEmpty) {
        delete board->boardState[start];
        board->boardState[start] = new emptyPiece(board, false, start, ' ');
    }

    return true;

}
