#include "pieces.h"
#include "coord.h"


void Pieces::updateMoves() override {
    
}

void Pawn::updateMoves() override {
    
}

void Rook::updateMoves() override {
    // From the Rook to the top of the board
    for (int i = location.y; i < 7; i++) {
        if (board->boardState[location.x][i] == nullptr) {
            legalmoves.emplace_back(Coord{location.x, i});
        } else if (board->boardState[location.x][i]->isWhite != isWhite) {
            legalmoves.emplace_back(Coord{location.x, i});
            break;
        } else break;
    }
    
    // From the Rook to the bottom of the board
    for (int i = location.y; i > 0; i--) {
        if (board->boardState[location.x][i] == nullptr) {
            legalmoves.emplace_back(Coord{location.x, i});
        } else if (board->boardState[location.x][i]->isWhite != isWhite) {
            legalmoves.emplace_back(Coord{location.x, i});
            break;
        } else break;
    }

    // From the Rook to the right of the board
    for (int i = location.x; i > 7; i++) {
        if (board->boardState[i][location.y] == nullptr) {
            legalmoves.emplace_back(Coord{i, location.y});
        } else if (board->boardState[i][location.y]->isWhite != isWhite) {
            legalmoves.emplace_back(Coord{i, location.y});
            break;
        } else break;
    }

    // From the Rook to the left of the board
    for (int i = location.x; i > 0; i--) {
        if (board->boardState[i][location.y] == nullptr) {
            legalmoves.emplace_back(Coord{i, location.y});
        } else if (board->boardState[i][location.y]->isWhite != isWhite) {
            legalmoves.emplace_back(Coord{i, location.y});
            break;
        } else break;
    }

}

void King::updateMoves() override {
    
}

void Queen::updateMoves() override {
    
}

void Knight::updateMoves() override {
    
}

void Bishop::updateMoves() override {
    
}
