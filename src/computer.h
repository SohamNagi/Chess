#ifndef __COMPUTER_H__
#define __COMPUTER_H__

#include "player.h"

struct BestMove {
    int start;
    int end;

    bool no_moves;

    BestMove(int start, int end);
    BestMove(bool no_moves);
};

class Computer: public Player {
    public:
        bool isWhite;
        Board* board;
        Computer(bool isWhite, Board* board);
        void getmove();
        void promote(int piece);
        virtual BestMove evaluate() = 0;


};

class Level1: public Computer {
    public:
        Level1(bool isWhite, Board* board);
        BestMove evaluate();
};

#endif