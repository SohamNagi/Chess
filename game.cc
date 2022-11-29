#include "game.h"
#include "human.h"
#include <string>
#include <iostream>
#include "textObserver.h"

Game::Game(std::string fen, std::string white, std::string black):
    boardstate{new Board(fen)}, result{11}
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

void Game::start(){
  std::string command;
  while(std::cin >> command){
    if (command == "move"){
      if (boardstate->moves % 2 == 0){
        whitePlayer->getmove();
      } else {
        blackPlayer->getmove();
      }
      notifyObservers();
    } else if (command == "resign"){
      if (boardstate->moves % 2 == 0){
        result = -1;
      } else {
        result = 1;
      }
    }
  }
}

char Game::getState(int index){
  return boardstate->boardState[index]->type;
};
