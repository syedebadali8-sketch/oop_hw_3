#ifndef POINT_HPP
#define POINT_HPP

#include "shape.hpp"
using namespace std;

class Point : public Shape{
    private:
        int x;
        int y;
    public:
        Point(int id, int x, int y);
        int getx() const;
        int gety() const;
};

#endif