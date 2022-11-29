#include "game.h"
#include "human.h"
#include <string>

Game::Game(std::string fen, std::string white, std::string black):
    boardstate{Board(fen)}
{
    if(white == "human"){
        whitePlayer = new Human();
    }

    if (black = "human"){
        blackPlayer = new human ();
    }
}