#ifndef HUMAN
#define HUMAN

#include "player.h"

class Human: public Player {
    public:
        void getmove();
        Human(bool isWhite, Board* board);
};


#endif 