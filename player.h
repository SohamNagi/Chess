#ifndef PLAYER.H
#define PLAYER.H

#include "coord.h"

class Rook;

class Player {

    // Fields for Player

    private:
        bool isWhite;

    // Methods for Player
    public:
        void resign();
        void offerDraw();
        bool move(Coord start, Coord end, Pieces** board);
        virtual void getmove() = 0;
        void castle(Rook* rook);
        void promote(char c);
};


#endif


