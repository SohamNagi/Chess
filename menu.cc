#include "game.h"
#include <iostream>
using namespace std;

// string board_setup(){
//     return "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
// }

int main(int argc, char const *argv[])
{
    
    int black_wins = 0;
    int white_wins = 0;
    int draw = 0;

    string command;
    
    while(cin >> command){
        string board = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

        if (command == "setup"){
            // string board = board_setup();
        } else if (command == "game"){
            string white;
            string black;
            std::cout << "test 1" << std::endl;
            Game* round = new Game(board, white, black);
            std::cout << "test 2" << std::endl;
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
