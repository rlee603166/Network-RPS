
#include <string>
#include "player.h"

Player::Player(const std::string& player_name)
    : name(player_name), move(-1)
{
    std::cout << "Welcome " << name << "!" << std::endl;
}


std::string Player::get_name() const
{
    return name;
}

int Player::get_move() const
{
    return move;
}

void Player::set_move(const int& moveName)
{
    move = moveName;
}

