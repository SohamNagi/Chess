#include "pieces.h"
#include <iostream>
#include <algorithm>


// make extra moves like castle and en passant and 2step pawn work in setup


// Still need to implement:
// - Remove moves that result in checks
// - En Passant
// - Castling
// - Remove all moves that don't fix a current check
// - should something else change if the legal move involves capturing?

// personal notes:

// Use functions for the bishop and rook so the queen's function is shorter
// + a lot could be done to make the code shorter and more readable

// could implement a vector in the board class that has the attack coords for white and black
// the only problem with this is the processing required, after every move the program would need to iterate through
// all 64 locations and iterate through those coords' legalmoves vector. Could instead copy over the entire vector,
// so instead we have 2 vectors (black and white attack coords) that consist of 0-16 vectors each, optimizing the program

// refactor to reduce x and y, and use location instead
//cant castle if king is in chec


// CASTLING CHECKTEST en passant?

// Helper function to check if a location is an opponent
bool isEnemy(Pieces* piece, int checkLocation) {
    return (!piece->board->boardState[checkLocation]->isEmpty && 
        piece->board->boardState[checkLocation]->isWhite != piece->isWhite);
}


//  !!!!!!!!!!!!!! implement castling constraints and copy constructors and add code to each piece !!!!!!!!!!!!!!
// check if given move results in on king being in check
bool resultsInCheck(Pieces* piece, int end) {
    for (auto i : piece->board->boardState) {
        if ((i->type == 'k' || i->type == 'K') && i->location == end) return true;
    }
    int start = piece->location;
    // making the move
    piece->board->boardState[start]->location = end;
    piece->board->boardState[end]->location = start;
    std::iter_swap(piece->board->boardState.begin() + start, piece->board->boardState.begin() + end);
    
    // copying the important fields
    bool isWhite = piece->board->boardState[start]->isWhite;
    char type = piece->board->boardState[start]->type;
    bool moved = piece->board->boardState[start]->moved;
    int twoStep = piece->board->boardState[start]->twoStep;
    if (!piece->board->boardState[start]->isEmpty) {
        delete piece->board->boardState[start];
        piece->board->boardState[start] = new emptyPiece(piece->board, false, start, ' ');
    }
    // checking if theres a check
    int checkState = 0;
    checkState = piece->board->boardInCheck(false);
    bool isCheck;
    if ((piece->isWhite && checkState == 1) || (!piece->isWhite && checkState == -1)) isCheck = true;
    else isCheck = false;

    // undoing the move made
    delete piece->board->boardState[start];

    if (type == ' ') {
        piece->board->boardState[start] = new emptyPiece(piece->board, isWhite, start, ' ');
    } else if (type == 'p' || type == 'P') {
        piece->board->boardState[start] = new Pawn(piece->board, isWhite, start, type);
        piece->moved = moved;
        piece->twoStep = twoStep;
    } else if (type == 'r' || type == 'R') {
        piece->board->boardState[start] = new Rook(piece->board, isWhite, start, type);
        piece->moved = moved;
    } else if (type == 'q' || type == 'Q') {
        piece->board->boardState[start] = new Queen(piece->board, isWhite, start, type);
    } else if (type == 'n' || type == 'N') {
        piece->board->boardState[start] = new Knight(piece->board, isWhite, start, type);
    } else if (type == 'b' || type == 'B') {
        piece->board->boardState[start] = new Bishop(piece->board, isWhite, start, type);
    }
    
    std::iter_swap(piece->board->boardState.begin() + start, piece->board->boardState.begin() + end);
    piece->board->boardState[start]->location = start;
    piece->board->boardState[end]->location = end;


    for (auto i: piece->board->boardState) {
        i->updateMoves(false);
    }


    return isCheck;

}


// add to legalmoves
void addToLegalMoves(bool checkTest, Pieces* piece, int move) {
    if (checkTest) {
        if (resultsInCheck(piece, move)) piece->board->illegalmoves[piece->location].emplace_back(move);
    }
    if (std::find(piece->legalmoves.begin(), piece->legalmoves.end(), move) == piece->legalmoves.end()) {
        piece->legalmoves.emplace_back(move);
    }
}


// Piece constructor
Pieces::Pieces(Board* board, bool isWhite, int location, char type, bool isEmpty) :
    board{ board }, isWhite{ isWhite }, location{ location }, type{ type }, isEmpty{ isEmpty },
    moved{ false }, twoStep{ -2 }, legalmoves{ }, illegalmoves{ } {}

