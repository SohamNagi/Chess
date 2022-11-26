#include "observer.h"
#include "studio.h"
#include "window.h"

class graphicObserver : public Observer{
    int top, bottom, left, right;
    int rows, cols;
    Xwindow* win;
    Studio* subject;
    std::vector<int> grid;
    public:
        int charColor(char c);
        graphicObserver(int t, int b, int l, int r, Studio* sub);
        void notify() override;
        virtual ~graphicObserver();
};
