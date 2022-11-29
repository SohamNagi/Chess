#include "observer.h"

#ifndef __TEXTOB__
#define __TEXTOB__

class Game;

class textObserver : public Observer{
    Game* subject;
    public:
        textObserver(Game* sub);
        void notify() override;
        ~textObserver() = default;
};

#endif