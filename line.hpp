#ifndef LINE_HPP
#define LINE_HPP

#include "point.hpp"
using namespace std;

class Angle;

class Line : public Shape{
    private:
        Point p1;
        Point p2;
    public:
        Line(int id, Point a, Point b);
        Point getp1() const;
        Point getp2() const;    
        void draw(char canvas[][80]) override;
        Angle* operator+(const Line& other) const;
};

#endif