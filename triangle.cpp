#include "triangle.hpp"
#include "rectangle.hpp"
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
    if (prevTriangle != triangle){
        delete prevTriangle;
        prevTriangle = triangle;
    }
}

Triangle :: ~Triangle(){
    delete prevTriangle;
    prevTriangle = nullptr;
}

Triangle :: Triangle(const Triangle& other) : Shape(other.ID), l1(other.l1), l2(other.l2), l3(other.l3){
    if (other.prevTriangle == nullptr){
        prevTriangle = nullptr;
    }
    else{
        prevTriangle = new Triangle(*other.prevTriangle);
    }
}

Triangle& Triangle:: operator=(const Triangle& other){
    if (this == &other){
        return *this;
    }
    delete prevTriangle;
    prevTriangle = nullptr;
    ID = other.ID;
    l1 = other.l1;
    l2 = other.l2;
    l3 = other.l3;
    if (other.prevTriangle != nullptr){
        prevTriangle = new Triangle(*other.prevTriangle);
    }

    return *this;
}

bool samePoint(Point a, Point b){
    return a.getx() == b.getx() && a.gety() == b.gety();
}

bool hasPoint(Point p, Point a, Point b, Point c){
    return samePoint(p, a) || samePoint(p, b) || samePoint(p, c);
}

Rectangle* Triangle :: operator+(const Triangle& other) const{
    Point a = l1.getp1();
    Point b = l1.getp2();
    Point c = l2.getp1();

    if (samePoint(c, a) || samePoint(c, b)){
        c = l2.getp2();
    }
    Point d = other.l1.getp1();
    Point e = other.l1.getp2();
    Point f = other.l2.getp1();
    if (samePoint(f, d) || samePoint(f, e)){
        f = other.l2.getp2();
    }

    if (samePoint(a, b) || samePoint(a, c) || samePoint(b, c) ||
        samePoint(d, e) || samePoint(d, f) || samePoint(e, f)){
        cout << "Invalid triangle" << endl;
        return nullptr;
    }
    int cross1 =
        (int)(b.getx() - a.getx()) * (c.gety() - a.gety()) -
        (int)(b.gety() - a.gety()) * (c.getx() - a.getx());

    int cross2 =
        (int)(e.getx() - d.getx()) * (f.gety() - d.gety()) -
        (int )(e.gety() - d.gety()) * (f.getx() - d.getx());
    if (cross1 == 0 || cross2 == 0){
        cout << "Invalid triangle" << endl;
        return nullptr;
    }

    int count = 0;
    if (hasPoint(a, d, e, f)){
        count++;
    }
    if (hasPoint(b, d, e, f)){
        count++;
    }
    if (hasPoint(c, d, e, f)){
        count++;
    }

    if (count != 2){
        cout << "Triangles must share one side" << endl;
        return nullptr;
    }
    Point shared1(0, 0, 0);
    Point shared2(0, 0, 0);
    Point corner1(0, 0, 0);
    Point corner2(0, 0, 0);

    if (!hasPoint(a, d, e, f)){
        corner1 = a;
        shared1 = b;
        shared2 = c;
    }
    else if (!hasPoint(b, d, e, f)){
        corner1 = b;
        shared1 = a;
        shared2 = c;
    }
    else{
        corner1 = c;
        shared1 = a;
        shared2 = b;
    }

    if (!hasPoint(d, a, b, c)){
        corner2 = d;
    }
    else if (!hasPoint(e, a, b, c)){
        corner2 = e;
    }
    else{
        corner2 = f;
    }
    if (shared1.getx() + shared2.getx() != corner1.getx() + corner2.getx() ||
        shared1.gety() + shared2.gety() != corner1.gety() + corner2.gety()){
        cout << "Triangles do not form a Rectangle" << endl;
        return nullptr;
    }
    int dx1 = shared1.getx() - corner1.getx();
    int dy1 = shared1.gety() - corner1.gety();
    int dx2 = shared2.getx() - corner1.getx();
    int dy2 = shared2.gety() - corner1.gety();

    if (dx1 * dx2 + dy1 * dy2 != 0){
        cout << "Triangles do not form a Rectangle" << endl;
        return nullptr;
    }
    Rectangle* newRectangle = new Rectangle(0, *this, other);
    return newRectangle;
}

void Triangle :: printType() const{
    cout << "Triangle";
}


