#ifndef FILEIO_H
#define FILEIO_H

#include "Player.h"
#include <fstream>
#include <sstream>
#include <iostream>

class FileIO
{
    private:
        const std::string file = "High_Scores.txt";
    public:
        std::vector<Player> read();
        void write(std::vector<Player> player);
};

#endif