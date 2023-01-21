#include "Food.h"

Food::Food (int area)
{
    srand(time(NULL)); // seed program
    this->area = area;
    food.setCoord(rand() % area, rand() % area);
}
void Food::newFood()
{
    food[0] = rand() % area; // new random position in gride
    food[1] = rand() % area;
}
int Food::foodX() { return food[0]; }
int Food::foodY() { return food[1]; }