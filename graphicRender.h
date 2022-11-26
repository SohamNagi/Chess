#include "view.h"
#include "window.h"

class graphicObserver : public Viewer{
    Xwindow* win;
    Studio* subject;
    std::vector<int> grid;
    public:
        int charColor(char c);
        graphicObserver(int t, int b, int l, int r, Studio* sub);
        void notify() override;
        virtual ~graphicObserver();
};