// Piece destructor
Pieces::~Pieces() {}

// emptyPiece constructor
emptyPiece::emptyPiece(Board* board, bool isWhite, int location, char type) :
    Pieces{ board, isWhite, location, type, true } {}

// emptyPiece updatemoves
void emptyPiece::updateMoves(bool checkTest) {}

// emptyPiece destructor
emptyPiece::~emptyPiece() {}

// Pawn constructor
Pawn::Pawn(Board* board, bool isWhite, int location, char type) :
    Pieces{ board, isWhite, location, type, false } {}

void Pawn::updateMoves(bool checkTest) {
    legalmoves.clear();
    int x = location % 8;
    int y = (location-(location % 8)) / 8;
    // White Pawns:
    // Check the space immediately above
    if (isWhite && y + 1 <= 7 && board->boardState[(y + 1) * 8 + x]->isEmpty) {
        addToLegalMoves(checkTest, this, (y + 1) * 8 + x);
    }
    // Check the space 2 above
    if (isWhite && !moved && board->boardState[(y + 1) * 8 + x]->isEmpty && board->boardState[(y + 2) * 8 + x]->isEmpty) {
        addToLegalMoves(checkTest, this, (y + 2) * 8 + x);
    }
    // Check 1 up and 1 left to see if a capture is available
    if (isWhite && y + 1 <= 7 && x - 1 >= 0 && isEnemy(this, (y + 1) * 8 + (x - 1))) {
        addToLegalMoves(checkTest, this, (y + 1) * 8 + (x - 1));
    }
    // Check 1 up and 1 right to see if a capture is available
    if (isWhite && y + 1 <= 7 && x + 1 <= 7 && isEnemy(this, (y + 1) * 8 + (x + 1))) {
        addToLegalMoves(checkTest, this, (y + 1) * 8 + (x + 1));
    }
    // Check En Passant left
    if (isWhite && x > 0 && board->boardState[y*8 + x - 1]->type == 'p' && 
        board->boardState[y*8 + x - 1]->twoStep - board->halfMoves == -1) {
        addToLegalMoves(checkTest, this, (y + 1) * 8 + (x - 1));
    }
    // Check En Passant right
    if (isWhite && x < 7 && board->boardState[y*8 + x + 1]->type == 'p' && 
        board->boardState[y*8 + x + 1]->twoStep - board->halfMoves == -1) {
        addToLegalMoves(checkTest, this, (y + 1) * 8 + (x + 1));
    }

    // Black Pawns:
    // Check the space immediately below
    if (!isWhite && y - 1 >= 0 && board->boardState[(y - 1) * 8 + x]->isEmpty) {
        addToLegalMoves(checkTest, this, (y - 1) * 8 + x);
    }
    // Check the space 2 below
    if (!isWhite && !moved && board->boardState[(y - 1) * 8 + x]->isEmpty && board->boardState[(y - 2) * 8 + x]->isEmpty) {
        addToLegalMoves(checkTest, this, (y - 2) * 8 + x);
    }
    // Check 1 down and 1 left to see if a capture is available
    if (!isWhite && y - 1 >= 0 && x - 1 >= 0 && isEnemy(this, (y - 1) * 8 + (x - 1))) {
        addToLegalMoves(checkTest, this, (y - 1) * 8 + (x - 1));
    }
    // Check 1 down and 1 right to see if a capture is available
    if (!isWhite && y - 1 >= 0 && x + 1 <= 7 && isEnemy(this, (y - 1) * 8 + (x + 1))) {
        addToLegalMoves(checkTest, this, (y - 1) * 8 + (x + 1));
    }
    // Check En Passant left
    if (!isWhite && x > 0 && board->boardState[y*8 + x - 1]->type == 'P' && 
        board->boardState[y*8 + x - 1]->twoStep - board->halfMoves == -1) {
        addToLegalMoves(checkTest, this, (y - 1) * 8 + (x - 1));
    }
    // Check En Passant right
    if (!isWhite && x < 7 && board->boardState[y*8 + x + 1]->type == 'P' && 
        board->boardState[y*8 + x + 1]->twoStep - board->halfMoves == -1) {
        addToLegalMoves(checkTest, this, (y - 1) * 8 + (x + 1));
    }
}

