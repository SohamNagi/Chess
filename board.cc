#include "board.h"
#include "pieces.h"
#include <iostream>

// Setup boards may be in check
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
        if (curr == '/'){
            row--;
            col = 0;
        } else if (isdigit(curr)) {
            int skip = curr - '0';
            for(int g = 0; g < skip; g++){
                boardState[index+g] = new emptyPiece(this, false, index, ' ');
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

