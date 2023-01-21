#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

class Player
{
    private:
        std::string name;
        int score;
    public:
        Player(std::string name, int score) {
            this->name = name;
            this->score = score;
        }
        std::string playerName() { return name; }
        int playerScore() { return score; } 
};

#endif