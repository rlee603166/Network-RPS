
#ifndef GAME_H
#define GAME_H

#include <string>
#include "player.h"

bool checkConnection(int& number);

void getMove(Player& player);

void countdown();

void encodeMove(int move, std::string player);

#endif 
