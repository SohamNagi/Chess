#include "player.h"
#include "pieces.h"
#include "board.h"
#include <algorithm>
#include <iostream>


Player::Player(bool isWhite, Board* board): isWhite(isWhite), board{board} {};


bool Player::move(int start, int end, Board* board) {
    // Checks if the square (represented as an index to the
    //    boardState) contains and empty.
    
    if (board->boardState[start]->isEmpty) {
        return false;
    }
    // Iterators for finding the end move in the selected pieces
    //  legal moves.

    Pieces* piece = board->boardState[start];

    if (std::find(piece->legalmoves.begin(), piece->legalmoves.end(), end) == piece->legalmoves.end()) {
        return false;
    }
    // Changes the location in the selected pieces
    //  and swaps the contents stored in the start
    //  index and end index.

    board->boardState[start]->location = end;
    board->boardState[end]->location = start;
    std::iter_swap(board->boardState.begin() + start, board->boardState.begin() + end);
    return true;

}
