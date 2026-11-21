#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "line.hpp"
using namespace std;

class Triangle : public Shape{
    private:
        Line l1;
        Line l2;
        Line l3;
    public:
        Triangle(int id, Line a, Line b, Line c);
        Line getl1() const;
        Line getl2() const;
        Line getl3() const;
        void draw(char canvas[][80]) override;
        Triangle mirrored(int side);
};
#endif
