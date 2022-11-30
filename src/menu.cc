#include "game.h"
#include <iostream>
#include "window.h"

using namespace std;

int mapFiles(char file){
    if(file == 'a'){
        return 0;
    } else if(file == 'b'){
        return 1;
    } else if(file == 'c'){
        return 2;
    } else if (file == 'd'){
        return 3;
    } else if (file == 'e'){
        return 4;
    } else if (file == 'f'){
        return 5;
    } else if (file == 'g'){
        return 6;
    } else {
        return 7;
    }
}

void printer(vector<char> grid){
    cout << " +-----------------+" << endl;
    for(int i = 7; i >= 0; i--){
        cout << i+1 << "| ";
        for(int j = 0; j < 8; j++){
            char curr = grid.at((8*i)+j);
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

void gfx_printer(Xwindow* win, vector<char> grid){
    std::string header = "CS246 - C++ Chess";
    win->drawString(200, 35, header);
    vector<char> opti;
    opti.assign(64, ' ');
    int shift = 50;
    for(int i = 0; i < 8; i++){
        win->drawString(25, i*50 + 25 + shift, std::to_string(8-i));
        for(int j = 0; j < 8; j++){
            if ((j+i) % 2 != 0){
                win->fillRectangle((i*50) + shift, (j*50) + shift, 50, 50, 4); // Print Black Square
            }
        }
    }
    win->fillRectangle(shift, shift, 400, 5, 1);
    win->fillRectangle(shift, shift, 5, 400, 1);
    win->fillRectangle(400+shift, shift, 5, 405, 1);
    win->fillRectangle(shift, 400+shift, 400, 5, 1);
    std::string rows = "A       B       C        D       E        F       G       H";
    win->drawString(25 + shift, 400 + 25 + shift, rows);


    for(int a = 0; a < 8; a++){
        for(int b = 0; b < 8; b++){
            int index = (8*(7-b)) + a; // Printing direction is not same as board so we offset
            char curr = grid.at(index); // Fetch Current Char
            if(curr != opti[index]){ // Optimization - Store board and only print if changed
                if ((b+a) % 2 != 0){
                    win->fillRectangle((a*50) + shift, (b*50) + shift, 50, 50, 4); // Print Black Square
                } else {
                    win->fillRectangle((a*50) + shift, (b*50) + shift, 50, 50, 0);
                }
                opti[index] = curr; // Reset Value in Optimization index
                std::string s(1, curr);
                win->drawString(a*50 + 25 + shift, b*50 + 25 + shift, s); // Print Piece Name
            }
        }
    }
    // Print Board Borders
    win->fillRectangle(shift, shift, 400, 5, 1);
    win->fillRectangle(shift, shift, 5, 400, 1);
    win->fillRectangle(400+shift, shift, 5, 405, 1);
    win->fillRectangle(shift, 400+shift, 400, 5, 1);

}

string board_setup(){
    auto win = new Xwindow{500,500};
    string command;
    string output;
    int empty = 0;
    string turn = "w";
    vector<char> grid;
    grid.resize(64,' ');

    while(cin >> command){
        if(command == "+"){
            char piece; std::cin >> piece;
            char file; std::cin >> file;
            int row; std::cin >> row;
            grid[(8*(row-1))+mapFiles(file)] = piece;
            printer(grid);
            gfx_printer(win,grid);
        } else if (command == "-"){
            char piece; std::cin >> piece;
            char file; std::cin >> file;
            int row; std::cin >> row;
            grid[(8*(row-1))+mapFiles(file)] = ' ';
            printer(grid);
            gfx_printer(win,grid);
        } else if (command == "="){
            string color; std::cin >> color;
            if (color == "white"){
                turn = "w";
            } else if (color == "black"){
                turn = "b";
            }
        } else if (command == "fen"){
            std::cin >> output;
            delete win;
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
    cout << output;
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
    
    while(cin >> command){
        if (command == "setup"){
            board = board_setup();
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
