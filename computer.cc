#include "computer.h"

BestMove::BestMove(int start, int end): start{start}, end{end} {};


void Computer::getmove() {
    BestMove move = this->evaluate();
    this->move(move.start, move.end, this->board);
}