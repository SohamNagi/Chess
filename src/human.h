#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "player.h"

class Human: public Player {
    public:
        void getmove();
        Human(bool isWhite, Board* board);
};


#endif 