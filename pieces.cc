#include "pieces.h"
#include "coord.h"

// Still need to implement:
// - Remove moves that result in checks
// - Pawn promotions
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

// temporarily make text render function where you can select a square and see its legal moves (as + symbols)

// Pawn constructor
Pawn::Pawn(Board* board, bool isWhite, Coord* location, char type;) :
    board{ board }, isWhite{ isWhite }, location{ location }, type{ type }, moved{ false } {}

void Pawn::updateMoves() override {
    // White Pawns:
    // Check the space immediately above
    if (isWhite && location.y + 1 <= 7 && board->boardState[location.x][location.y + 1] == nullptr) {
        legalmoves.emplace_back(Coord(location.x, location.y + 1));
    }
    // Check the space 2 above
    if (isWhite && !moved && board->boardState[location.x][location.y + 2] == nullptr) {
        legalmoves.emplace_back(Coord(location.x, location.y + 2));
    }
    // Check 1 up and 1 left to see if a capture is available
    if (isWhite && location.y + 1 <= 7 && location.x - 1 >= 0 && !board->boardState[location.x - 1][location.y + 1]->isWhite) {
        legalmoves.emplace_back(Coord(location.x - 1, location.y + 1));
    }
    // Check 1 up and 1 right to see if a capture is available
    if (isWhite && location.y + 1 <= 7 && location.x + 1 <= 7 && !board->boardState[location.x + 1][location.y + 1]->isWhite) {
        legalmoves.emplace_back(Coord(location.x + 1, location.y + 1));
    }

    // Black Pawns:
    // Check the space immediately below
    if (!isWhite && location.y - 1 >= 0 && board->boardState[location.x][location.y - 1] == nullptr) {
        legalmoves.emplace_back(Coord(location.x, location.y - 1));
    }
    // Check the space 2 below
    if (!isWhite && !moved && board->boardState[location.x][location.y - 2] == nullptr) {
        legalmoves.emplace_back(Coord(location.x, location.y - 2));
    }
    // Check 1 down and 1 left to see if a capture is available
    if (!isWhite && location.y - 1 >= 0 && location.x - 1 >= 0 && board->boardState[location.x - 1][location.y - 1]->isWhite) {
        legalmoves.emplace_back(Coord(location.x - 1, location.y - 1));
    }
    // Check 1 down and 1 right to see if a capture is available
    if (!isWhite && location.y - 1 >= 0 && location.x + 1 <= 7 && board->boardState[location.x + 1][location.y - 1]->isWhite) {
        legalmoves.emplace_back(Coord(location.x + 1, location.y - 1));
    }
}

// Rook constructor
Rook::Rook(Board* board, bool isWhite, Coord* location, char type;) :
    board{ board }, isWhite{ isWhite }, location{ location }, type{ type }, moved{ false } {}

void Rook::updateMoves() override {
    // From the Rook to the top of the board
    for (int i = location.y; i < 7; i++) {
        if (board->boardState[location.x][i] == nullptr) {
            legalmoves.emplace_back(Coord(location.x, i));
        } else if (board->boardState[location.x][i]->isWhite != isWhite) {
            legalmoves.emplace_back(Coord(location.x, i));
            break;
        } else break;
    }
    
    // From the Rook to the bottom of the board
    for (int i = location.y; i > 0; i--) {
        if (board->boardState[location.x][i] == nullptr) {
            legalmoves.emplace_back(Coord(location.x, i));
        } else if (board->boardState[location.x][i]->isWhite != isWhite) {
            legalmoves.emplace_back(Coord(location.x, i));
            break;
        } else break;
    }

    // From the Rook to the right of the board
    for (int i = location.x; i > 7; i++) {
        if (board->boardState[i][location.y] == nullptr) {
            legalmoves.emplace_back(Coord(i, location.y));
        } else if (board->boardState[i][location.y]->isWhite != isWhite) {
            legalmoves.emplace_back(Coord(i, location.y));
            break;
        } else break;
    }

    // From the Rook to the left of the board
    for (int i = location.x; i > 0; i--) {
        if (board->boardState[i][location.y] == nullptr) {
            legalmoves.emplace_back(Coord(i, location.y));
        } else if (board->boardState[i][location.y]->isWhite != isWhite) {
            legalmoves.emplace_back(Coord(i, location.y));
            break;
        } else break;
    }

}

