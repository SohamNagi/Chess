#include "game.h"
#include "human.h"
#include <string>
#include "textObserver.h"

Game::Game(std::string fen, std::string white, std::string black):
    boardstate{new Board(fen)}
{
    attach(new textObserver(this));

    if(white == "human"){
        whitePlayer = new Human(true, boardstate);
    }

    if (black == "human"){
        blackPlayer = new Human(false, boardstate);
    }
}


int Game::getResult(){return result;}

void Game::notifyObservers(){
    for(auto i : observers){
        i->notify();
    }
}


void Game::attach(Observer *o) {
  observers.emplace_back(o);
}

void Game::detach(Observer *o) {
  for (auto it = observers.begin(); it != observers.end(); ++it) {
    if (*it == o) {
      observers.erase(it);
      break;
    }
  }
}

