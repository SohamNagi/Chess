#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "coord.h"
#include "board.h"

class Rook;

class Player {

    public:
        bool isWhite;
        Board* board;
        Player(bool isWhite, Board* board);

        void resign();
        bool move(int start, int end, Board* board);
        virtual void getmove() = 0;
        void castle(Rook* rook);
        void promote(char c);
};


#endif


