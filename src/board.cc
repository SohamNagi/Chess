#include "board.h"
#include "pieces.h"
#include <iostream>
#include <algorithm>

// Setup boards may be in check// Setup needs to assign proper turn from fen
Board::Board(std::string input):
    halfMoves{0},moves{1},WhiteCheck{false}, BlackCheck{false}, eval{0}
{
    int row = 7;
    int col = 0;
    int i = 0;
    boardState.resize(64);
    while (input[i] != ' ') {
        char curr = input[i];
        int index = (8*row) + col;
        if (input[i+2] == 'w') {
            whiteTurn = true;
        } else if (input[i+2] == 'b') {
            whiteTurn = false;
        }

        if (curr == '/'){
            row--;
            col = 0;
        } else if (isdigit(curr)) {
            int skip = curr - '0';
            for(int g = 0; g < skip; g++){
                boardState[index+g] = new emptyPiece(this, false, index + g, ' ');
                col++;
            }
            if(col == 7){
                --row;
                col = 0;
            }
        } else {
            if(curr == 'k'){
                boardState[index] = new King(this, false, index, 'k');
            } else if (curr == 'q'){
                boardState[index] = new Queen(this, false, index, 'q');
            } else if (curr == 'p'){
                boardState[index] = new Pawn(this, false, index, 'p');
            } else if (curr == 'n'){
                boardState[index] = new Knight(this, false, index, 'n');
            } else if (curr == 'r'){
                boardState[index] = new Rook(this, false, index, 'r');
            } else if (curr == 'b'){
                boardState[index] = new Bishop(this, false, index, 'b');
            } else if (curr == 'K'){
                boardState[index] = new King(this, true, index, 'K');
            } else if (curr == 'Q'){
                boardState[index] = new Queen(this, true, index, 'Q');
            } else if (curr == 'P'){
                boardState[index] = new Pawn(this, true, index, 'P');
            } else if (curr == 'N'){
                boardState[index] = new Knight(this, true, index, 'N');
            } else if (curr == 'R'){
                boardState[index] = new Rook(this, true, index, 'R');
            } else if (curr == 'B'){
                boardState[index] = new Bishop(this, true, index, 'B');
            }
            col++;
        }
        i++;
    }
}

void Board::notifyStateChange() {
    for (auto i : boardState) {
        i->updateMoves();
    }
}

Board::~Board(){
    for(auto i: boardState){
        delete i;
    }
}

// Checks if the board has an active check, returns 1 if white is in check, -1 if black is in check, and 0 if no checks
int Board::boardInCheck(){
    for (auto i: boardState) {
        i->updateMoves();
    }
    std::vector<int> blackMoves;
    std::vector<int> whiteMoves;
    int whiteKingPosition = -1;
    int blackKingPosition = -1;
    for(auto i: boardState){
        if (i->type == 'K' || i->type == 'k') {
            (i->type == 'K') ? whiteKingPosition = i->location : blackKingPosition = i->location;
            continue;
        } 
        if (!i->isEmpty) {
            for (auto move: i->legalmoves) {
                (i->isWhite) ? whiteMoves.emplace_back(move) : blackMoves.emplace_back(move);
            }
        }
    }

    if(std::find(whiteMoves.begin(), whiteMoves.end(), blackKingPosition) != whiteMoves.end()) {
        return -1;
    }
    else if (std::find(blackMoves.begin(), blackMoves.end(), whiteKingPosition) != blackMoves.end()) {
        return 1;
    }
    return 0;
}
