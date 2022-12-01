#ifndef COMPUTER.H
#define COMPUTER.H

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
        Computer(bool isWhite, Board* board);
        void getmove();
        virtual BestMove evaluate() = 0;


};

class Level1: public Computer {
    Level1(bool isWhite, Board* board);
    BestMove evaluate();
};

class Level2: public Computer {
    Level2(bool isWhite, Board* board);
    BestMove evaluate();
};

class Level3: public Computer {
    Level3(bool isWhite, Board* board);
    BestMove evaluate();
};

class Level4: public Computer {
    Level4(bool isWhite, Board* board);
    BestMove evaluate();
};


#endif