// King constructor
King::King(Board* board, bool isWhite, Coord* location, char type;) :
    board{ board }, isWhite{ isWhite }, location{ location }, type{ type }, moved{ false } {}

void King::updateMoves() override {
    // Check all surrounding spaces for the King
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j--) {
            if (!(i == 0 && j == 0) && board->boardState[location.x + i][location.y + j] == nullptr ||
                !board->boardState[location.x + i][location.y + j]->isWhite) {
                    legalmoves.emplace_back(Coord(location.x + i, location.y + j));
                }
        }
    }
}

// Queen constructor
Queen::Queen(Board* board, bool isWhite, Coord* location, char type;) :
    board{ board }, isWhite{ isWhite }, location{ location }, type{ type } {}

void Queen::updateMoves() override {
    // Queen x/y sliding:    
    // From the Queen to the top of the board
    for (int i = location.y + 1; i < 7; i++) {
        if (board->boardState[location.x][i] == nullptr) {
            legalmoves.emplace_back(Coord(location.x, i));
        } else if (board->boardState[location.x][i]->isWhite != isWhite) {
            legalmoves.emplace_back(Coord(location.x, i));
            break;
        } else break;
    }
    
    // From the Queen to the bottom of the board
    for (int i = location.y + 1; i > 0; i--) {
        if (board->boardState[location.x][i] == nullptr) {
            legalmoves.emplace_back(Coord(location.x, i));
        } else if (board->boardState[location.x][i]->isWhite != isWhite) {
            legalmoves.emplace_back(Coord(location.x, i));
            break;
        } else break;
    }

    // From the Queen to the right of the board
    for (int i = location.x + 1; i > 7; i++) {
        if (board->boardState[i][location.y] == nullptr) {
            legalmoves.emplace_back(Coord(i, location.y));
        } else if (board->boardState[i][location.y]->isWhite != isWhite) {
            legalmoves.emplace_back(Coord(i, location.y));
            break;
        } else break;
    }

    // From the Queen to the left of the board
    for (int i = location.x + 1; i > 0; i--) {
        if (board->boardState[i][location.y] == nullptr) {
            legalmoves.emplace_back(Coord(i, location.y));
        } else if (board->boardState[i][location.y]->isWhite != isWhite) {
            legalmoves.emplace_back(Coord(i, location.y));
            break;
        } else break;
    }


    // Queen diagonal sliding
    bool doubleBreak = false;

    // Checking the up/right diagonal
    for (int i = location.x + 1; i < 8; i++) {
        for (int j = location.y + 1; j < 8; j++) {
            if (abs(i - location.x) == abs(j - location.y)) {
                if (board->boardState[i][location.y]->isWhite == isWhite) {
                    doubleBreak = true;
                    break;
                }
                legalmoves.emplace_back(Coord(i, j));
                if (board->boardState[i][location.y]->isWhite != isWhite) {
                    doubleBreak = true;
                    break;
                }
            }
        }
        if (doubleBreak) break;
    }

    doubleBreak = false;

    // Checking the down/right diagonal
    for (int i = location.x + 1; i < 8; i++) {
        for (int j = location.y - 1; j >= 0; j--) {
            if (abs(i - location.x) == abs(j - location.y)) {
                if (board->boardState[i][location.y]->isWhite == isWhite) {
                    doubleBreak = true;
                    break;
                }
                legalmoves.emplace_back(Coord(i, j));
                if (board->boardState[i][location.y]->isWhite != isWhite) {
                    doubleBreak = true;
                    break;
                }
            }
        }
        if (doubleBreak) break;
    }

    doubleBreak = false;

    // Checking the down/left diagonal
    for (int i = location.x - 1; i >= 0; i--) {
        for (int j = location.y - 1; j >= 0; j--) {
            if (abs(i - location.x) == abs(j - location.y)) {
                if (board->boardState[i][location.y]->isWhite == isWhite) {
                    doubleBreak = true;
                    break;
                }
                legalmoves.emplace_back(Coord(i, j));
                if (board->boardState[i][location.y]->isWhite != isWhite) {
                    doubleBreak = true;
                    break;
                }
            }
        }
        if (doubleBreak) break;
    }

    doubleBreak = false;

    // Checking the up/left diagonal
    for (int i = location.x - 1; i >= 0; i--) {
        for (int j = location.y + 1; j < 8>; j++) {
            if (abs(i - location.x) == abs(j - location.y)) {
                if (board->boardState[i][location.y]->isWhite == isWhite) {
                    doubleBreak = true;
                    break;
                }
                legalmoves.emplace_back(Coord(i, j));
                if (board->boardState[i][location.y]->isWhite != isWhite) {
                    doubleBreak = true;
                    break;
                }
            }
        }
        if (doubleBreak) break;
    }
}

