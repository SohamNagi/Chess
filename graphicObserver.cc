#include "graphicObserver.h"
#include "window.h"
#include "game.h"

graphicObserver::graphicObserver(Game* sub):
    win{new Xwindow(500,500)}, subject{sub}
{
    grid.assign(64, ' ');
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if (j % 2 == 0){
                win->fillRectangle((j*10), (i*10), 10, 10, 1);
            } else {
                win->fillRectangle((j*10), (i*10), 10, 10, 0);
            }
        }
    }
};

graphicObserver::~graphicObserver(){
    delete win;
}

void graphicObserver::notify(){
    for (int i = 0; i <= 7; ++i) {
        for (int j = 0; j <= 7; ++j) {
            int index = (8*i) + j;
            char curr = subject->getState(index);
            if(curr != grid[index]){
                grid[index] = curr;
                if(j%2 == 0){
                    win->fillRectangle(j,i,10,10,1);
                } else {
                    win->fillRectangle(j,i,10,10,0);
                }
                if (curr != ' '){
                    std::string s(1, curr);
                    win->drawString(i*10, j*10, s);
                }
            }
        }
    }
}
