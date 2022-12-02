#include "computer.h"
#include "player.h"
#include <vector>
#include "pieces.h"
#include <cstdlib>

Computer::Computer(bool isWhite, Board* board): Player(isWhite, board) {};
void Computer::promote(int piece) {}; // Implement

BestMove::BestMove(int start, int end): start{start}, end{end}, no_moves{false} {};
BestMove::BestMove(bool no_moves): start{0}, end{0}, no_moves{no_moves} {};

// COMPUTER SHOULD CHANGE TURN AFTER MOVING board->whiteTurn = !board->whiteTurn;
void Computer::getmove() {
    BestMove move = this->evaluate();

    if (move.no_moves) {
        this->move(move.start, move.end, this->board);
        this->board->whiteTurn = !(this->board->whiteTurn);
    } 

    // Add code for checkmate and stalemate
}

// Level1 function
Level1::Level1(bool isWhite, Board* board): Computer(isWhite, board) {};


BestMove Level1::evaluate() {
    std::vector<BestMove> moves;

    for (int i = 0; i < 64; ++i) {
        Pieces* curr  = this->board->boardState.at(i);

        if (curr->type == ' ' || curr->isWhite == this->isWhite) {
            continue;
        }

        for (auto j = curr->legalmoves.begin(); j < curr->legalmoves.end(); ++j) {
            moves.emplace_back(BestMove(i, *j));
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
