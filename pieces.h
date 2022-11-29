#ifndef __PIECES_H__
#define __PIECES_H__

#include <vector>
#include "board.h"

class Pieces {
    public:
        Board* board;
        bool isWhite;
        int location;
        char type;
        bool isEmpty;
        std::vector <int> legalmoves;
    public:
        Pieces(Board* board, bool isWhite, int location, char type, bool isEmpty);
        virtual void updateMoves() = 0;
        virtual ~Pieces() = 0;
};

// class emptyPiece: public Pieces {
//     public:
//         void updateMoves() override;
//         emptyPiece(Board* board, bool isWhite, int location, char type);
//         virtual ~emptyPiece();
// };

class emptyPiece : public Pieces {
    public:
        void updateMoves() override;
        emptyPiece(Board* board, bool isWhite, int location, char type);
        virtual ~emptyPiece();
};

class Pawn : public Pieces {
    public:
        bool moved;
        void updateMoves() override;
        Pawn(Board* board, bool isWhite, int location, char type);
        virtual ~Pawn();
};

class Rook: public Pieces {
    public:
        bool moved;
        void updateMoves() override;
        Rook(Board* board, bool isWhite, int location, char type);
        virtual ~Rook();
};

class King: public Pieces {
    public:
        bool moved;
        void updateMoves() override;
        King(Board* board, bool isWhite, int location, char type);
        virtual ~King();
};

class Queen: public Pieces {
    public:
        void updateMoves() override;
        Queen(Board* board, bool isWhite, int location, char type);
        virtual ~Queen();
};

class Knight: public Pieces {
    public:
        void updateMoves() override;
        Knight(Board* board, bool isWhite, int location, char type);
        virtual ~Knight();
};

class Bishop: public Pieces {
    public:
        void updateMoves() override;
        Bishop(Board* board, bool isWhite, int location, char type);
        virtual ~Bishop();
};

#endif

