#include "game.h"
#include <iostream>

using namespace std;

string board_setup(){
    string command;
    string output;
    int empty;
    string turn = "w";
    vector<char> grid;
    grid.resize(64,' ');
    
    while(cin >> command){
        if(command == "+"){
            char piece; std::cin >> piece;
            char ccol; std::cin >> ccol;
            int row; std::cin >> row;
            int col = col - 17;
            grid[(8*row)+col] = piece;
        } else if (command == "-"){
            char piece; std::cin >> piece;
            char ccol; std::cin >> ccol;
            int row; std::cin >> row;
            int col = col - 17;
            grid[(8*row)+col] = ' ';
        } else if (command == "="){
            string color; std::cin >> color;
            if (color == "white"){
                turn = "w";
            } else if (color == "black"){
                turn = "b";
            }
        } else if (command == "fen"){
            std::cin >> output;
            return output;
        } else if (command == "done"){
            break;
        }
    }

    for(int i = 7; i >= 0; i--){
        for(int j = 0; j < 8; j++){
            if(grid[(8*i) + j] == ' '){
                empty++;
            } else {
                if(empty > 0){
                    auto s = std::to_string(empty);
                    output += s;
                    empty = 0;
                }
                output += grid[(8*i) + j];
            }
        }
        output += "/";
    }

    return output + " " + turn + " ---- - 0 1";
}

int main(int argc, char const *argv[])
{
    cout << "+-----------------------------------------------------+" << endl;
    cout << "|   _____                  _____ _                    |" << endl;
    cout << "|  / ____|    _     _     / ____| |                   |" << endl;
    cout << "| | |       _| |_ _| |_  | |    | |__   ___  ___ ___  |" << endl;
    cout << "| | |      |_   _|_   _| | |    | '_ \\ / _ \\/ __/ __| |" << endl;
    cout << "| | |____    |_|   |_|   | |____| | | |  __/\\__ \\__ \\ |" << endl;
    cout << "|  \\_____|                \\_____|_| |_|\\___||___/___/ |" << endl;
    cout << "+-----------------------------------------------------+ " << endl; 
    cout << "|    BY ABDULLAH SHAHID, ARIQ ISHFAR   & SOHAM NAGI   |" << endl;
    cout << "+-----------------------------------------------------+" << endl;

    int black_wins = 0;
    int white_wins = 0;
    int draw = 0;

    string command;
    
    while(cin >> command){
         string board = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        if (command == "setup"){
            string board = board_setup();
        } else if (command == "game"){
            string white;
            cin >> white;
            string black;
            cin >> black;
            Game* round = new Game(board, white, black);
            round->notifyObservers();
            round->start();
            int score = round->getResult();
            if (score == -1){
                ++black_wins;
            } else if (score == 0){
                ++draw;
            } else {
                ++white_wins;
            }
        } else if (command == "quit"){
            break;
        }
    }
    cout << "Final Score:" << endl;
    cout << "White: " << white_wins << endl;
    cout << "Black: " << black_wins << endl;
}
