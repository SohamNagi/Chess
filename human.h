#ifndef HUMAN.H
#define HUMAN.H

#include "player.h"

class Human: public Player {
    public:
        void getmove();
        Human(bool isWhite, Board* board);
};


#endif 