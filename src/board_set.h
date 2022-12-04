#ifndef __BOARDSET_H__
#define __BOARDSET_H__
#include <string>
#include "board.h"


Board* board_setup(std::vector<char>* start, std::string set_turn, int status);

#endif
