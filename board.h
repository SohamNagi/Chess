#ifndef BOARD.H
#define BOARD.H

#include <vector>
#include <string>
#include "coord.h"

class Pieces;

class BoardState{

    // Fields for Board
    public:

        std::vector<Pieces> boardState;
        std::vector<Coord> LastMove;
        Coord en_passant;
        int eval;

    private:

        int halfMoves;
        int moves;
        bool WhiteCheck;
        bool BlackCheck;

    // Methods for Board:
    public:
        void attachPiece();
        void detachPiece();

    private:

        std::string FEN();
        void notifyStateChange(); // updates eval?
};

#endif



