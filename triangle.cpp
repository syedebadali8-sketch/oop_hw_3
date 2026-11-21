#include "triangle.hpp"
#include <iostream>
using namespace std;

Triangle :: Triangle(int id, Line a, Line b, Line c) : Shape(id), l1(a), l2(b), l3(c){}

Line Triangle :: getl1() const{
    return l1;
}

Line Triangle :: getl2() const{
    return l2;
}

Line Triangle :: getl3() const{
    return l3;
}

void Triangle :: draw(char canvas[][80]){
    l1.draw(canvas);
    l2.draw(canvas);
    l3.draw(canvas);
}
