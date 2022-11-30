#include "game.h"
#include "human.h"
#include <string>
#include <iostream>
#include "textObserver.h"
#include "graphicObserver.h"
#include "board.h"
#include "pieces.h"


Game::Game(std::string fen, std::string white, std::string black):
    board{new Board(fen)}, result{11}
{
    attach(new textObserver(this));
    //attach(new graphicObserver(this));

    if(white == "human"){
        whitePlayer = new Human(true, board);
    }

    if (black == "human"){
        blackPlayer = new Human(false, board);
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
  for (auto i: board->boardState) {
    std::cout << i->type << i->location << std::endl;
    i->updateMoves();
  }
  while(std::cin >> command){
    if (command == "move"){
      if (board->moves % 2 == 0){
        whitePlayer->getmove();
      } else {
        blackPlayer->getmove();
      }
      notifyObservers();
    } else if (command == "resign"){
      if (board->moves % 2 == 0){
        result = -1;
      } else {
        result = 1;
      }
    } else if (command == "print"){
      notifyObservers();
    }
  }
}

char Game::getState(int index){
  return board->boardState[index]->type;
};
