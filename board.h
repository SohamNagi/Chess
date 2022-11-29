#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
#include <string>

class Pieces;

class Board {

    // Fields for Board
    public:
        std::vector<Pieces*> boardState;
        //std::vector<Coord> LastMove;
        //Coord en_passant;

        int halfMoves;
        int moves;
        bool WhiteCheck;
        bool BlackCheck;
        int eval;

    // Methods for Board:
    public:
        void attachPiece();
        void detachPiece();
        Board(std::string fen);

    private:

        std::string FEN();
        void notifyStateChange(); // updates eval?
};

#endif



