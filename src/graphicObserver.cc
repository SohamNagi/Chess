#include "graphicObserver.h"
#include "window.h"
#include "game.h"

int BOARD_COL = 8;
int HIGHLIGHT = 4;

std::string parse(char input){
    if(input == 'K'){
                return "k";
            } else if (input == 'Q'){
                return "q";
            } else if (input == 'P'){
                return "p";
            } else if (input == 'N'){
                return "h";
            } else if (input == 'R'){
                return "r";
            } else if (input == 'B'){
                return "b";
            } else if (input == 'k'){
                return "l";
            } else if (input == 'q'){
                return "w";
            } else if (input == 'p'){
                return "o";
            } else if (input == 'n'){
                return "j";
            } else if (input == 'r'){
                return "t";
            } else if (input == 'b'){
                return "n";
            }
            return "x";
}


// Constructs Board and Window
graphicObserver::graphicObserver(Game* sub):
win{new Xwindow(500,500)}, subject{sub}
{
    win->drawStringBold(90, 35, "CS246 - C++ Chess");
    grid.assign(64, ' ');
    int shift = 50;
    char file = 'A';
    for(int i = 0; i < 8; i++){
        win->drawStringBold(20, i*50 + 35 + shift, std::to_string(8-i));
        for(int j = 0; j < 8; j++){
            if ((j+i) % 2 != 0){
                win->fillRectangle((i*50) + shift, (j*50) + shift, 50, 50, BOARD_COL); // Print Black Square
            }
        }
        std::string s(1,file);
        win->drawStringBold((i*50) + 10 + shift, 490, s);
        file++;
    }
};

graphicObserver::~graphicObserver(){
    delete win;
}

Xwindow* graphicObserver::getWin(){
    return win;
};

void graphicObserver::square_highlight(int index){
    int shift = 50;
    int x = index % 8;
    int y = (index-(index % 8)) /8;
    win->BlankRectangle((x*50)+shift,400-(y*50),50,50,HIGHLIGHT);
}

void graphicObserver::square_unhighlight(int index){
    int shift = 50;
    int x = index % 8;
    int y = (index-(index % 8)) / 8;
    if ((x+y) % 2 != 0){
        win->BlankRectangle((x*50)+shift,400-(y*50),50,50,0);
    } else {
        win->BlankRectangle((x*50)+shift,400-(y*50),50,50,BOARD_COL);
    }
}

void graphicObserver::notify(){
    int shift = 50;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            int index = (8*(7-j)) + (i); // Printing direction is not same as board so we offset
            char curr = subject->getState(index); // Fetch Current Char
            if(curr != grid[index]){ // Optimization - Store board and only print if changed
                if ((j+i) % 2 != 0){
                    win->fillRectangle((i*50) + shift, (j*50) + shift, 50, 50, BOARD_COL); // Print Black Square
                } else {
                    win->fillRectangle((i*50) + shift, (j*50) + shift, 50, 50, 0);
                }
                grid[index] = curr; // Reset Value in Optimization index
                std::string s(1, curr);
                //win->drawString(i*50 + 15 + shift, j*50 + 35 + shift, s); // Print Piece Name
                 win->drawSym(i*50 + 15 + shift, j*50 + 35 + shift, parse(curr)); // Print Piece Name
            }
        }
    }
    // Print Board Borders
    win->fillRectangle(shift, shift, 400, 5, 1);
    win->fillRectangle(shift, shift, 5, 400, 1);
    win->fillRectangle(400+shift, shift, 5, 405, 1);
    win->fillRectangle(shift, 400+shift, 400, 5, 1);
    // Mouse testing
    //while(1){int status = 1;win->getMouseData(status);if(status == -1){break;}}
}


// std::string getSqaureFromMouse(int mouse_x, int mouse_y){
//     int rounded_x = (mouse_x/50)*50;
//     int rounded_y = (mouse_y/50)*50;
//     char file = (rounded_x - 50)/50 + 'A'; 
//     int rank = 8 - ((rounded_y - 50)/50);
//     std::string output;
//     output+= file;
//     output += std::to_string(rank);
// }