// Pawn destructor
Pawn::~Pawn() {}

// Rook constructor
Rook::Rook(Board* board, bool isWhite, int location, char type) :
    Pieces{ board, isWhite, location, type, false } {}

void Rook::updateMoves(bool checkTest) {
    legalmoves.clear();
    int x = location % 8;
    int y = (location-(location % 8)) / 8;

    // From the Rook to the top of the board
    for (int i = y + 1; i <= 7; i++) {
        if (board->boardState[i * 8 + x]->isEmpty) {
            addToLegalMoves(checkTest, this, i * 8 + x);
        } else if (board->boardState[i * 8 + x]->isWhite != isWhite) {
            addToLegalMoves(checkTest, this, i * 8 + x);
            break;
        } else break;
    }
    // From the Rook to the bottom of the board
    for (int i = y - 1; i >= 0; i--) {
        if (board->boardState[i * 8 + x]->isEmpty) {
            addToLegalMoves(checkTest, this, i * 8 + x);
        } else if (board->boardState[i * 8 + x]->isWhite != isWhite) {
            addToLegalMoves(checkTest, this, i * 8 + x);
            break;
        } else break;
    }
    // From the Rook to the right of the board
    for (int i = x + 1; i <= 7; i++) {
        if (board->boardState[y * 8 + i]->isEmpty) {
            addToLegalMoves(checkTest, this, y * 8 + i);
        } else if (board->boardState[y * 8 + i]->isWhite != isWhite) {
            addToLegalMoves(checkTest, this, y * 8 + i);
            break;
        } else break;
    }
    // From the Rook to the left of the board
    for (int i = x - 1; i >= 0; i--) {
        if (board->boardState[y * 8 + i]->isEmpty) {
            addToLegalMoves(checkTest, this, y * 8 + i);
        } else if (board->boardState[y * 8 + i]->isWhite != isWhite) {
            addToLegalMoves(checkTest, this, y * 8 + i);
            break;
        } else break;
    }    
}

// Rook destructor
Rook::~Rook() {}

// King constructor
King::King(Board* board, bool isWhite, int location, char type) :
    Pieces{ board, isWhite, location, type, false } {}

void King::updateMoves(bool checkTest)  {
    legalmoves.clear();
    int x = location % 8;
    int y = (location-(location % 8)) / 8;

    // Check all surrounding spaces for the King
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int possible = (y + j) * 8 + (x + i);
            if (0 <= possible && possible < 64 && !(i == 0 && j == 0) && (board->boardState[possible]->isEmpty ||
                board->boardState[possible]->isWhite != isWhite)) {
                    addToLegalMoves(checkTest, this, (y + j) * 8 + (x + i));
                }
        }
    }

    // Castling
    if (isWhite && !moved && board->boardState[5]->isEmpty && board->boardState[6]->isEmpty && 
        board->boardState[7]->type == 'R' && !board->boardState[7]->moved) {
            legalmoves.emplace_back(6);
    }
    if (isWhite && !moved && board->boardState[3]->isEmpty && board->boardState[2]->isEmpty && 
        board->boardState[1]->isEmpty && board->boardState[0]->type == 'R' && !board->boardState[0]->moved) {
            legalmoves.emplace_back(2);
    }
    if (!isWhite && !moved && board->boardState[61]->isEmpty && board->boardState[62]->isEmpty && 
        board->boardState[63]->type == 'r' && !board->boardState[63]->moved) {
            legalmoves.emplace_back(62);
    }
    if (!isWhite && !moved && board->boardState[59]->isEmpty && board->boardState[58]->isEmpty && 
        board->boardState[57]->isEmpty && board->boardState[56]->type == 'r' && !board->boardState[56]->moved) {
            legalmoves.emplace_back(58);
    }
}

// King destructor
King::~King() {}

// Queen constructor
Queen::Queen(Board* board, bool isWhite, int location, char type) :
    Pieces{ board, isWhite, location, type, false } {}

