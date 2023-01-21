#ifndef SNAKE_H
#define SNAKE_H

#include "Coord.h"

class Snake
{
    private:
        int advance;
        char direction;
    protected:
        std::vector<Coord> snakeBody;
        Coord snakeHead;
    public:
        void grow();
        void move();
        int headX();
        int headY();
        void coordSwap();
        virtual bool collision();
        virtual int getArea() = 0;
        virtual int getSpeed() = 0;
        bool bodyPosition(int x, int y);
        void setDirection(char dir, int adv);
};

#endif