#ifndef COMPUTER.H
#define COMPUTER.H

#include "player.h"

struct BestMove {
    int start;
    int end;

    BestMove(int start, int end);
};

class Computer: public Player {
    public:
        Computer(bool isWhite, Board* board);
        void getmove();
        virtual BestMove evaluate() = 0;


};

class Level1: public Computer {
    BestMove evaluate();
};

class Level2: public Computer {
    BestMove evaluate();
};

class Level3: public Computer {
    BestMove evaluate();
};

class Level4: public Computer {
    BestMove evaluate();
};


#endif