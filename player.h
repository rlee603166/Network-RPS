
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>

class Player {
    private:
        std::string name;
        int move;
    public:
        Player(const std::string& player_name);

        // getters
        std::string get_name() const;
        int get_move() const;
        
        // setters
        void set_move(const int& new_move);
};


#endif // !PLAYER_H
