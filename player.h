#ifndef PLAYER.H
#define PLAYER.H

#include "coord.h"
#include "board.h"

class Rook;

class Player {

    // Fields for Player

    private:
        bool isWhite;
        Board* board;

    // Methods for Player
    public:

        Player(bool isWhite, Board* board);

        void resign();
        void offerDraw();
        bool move(Coord start, Coord end, Pieces** board);
        virtual void getmove() = 0;
        void castle(Rook* rook);
        void promote(char c);
};


#endif


