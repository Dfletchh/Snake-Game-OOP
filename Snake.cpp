#include "Snake.h"

int Snake::headX() { return snakeHead[0]; }
int Snake::headY() { return snakeHead[1]; }
void Snake::grow() // Function to add a segment to the snake
{
    Coord segment;
    segment.setCoord(snakeHead[1], snakeHead[0]); // set prev head to new segment
    snakeBody.push_back(segment);
}
void Snake::move() // Function to continuously moves snake 
{
    switch(direction)
    {
        case 'x': 
                if (snakeBody.size() > 0) coordSwap(); // update segment to the one previous
                snakeHead[0] += advance; // advance head
                break;
        case 'y': 
                if (snakeBody.size() > 0) coordSwap();
                snakeHead[1] += advance;
                break;
    }
}
bool Snake::collision() // Function for wall/self collision tests
{
    // Border Collision //
    if (snakeHead[0] == -1 || snakeHead[0] == 14) // right/left edges
        return true;
    else if (snakeHead[1] == -1 || snakeHead[1] == 14) // top/bottom edges
        return true;
    // Self Collision // 
    for (int i = 0; i < snakeBody.size(); i++) // head collides with self
    { 
        if (snakeHead[0] == snakeBody[i][0] && snakeHead[1] == snakeBody[i][1]) 
            return true;
    }  
    return false;
}
void Snake::coordSwap() // Helper function for move() to update coords
{
    for (int i = snakeBody.size()-1; i > 0; i--) { // start from end 
        snakeBody[i][0] = snakeBody[i-1][0]; // copying coords
        snakeBody[i][1] = snakeBody[i-1][1];
    }
    snakeBody[0][0] = snakeHead[0]; // copy head
    snakeBody[0][1] = snakeHead[1];
}
void Snake::setDirection(char dir, int adv) // Function to change snake direction
{
        direction = dir;
        advance = adv;
}
bool Snake::bodyPosition(int x, int y) // Function used test x, y against each segments coords
{   
    for(int i=0; i<snakeBody.size(); i++) {
        if (snakeBody[i][0] == x && snakeBody[i][1] == y)
            return true;
    }
    return false;
}