void Queen::updateMoves(bool checkTest) {
    legalmoves.clear();
    int x = location % 8;
    int y = (location-(location % 8)) / 8;
    // Queen x/y sliding:    
    // From the Queen to the top of the board
    for (int i = y + 1; i <= 7; i++) {
        if (board->boardState[i * 8 + x]->isEmpty) {
            addToLegalMoves(checkTest, this, i * 8 + x);
        } else if (board->boardState[i * 8 + x]->isWhite != isWhite) {
            addToLegalMoves(checkTest, this, i * 8 + x);
            break;
        } else break;
    }
    // From the Queen to the bottom of the board
    for (int i = y - 1; i >= 0; i--) {
        if (board->boardState[i * 8 + x]->isEmpty) {
            addToLegalMoves(checkTest, this, i * 8 + x);
        } else if (board->boardState[i * 8 + x]->isWhite != isWhite) {
            addToLegalMoves(checkTest, this, i * 8 + x);
            break;
        } else break;
    }
    // From the Queen to the right of the board
    for (int i = x + 1; i <= 7; i++) {
        if (board->boardState[y * 8 + i]->isEmpty) {
            addToLegalMoves(checkTest, this, y * 8 + i);
        } else if (board->boardState[y * 8 + i]->isWhite != isWhite) {
            addToLegalMoves(checkTest, this, y * 8 + i);
            break;
        } else break;
    }
    // From the Queen to the left of the board
    for (int i = x - 1; i >= 0; i--) {
        if (board->boardState[y * 8 + i]->isEmpty) {
            addToLegalMoves(checkTest, this, y * 8 + i);
        } else if (board->boardState[y * 8 + i]->isWhite != isWhite) {
            addToLegalMoves(checkTest, this, y * 8 + i);
            break;
        } else break;
    }

    // Queen diagonal sliding
    bool doubleBreak = false;

    // Checking the up/right diagonal
    for (int i = x + 1; i < 8; i++) {
        for (int j = y + 1; j < 8; j++) {
            if (abs(i - x) == abs(j - y)) {
                if (!board->boardState[j * 8 + i]->isEmpty && board->boardState[j * 8 + i]->isWhite == isWhite) {
                    doubleBreak = true;
                    break;
                }
                addToLegalMoves(checkTest, this, j * 8 + i);
                if (!board->boardState[j * 8 + i]->isEmpty && board->boardState[j * 8 + i]->isWhite != isWhite) {
                    doubleBreak = true;
                    break;
                }
            }
        }
        if (doubleBreak) break;
    }

    doubleBreak = false;
    // Checking the down/right diagonal
    for (int i = x + 1; i < 8; i++) {
        for (int j = y - 1; j >= 0; j--) {
            if (abs(i - x) == abs(j - y)) {
                if (!board->boardState[j * 8 + i]->isEmpty && board->boardState[j * 8 + i]->isWhite == isWhite) {
                    doubleBreak = true;
                    break;
                }
                addToLegalMoves(checkTest, this, j * 8 + i);
                if (!board->boardState[j * 8 + i]->isEmpty && board->boardState[j * 8 + i]->isWhite != isWhite) {
                    doubleBreak = true;
                    break;
                }
            }
        }
        if (doubleBreak) break;
    }

    doubleBreak = false;

    // Checking the down/left diagonal
    for (int i = x - 1; i >= 0; i--) {
        for (int j = y - 1; j >= 0; j--) {
            if (abs(i - x) == abs(j - y)) {
                if (!board->boardState[j * 8 + i]->isEmpty && board->boardState[j * 8 + i]->isWhite == isWhite) {
                    doubleBreak = true;
                    break;
                }
                addToLegalMoves(checkTest, this, j * 8 + i);
                if (!board->boardState[j * 8 + i]->isEmpty && board->boardState[j * 8 + i]->isWhite != isWhite) {
                    doubleBreak = true;
                    break;
                }
            }
        }
        if (doubleBreak) break;
    }

    doubleBreak = false;

    // Checking the up/left diagonal
    for (int i = x - 1; i >= 0; i--) {
        for (int j = y + 1; j < 8; j++) {
            if (abs(i - x) == abs(j - y)) {
                if (!board->boardState[j * 8 + i]->isEmpty && board->boardState[j * 8 + i]->isWhite == isWhite) {
                    doubleBreak = true;
                    break;
                }
                addToLegalMoves(checkTest, this, j * 8 + i);
                if (!board->boardState[j * 8 + i]->isEmpty && board->boardState[j * 8 + i]->isWhite != isWhite) {
                    doubleBreak = true;
                    break;
                }
            }
        }
        if (doubleBreak) break;
    }
}

// Queen destructor
Queen::~Queen() {}

// Knight constructor
Knight::Knight(Board* board, bool isWhite, int location, char type) :
    Pieces{ board, isWhite, location, type, false } {}

