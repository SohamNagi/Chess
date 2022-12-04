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
        bool whiteTurn;

    // Methods for Board:
    public:
        void attachPiece();
        void detachPiece();
        int boardInCheck();
        Board(std::string fen);
        bool isValid();
        void notifyStateChange();
        ~Board();
    private:

        std::string FEN();
};

#endif



