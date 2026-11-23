#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include "triangle.hpp"
using namespace std;

class Pentagon;

class Hexagon : public Shape{
    public:
        Hexagon(int id, Triangle first, Triangle second, Triangle third, Triangle fourth);
        Hexagon(const Hexagon& other);
        Hexagon& operator=(const Hexagon& other);
        ~Hexagon();
        void draw(char canvas[][80]) override;
        Pentagon* operator-(const Triangle& other) const;
        void printType() const override;
};

#endif
