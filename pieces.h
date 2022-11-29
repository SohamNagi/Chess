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
};

class Rook: public Pieces {
    bool moved;
    virtual void updateMoves() override;
};

class King: public Pieces {
    bool moved;
    virtual void updateMoves() override;
};

class Queen: public Pieces {
    virtual void updateMoves() override;
};

class Knight: public Pieces {
    virtual void updateMoves() override;
};

class Bishop: public Pieces {
    virtual void updateMoves() override;   
};

class emptyPiece: public Pieces {
    virtual void updateMoves() override;   
};

#endif

