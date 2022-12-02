#ifndef __GFXOB__
#define __GFXOB__

#include "observer.h"
#include "window.h"
#include <vector>
class Game;

class graphicObserver : public Observer{
    Xwindow* win;
    Game* subject;
    std::vector<char> grid;
    public:
        int charColor(char c);
        graphicObserver(Game* sub);
        void notify() override;
        Xwindow* getWin() override;
        virtual ~graphicObserver();
};

#endif
