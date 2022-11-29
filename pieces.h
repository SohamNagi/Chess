#ifndef PIECES.H
#define PIECES.H

#include <vector>

class Board;
class Coord;

class Pieces {
    public:
        Board* board;
        bool isWhite;
        Coord* location;
        char type;
        bool isEmpty;
        std::vector <int> legalmoves;
    public:
        virtual void updateMoves() = 0;
};

class Pawn : public Pieces {
    public:
        bool moved;
        virtual void updateMoves() override;
        Pawn(Board* board, bool isWhite, int location, char type;);
};

class Rook: public Pieces {
    public:
        bool moved;
        virtual void updateMoves() override;
        Rook(Board* board, bool isWhite, int location, char type;);
};

class King: public Pieces {
    public:
        bool moved;
        virtual void updateMoves() override;
        King(Board* board, bool isWhite, int location, char type;);
};

class Queen: public Pieces {
    public:
        virtual void updateMoves() override;
        Queen(Board* board, bool isWhite, int location, char type;);
};

class Knight: public Pieces {
    public:
        virtual void updateMoves() override;
        Knight(Board* board, bool isWhite, int location, char type;);
};

class Bishop: public Pieces {
    public:
        virtual void updateMoves() override;
        Bishop(Board* board, bool isWhite, int location, char type;)
};

class emptyPiece: public Pieces {
    public:
        virtual void updateMoves() override;
        emptyPiece(Board* board, int location);
};

#endif

