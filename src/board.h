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
        std::vector<std::vector<int>> illegalmoves;

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
        Board(std::string fen);
        void notifyStateChange(bool checkTest);
        ~Board();
        int boardInCheck();
    private:

        std::string FEN();
};

#endif