void Knight::updateMoves(bool checkTest) {
    legalmoves.clear();
    int x = location % 8;
    int y = (location-(location % 8)) / 8;
    // Combining these two arrays gives the 8 possible moves for any knight

    // make this into 1 array for pieces2.cc
    int xChange[8] = {-1, 1, -2, -2, -1, 1, 2, 2};
    int yChange[8] = {-2, -2, -1, 1, 2, 2, -1, 1};
    // Looping through all 8 positions and checking if they are empty or capturable
    for (int i = 0; i < 8; i++) {
        int possible = (y + yChange[i]) * 8 + x + xChange[i];
        if (0 <= possible && possible < 64 && y + yChange[i] < 8 && x + xChange[i] < 8 && y + yChange[i] >= 0 && x + xChange[i] >= 0 &&
            (board->boardState[possible]->isEmpty || board->boardState[possible]->isWhite != isWhite)) {
                addToLegalMoves(checkTest, this, possible);
        }
    }
}

// Knight destructor
Knight::~Knight() {}

// Bishop constructor
Bishop::Bishop(Board* board, bool isWhite, int location, char type) :
    Pieces{ board, isWhite, location, type, false } {}

void Bishop::updateMoves(bool checkTest) {
    legalmoves.clear();
    int x = location % 8;
    int y = (location-(location % 8)) / 8;

    // create a helper function for the inner portion of the loop

    bool doubleBreak = false;

    // Checking the up/right diagonal
    for (int i = x + 1; i < 8; i++) {
        for (int j = y + 1; j < 8; j++) {
            if (abs(i - x) == abs(j - y)) {
                if (!board->boardState[j * 8 + i]->isEmpty && board->boardState[j * 8 + i]->isWhite == isWhite) {
                    doubleBreak = true;
                    break;
                }
                addToLegalMoves(checkTest, this, j * 8 + i);
                if (!board->boardState[j * 8 + i]->isEmpty && board->boardState[j * 8 + i]->isWhite != isWhite) {
                    doubleBreak = true;
                    break;
                }
            }
        }
        if (doubleBreak) break;
    }
    if (checkTest) {
        doubleBreak = false;
    }
    // Checking the down/right diagonal
    for (int i = x + 1; i < 8; i++) {
        for (int j = y - 1; j >= 0; j--) {
            if (abs(i - x) == abs(j - y)) {
                if (!board->boardState[j * 8 + i]->isEmpty && board->boardState[j * 8 + i]->isWhite == isWhite) {
                    doubleBreak = true;
                    break;
                }
                addToLegalMoves(checkTest, this, j * 8 + i);
                if (!board->boardState[j * 8 + i]->isEmpty && board->boardState[j * 8 + i]->isWhite != isWhite) {
                    doubleBreak = true;
                    break;
                }
            }
        }
        if (doubleBreak) break;
    }

    doubleBreak = false;

    // Checking the down/left diagonal
    for (int i = x - 1; i >= 0; i--) {
        for (int j = y - 1; j >= 0; j--) {
            if (abs(i - x) == abs(j - y)) {
                if (!board->boardState[j * 8 + i]->isEmpty && board->boardState[j * 8 + i]->isWhite == isWhite) {
                    doubleBreak = true;
                    break;
                }
                addToLegalMoves(checkTest, this, j * 8 + i);
                if (!board->boardState[j * 8 + i]->isEmpty && board->boardState[j * 8 + i]->isWhite != isWhite) {
                    doubleBreak = true;
                    break;
                }
            }
        }
        if (doubleBreak) break;
    }

    doubleBreak = false;

    // Checking the up/left diagonal
    for (int i = x - 1; i >= 0; i--) {
        for (int j = y + 1; j < 8; j++) {
            if (abs(i - x) == abs(j - y)) {
                if (!board->boardState[j * 8 + i]->isEmpty && board->boardState[j * 8 + i]->isWhite == isWhite) {
                    doubleBreak = true;
                    break;
                }
                addToLegalMoves(checkTest, this, j * 8 + i);
                if (!board->boardState[j * 8 + i]->isEmpty && board->boardState[j * 8 + i]->isWhite != isWhite) {
                    doubleBreak = true;
                    break;
                }
            }
        }
        if (doubleBreak) break;
    }
}

// Bishop destructor
Bishop::~Bishop() {}
