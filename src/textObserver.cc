#include <iostream>
#include <string>
#include <vector>
#include "game.h"
#include "textObserver.h"
#include "pieces.h"
using namespace std;

textObserver::textObserver(Game* sub):
    subject{sub}
{};


std::string getPieceSym(char name){
    if (name == 'k'){
        return "♔";
    } else if (name == 'q'){
        return "♕";
    } else if (name == 'r'){
        return "♖";
    } else if (name == 'b'){
        return "♗";
    } else if (name == 'n'){
        return "♘";
    } else if (name == 'p') {
        return "♙";
    } else if (name == 'K'){
        return "♚";
    } else if (name == 'Q'){
        return "♛";
    } else if (name == 'R'){
        return "♜";
    } else if (name == 'B'){
        return "♝";
    } else if (name == 'N'){
        return "♞";
    } else {
        return "♟︎";
    }
}


void textObserver::notify(){
    cout << " +-----------------+" << endl;
    for(int i = 7; i >= 0; i--){
        cout << i+1 << "| ";
        for(int j = 0; j < 8; j++){
            char curr = subject->board->boardState.at((8*i)+j)->type;
            if (curr == ' '){
                if ((i+j) % 2 != 0){
                    if(j < 7){
                cout << "  ";
                } else {
                    cout << "  |";;
                }
                    
                } else {
                    if(j < 7){
                cout << "- ";
                } else {
                    cout << "- |";
                }
    
                }
            } else {
                if(j < 7){
                cout << getPieceSym(curr) << " ";
                } else {
                    cout << getPieceSym(curr) << " |";
                }
            }
        }
        cout << endl;
    }
    cout << " +-----------------+" << endl;
    cout << "   A B C D E F G H" << endl;
}

