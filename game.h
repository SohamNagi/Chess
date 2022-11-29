#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include <string>
#include "board.h"
#include "observer.h"

class Piece;
class Player;

class Game {

    // Fields for Game
    private:
        std::vector<std::string> history;
        Player* whitePlayer;
        Player* blackPlayer;
        std::vector<Observer*> observers;
    
    public:
        Board* board;
        int result;
        Game(std::string fen, std::string white, std::string black);
       // void undo();
        // void makeMoves();
        void start();
        int getResult();
        void attach(Observer *o);
        void detach(Observer *o);
        void notifyObservers();
        char getState(int index);
};

#endif
