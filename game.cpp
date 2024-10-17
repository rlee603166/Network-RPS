
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <thread>

#include "player.h"
#include "game.h"

bool checkConnection(int& number)
{
    if (number < 0)
    {
        std::cerr << "Error getting opponent's move!" << std::endl;
        return false;
    }
    else if (number == 0)
    {
        std::cout << "Opponent disconnected" << std::endl;
        return false;
    }
    
    return true;
}


void getMove(Player& player)
{
    int move;
    std::cout << "Enter your move (1 = rock, 2 = paper, 3 = scissors): ";
    std::cin >> move;
    player.set_move(move);
}

void countdown()
{
    std::cout << "Results in .." << std::endl;
    for (int i = 3; i > 0; i--)
    {
        std::cout << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void encodeMove(int move, std::string playerName)
{
    switch(move)
    {
        case 1:
            std::cout << playerName << " chose rock!" << std::endl;
            break;
        case 2:
            std::cout << playerName << " chose paper!" << std::endl;
            break;
        case 3:
            std::cout << playerName << " chose scissors!" << std::endl;
            break;
    }
}
