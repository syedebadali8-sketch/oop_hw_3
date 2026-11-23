#ifndef PENTAGON_HPP
#define PENTAGON_HPP

#include "triangle.hpp"
using namespace std;
class Hexagon;
class Pentagon : public Shape{
    public:
        Pentagon(int id, Triangle first, Triangle second, Triangle third);
        Pentagon(const Pentagon& other);
        Pentagon& operator=(const Pentagon& other);
        ~Pentagon();
        void draw(char canvas[][80]) override;
        Hexagon* operator+(const Triangle& other) const;
};

#endif