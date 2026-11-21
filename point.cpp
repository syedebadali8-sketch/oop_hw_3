#include "point.hpp"
#include <iostream>
using namespace std;

Point :: Point(int id, int x_val, int y_val) : Shape(id){
    x = x_val;
    y = y_val;
}

int Point :: getx() const{
    return x;
}

int Point :: gety() const{
    return y;
}

void Point :: draw(char canvas[][80]){
    if (x >= 0 && x < 80 && y >= 0 && y < 40){
        canvas[y][x] = 'o';
    }
}


