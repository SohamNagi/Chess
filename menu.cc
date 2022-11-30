#include "game.h"
#include <iostream>
using namespace std;

// string board_setup(){
//     return "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
// }

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
        //string board = "8/4b3/4P3/1k4P1/8/ppK5/8/4R3 b - - 1 45";

        if (command == "setup"){
            // string board = board_setup();
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
