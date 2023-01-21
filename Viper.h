#ifndef VIPER_H
#define VIPER_H

#include "Snake.h"

class Viper: public Snake
{
    private:
        const static int viperArea = 14;
        const static int speed = 200;
    public:
        Viper() { snakeHead.setCoord(viperArea/2, viperArea/2); }
        int getSpeed() { return speed; }
        int getArea() { return viperArea; }
};

#endif