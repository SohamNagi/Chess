#ifndef GAME.H
#define GAME.H

#include <vector>
#include <string>
#include "board.h"

class Player;

class Game {

    // Fields for Game
    private:
        std::vector<std::string> history;
        Player* whitePlayer;
        Player* blackPlayer;
        int result;
    
    public:
        Board* boardstate;

    // Methods for Game:
        Game(std::string fen, std::string white, std::string black);
        void undo();
        void makeMoves();
        void start();
        int getResult();

};

#endif


