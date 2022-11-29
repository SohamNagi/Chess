#ifndef GAME.H
#define GAME.H

#include <vector>
#include <string>

class BoardState;
class Player;

class Game {

    // Fields for Game
    private:
        std::vector<std::string> history;
        Player* whitePlayer;
        Player* blackPlayer;
    
    public:
        BoardState* boardstate;

    // Methods for Game:
        Game(string board, string white, string black);
        void undo();
        void makeMoves();
        void start();


};

#endif


