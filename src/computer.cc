#include "computer.h"
#include <vector>
#include "pieces.h"
#include <cstdlib>

BestMove::BestMove(int start, int end): start{start}, end{end}, no_moves{false} {};
BestMove::BestMove(bool no_moves): start{0}, end{0}, no_moves{no_moves} {};

// COMPUTER SHOULD CHANGE TURN AFTER MOVING board->whiteTurn = !board->whiteTurn;
void Computer::getmove() {
    BestMove move = this->evaluate();
    this->move(move.start, move.end, this->board);
}

// Level1 function
Level1::Level1(bool isWhite, Board* board): Computer(isWhite, board) {


Level1::Level1(bool isWhite, Board* board): Computer(isWhite, board) {};

};

BestMove Level1::evaluate() {
    std::vector<BestMove> moves;

    auto start = this->board->boardState.begin();
    auto end = this->board->boardState.end();

    for (auto i = start; i < end; ++i) {
        if ((*i)->isWhite = this->isWhite) {
            for (auto j = (*i)->legalmoves.begin(); j < (*i)->legalmoves.end(); ++j ) {
               moves.emplace_back(BestMove((*i)->location, (*j)));
            }
        }
    }

    if (moves.size() == 0) {
        return BestMove(true);
    } else {
        int index = std::rand() % moves.size();
        return moves[index];

    }
}

//
Level2::Level2(bool isWhite, Board* board): Computer(isWhite, board) {};

Level3::Level3(bool isWhite, Board* board): Computer(isWhite, board) {};

Level4::Level4(bool isWhite, Board* board): Computer(isWhite, board) {};
