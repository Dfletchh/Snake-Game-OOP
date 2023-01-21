#ifndef COORD_H
#define COORD_H

#include <vector>

class Coord
{
    private:
        std::vector<int> coord;
    public:
        int& operator[] (int i) { return coord[i]; }
        void setCoord(int x, int y) {
            coord.push_back(y);
            coord.push_back(x);
        }
};

#endif