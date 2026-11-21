#include "triangle.hpp"
#include <iostream>
#include <cmath>
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

Triangle Triangle :: mirrored(int side){
    Line mirrorLine = l1;
    if (side == 2){
        mirrorLine = l2;
    }
    else if (side == 3){
        mirrorLine = l3;
    }
    else if (side != 1){
        cout << "Invalid side number" << endl;
        return *this;
    }
    Point a = mirrorLine.getp1();
    Point b = mirrorLine.getp2();
    double ax = a.getx();
    double ay = a.gety();
    double bx = b.getx();
    double by = b.gety();
    Line otherLine = l2;
    if (side == 2 || side == 3){
        otherLine = l1;
    }
    Point p = otherLine.getp1();
    if ((p.getx() == a.getx() && p.gety() == a.gety()) ||
        (p.getx() == b.getx() && p.gety() == b.gety())){
        p = otherLine.getp2();
    }
    if ((p.getx() == a.getx() && p.gety() == a.gety()) ||
        (p.getx() == b.getx() && p.gety() == b.gety())){
        cout << "Invalid triangle" << endl;
        return *this;
    }
    double px = p.getx();
    double py = p.gety();
    double dx = bx - ax;
    double dy = by - ay;
    double d = sqrt(dx * dx + dy * dy);
    if (d == 0){
        cout << "Invalid mirror line" << endl;
        return *this;
    }
    double ux = dx / d;
    double uy = dy / d;
    double x = px - ax;
    double y = py - ay;
    double newx = (2 * ux * ux - 1) * x + (2 * ux * uy) * y;
    double newy = (2 * ux * uy) * x + (2 * uy * uy - 1) * y;
    newx = newx + ax;
    newy = newy + ay;
    Point newPoint(0, round(newx), round(newy));
    Line line1(0, a, b);
    Line line2(0, b, newPoint);
    Line line3(0, newPoint, a);
    Triangle reflected(0, line1, line2, line3);
    return reflected;
}

Triangle* Triangle :: getprevTriangle() const{
    return prevTriangle;
}

void Triangle :: setprevTriangle(Triangle* triangle){
    prevTriangle = triangle;
}
