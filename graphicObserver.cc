#include "graphicObserver.h"
#include "window.h"
#include "game.h"

graphicObserver::graphicObserver(Game* sub):
    win{new Xwindow(500,500)}, subject{sub}
{
    std::string header = "CS246 - C++ Chess";
    win->drawString(200, 35, header);
    grid.assign(64, ' ');
    int shift = 50;
    for(int i = 7; i >= 0; i--){
        win->drawString(25, i*50 + 25 + shift, std::to_string(8-i));
        for(int j = 0; j < 8; j++){
            if ((j+i) % 2 != 0){
                win->fillRectangle((i*50) + shift, (j*50) + shift, 50, 50, 4);
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
    for(int i = 7; i > 0; --i){
        for(int j = 0; j < 8; j++){
            int index = (8*i) + j; // **
            char curr = subject->getState(index); // **
            if(curr != grid[index]){
                if ((j+i) % 2 != 0){
                    win->fillRectangle((i*50) + shift, (j*50) + shift, 50, 50, 4);
                } else {
                    win->fillRectangle((i*50) + shift, (j*50) + shift, 50, 50, 0);
                }
                grid[index] = curr;
                std::string s(1, curr);
                win->drawString(i*50 + 25 + shift, j*50 + 25 + shift, s); // **
            }
        }
    }
    win->fillRectangle(shift, shift, 400, 5, 1);
    win->fillRectangle(shift, shift, 5, 400, 1);
    win->fillRectangle(400+shift, shift, 5, 405, 1);
    win->fillRectangle(shift, 400+shift, 400, 5, 1);
}
            
                
                