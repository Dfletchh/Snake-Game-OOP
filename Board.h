#ifndef Board_H
#define Board_H

#include <iostream>

class Board
{
    private:
        int mapArea;
        bool gameOver = false;
        int score;
    public:
        int getArea();
        void setArea(int);
        int getScore();
        bool currentStatus();
        void changeStatus();
        void increaseScore();
        friend void outputScore(Board board);
};

#endif