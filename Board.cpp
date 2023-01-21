#include "Board.h"

int Board::getArea() { return mapArea; }
bool Board::currentStatus() { return gameOver; }
int Board::getScore() { return score; }
void Board::increaseScore() { score++; }
void Board::changeStatus() { gameOver = true; }
void Board::setArea(int param) { mapArea = param; }
void outputScore(Board board) { std::cout << "\t\tScore: " << board.score; }