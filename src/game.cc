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
    i->updateMoves();
  }
  std::cout << "Command:" << std::endl;
  while(std::cin >> command){
    std::cout << "Command:" << std::endl;
    if (command == "move"){
      bool skip = false;
      try {
        if (board->moves % 2 == 0){
          whitePlayer->getmove();
        } else {
          blackPlayer->getmove();
        }
      } catch (std::invalid_argument& e) {
        std::cout << "" << e.what() << std::endl;
        skip = true;
      }
      if (skip) continue;
      skip = false;
      board->halfMoves += 1;
      board->whiteTurn = !board->whiteTurn;
      if (board->whiteTurn) board->moves += 1;
      notifyObservers();
      for (auto i: board->boardState) {
        i->updateMoves();
      }
    } else if (command == "resign"){
      if (board->whiteTurn){
        result = -1;
      } else {
        result = 1;
      }
      //DELETE OBSERVERS AND PIECES BOARD
      delete board;
      for (auto i: observers){
        delete i;
      }
      delete whitePlayer;
      delete blackPlayer;
      break;
    } else if (command == "print"){
      notifyObservers();
    }
  }
  return;
}

char Game::getState(int index){
  return board->boardState[index]->type;
};
