#include "angle.hpp"
#include <iostream>
using namespace std;

Angle :: Angle(int id, Line a, Line b) : Shape(id), l1(a), l2(b){}

Line Angle :: getl1() const{
    return l1;
}

Line Angle :: getl2() const{
    return l2;
}

void Angle :: draw(char canvas[][80]){
    l1.draw(canvas);
    l2.draw(canvas);
}

