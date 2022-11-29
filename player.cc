#include "player.h"
#include "pieces.h"
#include "board.h"
#include <algorithm>


bool player::move(int start, int end, Board* board) {

    // Checks if the square (represented as an index to the
    //    boardState) contains and empty.

    if (board->boardState[start]->isEmpty) {
        return false;
    }

    // Iterators for finding the end move in the selected pieces
    //  legal moves.

    auto iter_start = board->boardState[start]->legalmoves.begin();
    auto iter_end = board->boardState[start]->legalmoves.end();

    auto result = std::find(iter_start, iter_end, end);

    if (result == iter_end) {
        return false;
    }

    // Changes the location in the selected pieces
    //  and swaps the contents stored in the start
    //  index and end index.

    board->boardState[start]->location = end;
    std::iter_swap(iter_start, result);
    return true;

}

void player::getmove() {
    char input;
    int start;
    int end;

    std::cin >> input;

    if (input )

}