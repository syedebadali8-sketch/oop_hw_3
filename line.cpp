#include "line.hpp"
#include <iostream>
using namespace std;


Line :: Line(int id, Point a, Point b) : Shape(id), p1(a), p2(b){}

Point Line :: getp1() const{
    return p1;
}

Point Line :: getp2() const{
    return p2;
}

void Line :: draw(char canvas[][80]){
    int x1 = p1.getx();
    int y1 = p1.gety();
    int x2 = p2.getx();
    int y2 = p2.gety();
    
    if (y1 == y2){
        for (int x = x1; x <= x2; x++){
            if (x >= 0 && x < 80 && y1 >= 0 && y1 < 40){
                canvas[y1][x] = '-';
            }
        }
    }

}



