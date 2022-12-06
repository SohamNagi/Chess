#include "board_set.h"
#include <string>
#include "renderUtil.h"
#include <vector>
#include "board.h"
#include "pieces.h"


using namespace std;

Board* board_setup(vector<char>* start, string set_turn, int status){
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
    string turn = set_turn;
    vector<char> grid;
    grid.resize(64,' ');
    if(status == -1){
        grid = *start;
    }
    Board* final_board = nullptr;
    system("clear");
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
                std::cout << "Set turn to white!" << std::endl;
                turn = " w";
            } else if (color == "black"){
                std::cout << "Set turn to black!" << std::endl;
                turn = " b";
            }
        } else if (command == "fen"){
            std::cin >> output;
            std::cin >> turn;
            delete win;
            output += " ";
            output += turn;
            std::cout << output << endl;
            system("clear");
            final_board = new Board(output);
            if(!final_board->isValid()){
                delete final_board;
                std::cout << "Your board is invalid, please fix it!" << std::endl;
                final_board = board_setup(&grid, turn, -1);
            }
            for(auto i: final_board->boardState){
                i->moved = true;
            }
            return final_board;
        } else if (command == "done"){
            system("clear");
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
    if(output == "8/8/8/8/8/8/8/8"){
        return new Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    }
    output += turn;
    final_board = new Board(output);
    if(!final_board->isValid()){
        delete final_board;
        std::cout << "Your board is invalid, please fix it!" << std::endl;
        final_board = board_setup(&grid, turn, -1);
    }

    for(auto i: final_board->boardState){
        i->moved = true;
    }
    
    return final_board;
}
