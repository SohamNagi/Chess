#ifndef __GFXOB__
#define __GFXOB__

#include "observer.h"
#include "window.h"
#include <vector>
class Game;

class graphicObserver : public Observer{
    Xwindow* win;
    Game* subject;
    std::vector<int> grid;
    public:
        int charColor(char c);
        graphicObserver(int t, int b, int l, int r, Game* sub);
        void notify() override;
        virtual ~graphicObserver();
};

#endif
