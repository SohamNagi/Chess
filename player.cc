#include "player.h"
#include "pieces.h"
#include "board.h"
#include <algorithm>
#include <iostream>


Player::Player(bool isWhite, Board* board): isWhite(isWhite), board{board} {};


bool Player::move(int start, int end, Board* board) {

    // Checks if the square (represented as an index to the
    //    boardState) contains and empty.
    
    std::cout << "test 1: " << start << " " << end << std::endl;
    if (board->boardState[start]->isEmpty) {
        return false;
    }

    // Iterators for finding the end move in the selected pieces
    //  legal moves.

    std::cout << "test 2" << std::endl;
    auto iter_start = board->boardState[start]->legalmoves.begin();
    auto iter_end = board->boardState[start]->legalmoves.end();

    std::cout << "type: " << board->boardState[start]->type << board->boardState[start]->location << std::endl;

    for (auto i: board->boardState[start]->legalmoves) {
        std::cout << i << ' ';
    }

    std::cout << "test 3" << std::endl;
    auto result = std::find(iter_start, iter_end, end);

    if (result == iter_end) {
        return false;
    }

    // Changes the location in the selected pieces
    //  and swaps the contents stored in the start
    //  index and end index.

    std::cout << "test 4" << std::endl;
    board->boardState[start]->location = *iter_end;
    std::iter_swap(iter_start, result);
    std::cout << "test 5" << std::endl;
    return true;

}