// Knight constructor
Knight::Knight(Board* board, bool isWhite, Coord* location, char type;) :
    board{ board }, isWhite{ isWhite }, location{ location }, type{ type } {}

void Knight::updateMoves() override {
    // Combining these two arrays gives the 8 possible moves for any knight
    int xChange[8] = {-1, 1, -2, -2, -1, 1, 2, 2};
    int yChange[8] = {-2, -2, -1, 1, 2, 2, -1, 1};

    // Looping through all 8 positions and checking if they are empty or capturable
    for (int i = 0; i < 8; i++) {
        if (board->boardState[location.x + xChange[i]][location.y + yChange[i]] == nullptr ||
            board->boardState[location.x + xChange[i]][location.y + yChange[i]]->isWhite != isWhite) {
                legalmoves.emplace_back(Coord(location.x + xChange[i], location.y + yChange[i]));
        }
    }
}

// Bishop constructor
Bishop::Bishop(Board* board, bool isWhite, Coord* location, char type;) :
    board{ board }, isWhite{ isWhite }, location{ location }, type{ type } {}

void Bishop::updateMoves() override {
    // create a helper function for the inner portion of the loop

    bool doubleBreak = false;

    // Checking the up/right diagonal
    for (int i = location.x + 1; i < 8; i++) {
        for (int j = location.y + 1; j < 8; j++) {
            if (abs(i - location.x) == abs(j - location.y)) {
                if (board->boardState[i][location.y]->isWhite == isWhite) {
                    doubleBreak = true;
                    break;
                }
                legalmoves.emplace_back(Coord(i, j));
                if (board->boardState[i][location.y]->isWhite != isWhite) {
                    doubleBreak = true;
                    break;
                }
            }
        }
        if (doubleBreak) break;
    }

    doubleBreak = false;

    // Checking the down/right diagonal
    for (int i = location.x + 1; i < 8; i++) {
        for (int j = location.y - 1; j >= 0; j--) {
            if (abs(i - location.x) == abs(j - location.y)) {
                if (board->boardState[i][location.y]->isWhite == isWhite) {
                    doubleBreak = true;
                    break;
                }
                legalmoves.emplace_back(Coord(i, j));
                if (board->boardState[i][location.y]->isWhite != isWhite) {
                    doubleBreak = true;
                    break;
                }
            }
        }
        if (doubleBreak) break;
    }

    doubleBreak = false;

    // Checking the down/left diagonal
    for (int i = location.x - 1; i >= 0; i--) {
        for (int j = location.y - 1; j >= 0; j--) {
            if (abs(i - location.x) == abs(j - location.y)) {
                if (board->boardState[i][location.y]->isWhite == isWhite) {
                    doubleBreak = true;
                    break;
                }
                legalmoves.emplace_back(Coord(i, j));
                if (board->boardState[i][location.y]->isWhite != isWhite) {
                    doubleBreak = true;
                    break;
                }
            }
        }
        if (doubleBreak) break;
    }

    doubleBreak = false;

    // Checking the up/left diagonal
    for (int i = location.x - 1; i >= 0; i--) {
        for (int j = location.y + 1; j < 8>; j++) {
            if (abs(i - location.x) == abs(j - location.y)) {
                if (board->boardState[i][location.y]->isWhite == isWhite) {
                    doubleBreak = true;
                    break;
                }
                legalmoves.emplace_back(Coord(i, j));
                if (board->boardState[i][location.y]->isWhite != isWhite) {
                    doubleBreak = true;
                    break;
                }
            }
        }
        if (doubleBreak) break;
    }
}
