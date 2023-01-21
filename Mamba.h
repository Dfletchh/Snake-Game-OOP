#ifndef MAMBA_H
#define MAMBA_H

#include "Snake.h"

class Mamba: public Snake
{
    private:
        const static int mambaArea = 20;
        const static int speed = 120;
    public:
        Mamba();
        int getSpeed();
        int getArea();
        bool collision();
        void enterWall();
};

#endif