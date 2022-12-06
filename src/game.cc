#include "game.h"
#include "human.h"
#include <string>
#include <iostream>
#include "textObserver.h"
#include "graphicObserver.h"
#include "board.h"
#include "pieces.h"
#include "computer.h"


Game::Game(Board* brd, std::string white, std::string black):
    board{brd}, result{11}
{
    attach(new textObserver(this));
    graphicObserver* gfx = new graphicObserver(this);
    attach(gfx);

    if (white == "human"){
      whitePlayer = new Human(true, brd, gfx);
    } else if (white == "1") {
      whitePlayer = new Level1(true, brd);
    } else if (white == "2") {
      whitePlayer = new Level2(true, brd);
    } else if (white == "3") {
      whitePlayer = new Level3(true, brd);
    }

    if (black == "human"){
      blackPlayer = new Human(false, brd,gfx);
    } else if (black == "1") {
      blackPlayer = new Level1(false, brd);
    } else if (black == "2") {
      blackPlayer = new Level2(false, brd);
    } else if (black == "3") {
      blackPlayer = new Level3(false, brd);
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
  board->notifyStateChange(true);
  while(std::cin >> command){
    if (command == "move"){    
      bool skip = false;
      try {
        if (board->whiteTurn){
          whitePlayer->getmove(board);
        } else {
          blackPlayer->getmove(board);
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
      board->notifyStateChange(true);    
      int board_state = board->boardInCheck(true);
      if(board_state == -1){
        std::cout << "Black King In Check!" << std::endl;
      } else if (board_state == 1){
        std::cout << "White King In Check!"  << std::endl;
      } else if (board_state == -2){
        std::cout << "Checkmate! Black Loses!" << std::endl;
        result = 1;
        for (auto i: observers){
          delete i;
        }
        delete whitePlayer;
        delete blackPlayer;
        break;
      } else if (board_state == 2){
        std::cout << "Checkmate! White Loses!" << std::endl;
        result = -1;
        for (auto i: observers){
          delete i;
        }
        delete whitePlayer;
        delete blackPlayer;
        break;
      } else if (board_state == 3){
        std::cout << "Stalemate - Game Drawn!" << std::endl;
        result = 0;
        for (auto i: observers){
          delete i;
        }
        delete whitePlayer;
        delete blackPlayer;
        break;
      }
    } else if (command == "resign"){
      if (board->whiteTurn){
        result = -1;
      } else {
        result = 1;
      }
      //DELETE OBSERVERS AND PIECES BOARD
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
