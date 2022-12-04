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
        virtual ~Player() = 0;

        void resign();
        bool move(int start, int end, Board* board);
        virtual void getmove(Board* test = nullptr) = 0; // Passing a board again is needed
        virtual void promote(int piece) = 0;             // as for some reason, the computer class
        void castle(Rook* rook);                         // cannot accessing the board field without 
};                                                       // without it thinking it is uninitialized


#endif


