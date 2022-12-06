#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "player.h"
#include "graphicObserver.h"


class Human: public Player {
    public:
        //graphicObserver* gfx;
        void getmove(Board* test = nullptr);
        void promote(int piece);
        Human(bool isWhite, Board* board);//, graphicObserver* obs);
        virtual ~Human();
};


#endif 