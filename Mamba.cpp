#include "Mamba.h"

Mamba::Mamba() { snakeHead.setCoord(mambaArea/2, mambaArea/2); }
int Mamba::getSpeed() { return speed; }
int Mamba::getArea() { return mambaArea; }
bool Mamba::collision() // checks for collisions
{
    // Border Collision //
    if (headX() < 1 || headX() > mambaArea-2) // right/left edges
        enterWall();
    else if (headY() < 1 || headY() > mambaArea-2) // top/bottom edges
        enterWall();
        
    // Self Collision // 
    for (int i = 0; i < snakeBody.size(); i++) { // head collides with self
        if (snakeHead[0] == snakeBody[i][0] && snakeHead[1] == snakeBody[i][1]) 
            return true;
    }  
    // Rock Collision //
    if (headX() == 5 && headY() == 4) return true;
    else if(headX() == 15 && headY() == 14) return true;
    else if(headX() == 3 && headY() == 16) return true;

    return false; // no collisions
}
void Mamba::enterWall() // Function for passing through wall
{ 
    if (headY() < 0)
        snakeHead[1] = mambaArea-1; 
    else if (headY() > mambaArea-1) 
        snakeHead[1] = 0;
    else if (headX() < 0) 
        snakeHead[0] = mambaArea-1;
    else if (headX() > mambaArea-1) 
        snakeHead[0] = 0;
}