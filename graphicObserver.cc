#include "graphicObserver.h"
#include "window.h"
#include "game.h"

// Constructs Board and Window
graphicObserver::graphicObserver(Game* sub):
    win{new Xwindow(500,500)}, subject{sub}
{
    std::string header = "CS246 - C++ Chess";
    win->drawString(200, 35, header);
    grid.assign(64, ' ');
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
};

graphicObserver::~graphicObserver(){
    delete win;
}

void graphicObserver::notify(){
    int shift = 50;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            int index = (8*(7-j)) + (i); // Printing direction is not same as board so we offset
            char curr = subject->getState(index); // Fetch Current Char
            if(curr != grid[index]){ // Optimization - Store board and only print if changed
                if ((j+i) % 2 != 0){
                    win->fillRectangle((i*50) + shift, (j*50) + shift, 50, 50, 4); // Print Black Square
                } else {
                    win->fillRectangle((i*50) + shift, (j*50) + shift, 50, 50, 0);
                }
                grid[index] = curr; // Reset Value in Optimization index
                std::string s(1, curr);
                win->drawString(i*50 + 25 + shift, j*50 + 25 + shift, s); // Print Piece Name
            }
        }
    }
    // Print Board Borders
    win->fillRectangle(shift, shift, 400, 5, 1);
    win->fillRectangle(shift, shift, 5, 400, 1);
    win->fillRectangle(400+shift, shift, 5, 405, 1);
    win->fillRectangle(shift, 400+shift, 400, 5, 1);
}
            
                
                