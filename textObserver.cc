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

vector<char> fenToBoard(string input){
    int row = 7;
    int col = 0;
    int i = 0;
    vector<char> board(64);
    for(int a = 0; a < 64; a++){
        board[a] = ' ';
    }
    while (input[i] != ' ') {
        char curr = input[i];
        if (curr == '/'){
            row--;
            col = 0;
        } else if (isdigit(curr)) {
            col += curr;
        } else {
            board[(8*row) + col] = curr;
            col++;
        }
        i++;
    }
    return board;
}


void textObserver::notify(){
    cout << " +-----------------+" << endl;
    for(int i = 7; i >= 0; i--){
        cout << i+1 << "| ";
        for(int j = 0; j < 8; j++){
            char curr = subject->board->boardState.at((8*i)+j)->type;
            if (curr == ' '){
                if ((i+j) % 2 == 0){
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
                cout << curr << " ";
                } else {
                    cout << curr << " |";
                }
            }
        }
        cout << endl;
    }
    cout << " +-----------------+" << endl;
    cout << "   A B C D E F G H" << endl;
}

