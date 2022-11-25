#include <vector>

class Board;
class Coord;

class Pieces {
        virtual void updateMoves() =0;
        Board* board;
        bool isWhite;
        Coord* location;
        std::vector <Coord*> legalmoves;
};

class Pawn : public Pieces {
    virtual void updateMoves() override;
};

class Rook: public Pieces {
    virtual void updateMoves() override;
};

class King: public Pieces {
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
