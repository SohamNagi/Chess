#include "graphicObserver.h"
#include "window.h"

graphicObserver::graphicObserver(int t, int b, int l, int r, Studio* sub):
    top{t}, bottom{b}, left{l}, right{r}, rows{(b-t)+1}, cols{(r-l)+1}, win{new Xwindow(cols*10,rows*10)}, subject{sub}
{
    grid.assign(((cols*bottom) + right + 1), 0);
};

graphicObserver::~graphicObserver(){
    delete win;
}

int graphicObserver::charColor(char c){
    if (c == ' ') { // White for blank
        return 0;
    } else if (48 <= c && c <= 57){ // Blue for number
        return 4;
    } else if (65 <= c && c <= 90){ // Green for upper-case
        return 3;
    } else if (97 <= c && c <= 122) { // Red for lower-case
        return 2;
    } else { // Black for anything else
        return 1;
    }
}

void graphicObserver::notify(){
    for (int i = top; i <= bottom; ++i) {
        for (int j = left; j <= right; ++j) {
            int c = charColor(subject->getState(i,j));
            if (grid[(cols * i) + j] != c){
                grid[(cols * i) + j] = c; 
                win->fillRectangle((j*10)-(left * 10), (i*10)-(top * 10), 10, 10, c);  
            }
        }
    }
}
