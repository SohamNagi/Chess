#include "observer.h"

class Game;

class textObserver : public Observer{
    Game* subject;
    public:
        textObserver(Game* sub);
        void notify() override;
        ~textObserver() = default;
};
