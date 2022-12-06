#include "computer.h"
#include "player.h"
#include <vector>
#include "pieces.h"
#include <cstdlib>

Computer::Computer(bool isWhite, Board* board): Player(isWhite, board) {};
void Computer::promote(int piece) {
    delete board->boardState[piece];
    board->boardState[piece] = new Queen(board, board->boardState[piece]->isWhite, piece, 'Q');
}

BestMove::BestMove(int start, int end): start{start}, end{end}, no_moves{false} {};
BestMove::BestMove(bool no_moves): start{0}, end{0}, no_moves{no_moves} {};

// COMPUTER SHOULD CHANGE TURN AFTER MOVING board->whiteTurn = !board->whiteTurn;
void Computer::getmove(Board* test) {
    BestMove move = this->evaluate(test);

    if (!(move.no_moves)) {
        this->move(move.start, move.end, test);
    } 

    // Add code for checkmate and stalemate
}

// Level1 function
Level1::Level1(bool isWhite, Board* board): Computer(isWhite, board) {};


BestMove Level1::evaluate(Board* test) {
    std::vector<BestMove> moves;

    for (int i = 0; i < 64; ++i) { 
        Pieces* curr = test->boardState.at(i);

        if (curr->type == ' ' || curr->isWhite != test->whiteTurn) {
            continue;
        }

        for (auto j = curr->legalmoves.begin(); j < curr->legalmoves.end(); ++j) {
            moves.emplace_back(BestMove(i, *j));
        }
    }

    if (moves.size() == 0) {
        return BestMove(true);
    } else {
        std::srand(time(0));
        int index = std::rand() % moves.size();
        return moves[index];

    }
}

// Level 2 functions

Level2::Level2(bool isWhite, Board* board): Computer(isWhite,board) {};

BestMove Level2::evaluate(Board *test) {
    std::vector<BestMove> preferred; // Captures and checks go here
    std::vector<BestMove> moves;

    for (int i = 0; i < 64; ++i) { 
        Pieces* curr = test->boardState.at(i);

        if (curr->type == ' ' || curr->isWhite != test->whiteTurn) {
            continue;
        }

        for (auto j = curr->legalmoves.begin(); j < curr->legalmoves.end(); ++j) {
            
            if (test->boardState.at(*j)->isWhite != this->isWhite) // Capture {
                preferred.emplace_back(BestMove(i, *j));
            else {
                moves.emplace_back(BestMove(i, *j));
            }
            }
            
        }

    if (preferred.size() != 0) {
        std::srand(time(0));
        int index = std::rand() % preferred.size();
        return preferred[index];
    } else if (moves.size() != 0) {
        std::srand(time(0));
        int index = std::rand() % moves.size();
        return moves[index];
    } else {
        return BestMove(true);
    }
}

// Level 3 functions

Level3::Level3(bool isWhite, Board* board): Computer(isWhite,board) {};

BestMove Level3::evaluate(Board *test) {
    std::vector<BestMove> preferred; // Captures, avoiding captures and checks go here
    std::vector<BestMove> moves;
    bool attacked_square[64];

    // Initializing loop
    for (int i = 0; i < 64; ++i) {
        attacked_square[i] = false;
    }

    Pieces* curr;

    // Loop for getting squares attacked by opponent player
    for (int i = 0; i < 64; ++i) {
        curr = test->boardState.at(i);

        if (curr->isWhite != test->whiteTurn) {
            auto start = curr->legalmoves.begin();
            auto end = curr->legalmoves.end();
            
            for (auto i = start; i < end; ++i) {
                attacked_square[*i] = true;
            }
        }
    }

    // Loop for getting moves of own player
    for (int i = 0; i < 64; ++i) { 
        curr = test->boardState.at(i);

        if (curr->type == ' ' || curr->isWhite != test->whiteTurn){
            continue;
        }

        auto start = curr->legalmoves.begin();
        auto end = curr->legalmoves.end();

        for (auto j = start; j < end; ++j) {
            
            if (test->boardState.at(*j)->isWhite != this->isWhite) { // Capture {
                preferred.emplace_back(BestMove(i, *j));
            } else if (!(attacked_square[*j])) {
                preferred.emplace_back(BestMove(i, *j));
            } else {
                moves.emplace_back(BestMove(i, *j));
            }
            }
            
        }

    if (preferred.size() != 0) {
        std::srand(time(0));
        int index = std::rand() % preferred.size();
        return preferred[index];
    } else if (moves.size() != 0) {
        std::srand(time(0));
        int index = std::rand() % moves.size();
        return moves[index];
    } else {
        return BestMove(true);
    }
}