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
    bool moved;
    virtual void updateMoves() override;
    Pawn(Board* board, bool isWhite, int location, char type;);
};

class Rook: public Pieces {
    bool moved;
    virtual void updateMoves() override;
    Rook(Board* board, bool isWhite, int location, char type;);
};

class King: public Pieces {
    bool moved;
    virtual void updateMoves() override;
    King(Board* board, bool isWhite, int location, char type;);
};

class Queen: public Pieces {
    virtual void updateMoves() override;
    Queen(Board* board, bool isWhite, int location, char type;);
};

class Knight: public Pieces {
    virtual void updateMoves() override;
    Knight(Board* board, bool isWhite, int location, char type;);
};

class Bishop: public Pieces {
    virtual void updateMoves() override;
    Bishop(Board* board, bool isWhite, int location, char type;)
};

class emptyPiece: public Pieces {
    virtual void updateMoves() override;
    emptyPiece(Board* board, int location);
};

#endif

