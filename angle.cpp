#include "angle.hpp"
#include "triangle.hpp"
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

Triangle* Angle :: operator+(const Line& other) const{
    Point a = l1.getp1();
    Point b = l1.getp2();
    Point c = l2.getp1();
    Point d = l2.getp2();
    Point common = a;
    Point p = b;
    Point q = d;
    if (a.getx() == c.getx() && a.gety() == c.gety()){
        common = a;
        p = b;
        q = d;
    }
    else if (a.getx() == d.getx() && a.gety() == d.gety()){
        common = a;
        p = b;
        q = c;
    }
    else if (b.getx() == c.getx() && b.gety() == c.gety()){
        common = b;
        p = a;
        q = d;
    }
    else if (b.getx() == d.getx() && b.gety() == d.gety()){
        common = b;
        p = a;
        q = c;
    }
    else{
        cout << "Invalid Angle" << endl;
        return nullptr;
    }
    Point e = other.getp1();
    Point f = other.getp2();
    bool closes = false;

    if (e.getx() == p.getx() && e.gety() == p.gety() &&
        f.getx() == q.getx() && f.gety() == q.gety()){
        closes = true;
    }
    if (e.getx() == q.getx() && e.gety() == q.gety() &&
        f.getx() == p.getx() && f.gety() == p.gety()){
        closes = true;
    }
    if (closes == false){
        cout << "Line does not close the Triangle" << endl;
        return nullptr;
    }
    int  dx1 = p.getx() - common.getx();
    int  dy1 = p.gety() - common.gety();
    int  dx2 = q.getx() - common.getx();
    int  dy2 = q.gety() - common.gety();
    if (dx1 * dy2 == dy1 * dx2){
        cout << "Points are on the same line" << endl;
        return nullptr;
    }
    Triangle* newTriangle = new Triangle(0, l1, l2, other);

    return newTriangle;
}


