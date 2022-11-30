#include "pieces.h"
#include "coord.h"


// Piece constructor
Pieces::Pieces(Board* board, bool isWhite, int location, char type, bool isEmpty) :
    board{ board }, isWhite{ isWhite }, location{ location }, type{ type }, isEmpty{ isEmpty }, legalmoves{ } {}

// Piece destructor
Pieces::~Pieces() {}


// emptyPiece constructor
emptyPiece::emptyPiece(Board* board, bool isWhite, int location, char type) :
    Pieces{ board, isWhite, location, type, true } {}

// emptyPiece updating legal moves vector
void emptyPiece::updateMoves() {}

// emptyPiece destructor
emptyPiece::~emptyPiece() {}


// Pawn constructor