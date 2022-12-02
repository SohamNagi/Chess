#include "game.h"
#include <iostream>
#include "window.h"
#include "renderUtil.h"

using namespace std;

string board_setup(){
    auto win = new Xwindow{500,500};
    win->drawStringBold(90, 35, "CS246 - C++ Chess");
    vector<char> opti;
    opti.assign(64, ' ');
    char file = 'A';
    int shift = 50;
    for(int i = 0; i < 8; i++){
        win->drawStringBold(20, i*50 + 35 + shift, std::to_string(8-i));
        for(int j = 0; j < 8; j++){
            if ((j+i) % 2 != 0){
                win->fillRectangle((i*50) + shift, (j*50) + shift, 50, 50, 4); // Print Black Square
            }
        }
        std::string s(1,file);
        win->drawStringBold((i*50) + 10 + shift, 490, s);
        file++;
    }
    win->fillRectangle(shift, shift, 400, 5, 1);
    win->fillRectangle(shift, shift, 5, 400, 1);
    win->fillRectangle(400+shift, shift, 5, 405, 1);
    win->fillRectangle(shift, 400+shift, 400, 5, 1);

    string command;
    string output;
    int empty = 0;
    string turn = " w";
    vector<char> grid;
    grid.resize(64,' ');

    cout << "You are in setup mode, here are your commands:" << endl;
    cout << "\"+ piece square\" to place a piece. " << endl;
    cout << "\"- square\" to remove a piece " << endl;
    cout << "\"= color\" to set turn " << endl;
    cout << "\"fen fen_string\" to build a board from a fen string" << endl;
    cout << "\"done\" to return to main menu and start a game. " << endl;

    while(cin >> command){
        if(command == "+"){
            char piece; std::cin >> piece;
            char file; std::cin >> file;
            int row; std::cin >> row;
            grid[(8*(row-1))+mapFiles(file)] = piece;
            txt_printer(grid);
            gfx_printer(win,grid, &opti);
        } else if (command == "-"){
            char piece; std::cin >> piece;
            char file; std::cin >> file;
            int row; std::cin >> row;
            grid[(8*(row-1))+mapFiles(file)] = ' ';
            txt_printer(grid);
            gfx_printer(win,grid,&opti);
        } else if (command == "="){
            string color; std::cin >> color;
            if (color == "white"){
                turn = " w";
            } else if (color == "black"){
                turn = " b";
            }
        } else if (command == "fen"){
            std::cin >> output;
            std::cin >> turn;
            delete win;
            output += " ";
            output += turn;
            std::cout << output << endl;
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
        if(empty != 0){
            auto s = std::to_string(empty);
            output += s;
            empty = 0;
        }
        if(i != 0){
            output += "/";
        }
    }
    delete win;
    output += turn;
    return output;
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
    cout << "|    BY ABDULLAH SHAHID, ARIQ ISHFAR, & SOHAM NAGI    |" << endl;
    cout << "+-----------------------------------------------------+" << endl;

    int black_wins = 0;
    int white_wins = 0;
    int draw = 0;

    string command;
    string board = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    
    cout << "Welcome to chess++!" << endl;
    cout << "You are in the main menu, here are your commands:" << endl;
    cout << "\"game\" to start a round of chess. " << endl;
    cout << "\"setup\" to enter setup mode. " << endl;
    cout << "\"quit\" to end the program and see results. " << endl;

    while(cin >> command){
        if (command == "setup"){
            board = board_setup();
        } else if (command == "game"){
            cout << board << endl;
            if(board == "8/8/8/8/8/8/8/8 w"){
                board = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
            }
            string white;
            string black;

            cout << "Select if white is to be a human player or a computer player from levels 1 to 4."  << endl;
            cout << "(human/1/2/3/4):" << endl;

            while(true) {
                cin >> white;

                if (cin.fail() || white == "human" || white == "1" || white == "2" || white == "3" || white == "4" ) {
                    break;
                }
                
                cout << "Invalid command for white! Try again." << endl;
            }

            cout << "Select if black is to be a human player or a computer player from levels 1 to 4."  << endl;
            cout << "(human/1/2/3/4):" << endl;

            while(true) {
                cin >> black;

                if (cin.fail() || white == "human" || white == "1" || white == "2" || white == "3" || white == "4" ) {
                    break;
                }
                
                cout << "Invalid command for black! Try again." << endl;
            }


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
            delete round;
            board = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        } else if (command == "quit"){
            break;
        } else {
            cout << "Invalid command! Try again!" << endl;
        }
    }
    cout << "Final Score:" << endl;
    cout << "White: " << white_wins << endl;
    cout << "Black: " << black_wins << endl;
}
