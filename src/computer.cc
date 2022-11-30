#include "computer.h"

BestMove::BestMove(int start, int end): start{start}, end{end} {};


void Computer::getmove() {
    BestMove move = this->evaluate();
    this->move(move.start, move.end, this->board);
}

Level1::Level1(bool isWhite, Board* board): Computer(isWhite, board) {};

Level2::Level2(bool isWhite, Board* board): Computer(isWhite, board) {};

Level3::Level3(bool isWhite, Board* board): Computer(isWhite, board) {};

Level4::Level4(bool isWhite, Board* board): Computer(isWhite, board) {};