
#ifndef ANGLE_HPP
#define ANGLE_HPP

#include "line.hpp"
using namespace std;

class Angle : public Shape{
    private:
        Line l1;
        Line l2;
    public:
        Angle(int id, Line a, Line b);
        Line getl1() const;
        Line getl2() const;
        virtual void draw(char canvas[][80]) override;
};

#endif
