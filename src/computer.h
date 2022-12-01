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
        bool isWhite;
        Board* board;
        Computer(bool isWhite, Board* board);
        virtual ~Computer() {};
        void getmove();
        void promote(int piece);
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