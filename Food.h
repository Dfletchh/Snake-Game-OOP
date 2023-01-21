#ifndef FOOD_H
#define FOOD_H

#include "Coord.h"
#include <stdio.h>      // NULL 
#include <stdlib.h>     // srand, rand 
#include <time.h>       // time

class Food
{
    private:
        Coord food;
        int area;
    public:
        Food (int area);
        int foodX();
        int foodY();
        void newFood();
};

#endif