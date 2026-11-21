#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "triangle.hpp"
using namespace std;

class Rectangle : public Shape{
    public:
        Rectangle(int id, Triangle first, Triangle second);
        Rectangle(const Rectangle& other);
        Rectangle& operator=(const Rectangle& other);
        ~Rectangle();
        void draw(char canvas[][80]) override;
};

#endif
