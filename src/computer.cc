#include "computer.h"
#include "player.h"
#include "pieces.h"
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <random>

Computer::Computer(bool isWhite, Board* board):
    Player{isWhite, board}, personalMoves{std::vector<int> (std::vector<int> (0))}
{};

void Computer::promote(int piece) {
    delete board->boardState[piece];
    board->boardState[piece] = new Queen(board, board->boardState[piece]->isWhite, piece, 'Q');
}

int returnWeightLevel2(Computer* comp, int start, int end) {
    if (!comp->board->boardState[end]->isEmpty) {
        return 5;
    }

    comp->board->boardState[start]->location = end;
    comp->board->boardState[end]->location = start;
    std::iter_swap(comp->board->boardState.begin() + start, comp->board->boardState.begin() + end);
    int checkState = 0;
    checkState = comp->board->boardInCheck(false);
    std::iter_swap(comp->board->boardState.begin() + start, comp->board->boardState.begin() + end);
    comp->board->boardState[start]->location = start;
    comp->board->boardState[end]->location = end;
    for (auto i : comp->board->boardState) {
        i->updateMoves(false);
    }

    if ((comp->isWhite && checkState == -2) || (!comp->isWhite && checkState == 2)) {
        return 20;
    }
    if ((comp->isWhite && checkState == -1) || (!comp->isWhite && checkState == 1)) {
        return 10;
    }
    return 1;
}

int returnWeightLevel3(Computer* comp, int start, int end) {
    if (!comp->board->boardState[end]->isEmpty) {
        return 5;
    }

    comp->board->boardState[start]->location = end;
    comp->board->boardState[end]->location = start;
    std::iter_swap(comp->board->boardState.begin() + start, comp->board->boardState.begin() + end);
    int checkState = 0;
    checkState = comp->board->boardInCheck(false);
    std::iter_swap(comp->board->boardState.begin() + start, comp->board->boardState.begin() + end);
    comp->board->boardState[start]->location = start;
    comp->board->boardState[end]->location = end;
    for (auto i : comp->board->boardState) {
        i->updateMoves(false);
    }
    if ((comp->isWhite && checkState == 2) || (!comp->isWhite && checkState == -2)) {
        return -20;
    }
    if ((comp->isWhite && checkState == -2) || (!comp->isWhite && checkState == 2)) {
        return 20;
    }
    if ((comp->isWhite && checkState == 1) || (!comp->isWhite && checkState == -1)) {
        return -10;
    }
    if ((comp->isWhite && checkState == -1) || (!comp->isWhite && checkState == 1)) {
        return 10;
    }
    return 1;
}

void Computer::updateData(int level) {
    for (auto moveVec : personalMoves) {
        moveVec.clear();
    }
    personalMoves.clear();
    for(auto i: board->boardState){
        if (i->isWhite == isWhite && (i->type == 'K' || i->type == 'k')) {
            ownKingPosition = i->location;
        } 
        if (!i->isEmpty && i->isWhite == isWhite) {
            for (auto move: i->legalmoves) {
                std::vector<int> moveVec = {i->location, move};
                personalMoves.emplace_back(moveVec);
            }
        }
    }

    if (level == 2) {
        int size = personalMoves.size();
        for (int j = 0; j < size; j++) {
            int add = returnWeightLevel2(this, personalMoves[j][0], personalMoves[j][1]);
            personalMoves[j].emplace_back(add);
        }
    }
    
}

// Level1 function
Level1::Level1(bool isWhite, Board* board): Computer(isWhite, board) {};

void Level1::getmove() {
    updateData(1);
    int randomMove = (std::rand() % (personalMoves.size()));
    move(personalMoves[randomMove][0], personalMoves[randomMove][1]);
}

// Level2 function
Level2::Level2(bool isWhite, Board* board): Computer(isWhite, board) {};

void Level2::getmove() {
    updateData(2);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(personalMoves.begin(), personalMoves.end(), g);
    int bestMove = 0;
    int bestMoveWeight = 0;
    int length = personalMoves.size();
    for (int i = 0; i < length; i++) {
        if (personalMoves[i][2] > bestMoveWeight) {
            bestMove = i;
            bestMoveWeight = personalMoves[i][2];
        }
    }
    move(personalMoves[bestMove][0], personalMoves[bestMove][1]);
}

// Level2 function
Level3::Level3(bool isWhite, Board* board): Computer(isWhite, board) {};

void Level3::getmove() {
    updateData(3);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(personalMoves.begin(), personalMoves.end(), g);
    int bestMove = 0;
    int bestMoveWeight = 0;
    int length = personalMoves.size();
    for (int i = 0; i < length; i++) {
        if (personalMoves[i][2] > bestMoveWeight) {
            bestMove = i;
            bestMoveWeight = personalMoves[i][2];
        }
    }
    move(personalMoves[bestMove][0], personalMoves[bestMove][1]);
}