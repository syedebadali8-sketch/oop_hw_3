#include "pentagon.hpp"
#include "rectangle.hpp"
#include "hexagon.hpp"
#include <iostream>
using namespace std;

Pentagon :: Pentagon(int id, Triangle first, Triangle second, Triangle third) : Shape(id){
    Triangle* firstCopy = new Triangle(first);
    Triangle* secondCopy = new Triangle(second);
    Triangle* thirdCopy = new Triangle(third);
    secondCopy->setprevTriangle(firstCopy);
    thirdCopy->setprevTriangle(secondCopy);
    prevTriangle = thirdCopy;
}

Pentagon :: ~Pentagon(){
    delete prevTriangle;
    prevTriangle = nullptr;
}

Pentagon :: Pentagon(const Pentagon& other) : Shape(other.ID){
    if (other.prevTriangle == nullptr){
        prevTriangle = nullptr;
    }
    else{
        prevTriangle = new Triangle(*other.prevTriangle);
    }
}

Pentagon& Pentagon :: operator=(const Pentagon& other){
    if (this == &other){
        return *this;
    }
    Triangle* temp = nullptr;
    if (other.prevTriangle != nullptr){
        temp = new Triangle(*other.prevTriangle);
    }
    delete prevTriangle;
    ID = other.ID;
    prevTriangle = temp;
    return *this;
}

void Pentagon :: draw(char canvas[][80]){
    Triangle* current = prevTriangle;
    while (current != nullptr){
        current->draw(canvas);
        current = current->getprevTriangle();
    }
}

bool samePointP(Point a, Point b){
    return a.getx() == b.getx() &&
           a.gety() == b.gety();
}

bool sameLineP(Line a, Line b){
    return (samePointP(a.getp1(), b.getp1()) &&
            samePointP(a.getp2(), b.getp2())) ||
           (samePointP(a.getp1(), b.getp2()) &&
            samePointP(a.getp2(), b.getp1()));
}

bool hasLineP(Triangle* t, Line line){
    return sameLineP(t->getl1(), line) ||
           sameLineP(t->getl2(), line) ||
           sameLineP(t->getl3(), line);
}

bool sameTriangleP(Triangle* a, const Triangle& b){
    return hasLineP(a, b.getl1()) &&
           hasLineP(a, b.getl2()) &&
           hasLineP(a, b.getl3());
}


Hexagon* Pentagon :: operator+(const Triangle& other) const{
    Triangle* third = prevTriangle;
    if (third == nullptr){
        cout << "Invalid Pentagon" << endl;
        return nullptr;
    }
    Triangle* second = third->getprevTriangle();
    if (second == nullptr){
        cout << "Invalid Pentagon" << endl;
        return nullptr;
    }
    Triangle* first = second->getprevTriangle();
    if (first == nullptr || first->getprevTriangle() != nullptr){
        cout << "Invalid Pentagon" << endl;
        return nullptr;
    }
    Line a = other.getl1();
    Line b = other.getl2();
    Line c = other.getl3();
    Line shared = a;
    int sharedCount = 0;
    Line sides[3] = {a, b, c};
    for (int i = 0; i < 3; i++){
        int count = 0;
        if (hasLineP(first, sides[i])){
            count++;
        }

        if (hasLineP(second, sides[i])){
            count++;
        }

        if (hasLineP(third, sides[i])){
            count++;
        }

        if (count == 1){
            shared = sides[i];
            sharedCount++;
        }
        else if (count > 1){
            cout << "Cannot attach to an internal edge" << endl;
            return nullptr;
        }
    }
    if (sharedCount != 1){
        cout << "Triangle must share one outer edge" << endl;
        return nullptr;
    }
    Triangle* attached = first;
    if (hasLineP(second, shared)){
        attached = second;
    }

    if (hasLineP(third, shared)){
        attached = third;
    }

    Point p = shared.getp1();
    Point q = shared.getp2();

    Line line = other.getl1();
    Point r = line.getp1();

    if (samePointP(r, p) || samePointP(r, q)){
        r = line.getp2();
    }

    if (samePointP(r, p) || samePointP(r, q)){
        line = other.getl2();
        r = line.getp1();
    }
    if (samePointP(r, p) || samePointP(r, q)){
        r = line.getp2();
    }
    line = attached->getl1();
    Point s = line.getp1();
    if (samePointP(s, p) || samePointP(s, q)){
        s = line.getp2();
    }
    if (samePointP(s, p) || samePointP(s, q)){
        line = attached->getl2();
        s = line.getp1();
    }
    if (samePointP(s, p) || samePointP(s, q)){
        s = line.getp2();
    }
    int dx = q.getx() - p.getx();
    int dy = q.gety() - p.gety();

    int cross1 = dx * (r.gety() - p.gety()) -
                 dy * (r.getx() - p.getx());

    int cross2 = dx * (s.gety() - p.gety()) -
                 dy * (s.getx() - p.getx());

    if (cross1 == 0 || cross2 == 0 ||
        (cross1 > 0 && cross2 > 0) ||
        (cross1 < 0 && cross2 < 0)){
        cout << "Triangle must be outside the Pentagon" << endl;
        return nullptr;
    }
    Triangle t1(0, first->getl1(), first->getl2(), first->getl3());
    Triangle t2(0, second->getl1(), second->getl2(), second->getl3());
    Triangle t3(0, third->getl1(), third->getl2(), third->getl3());
    Triangle t4(0, other.getl1(), other.getl2(), other.getl3());

    Hexagon* result = new Hexagon(0, t1, t2, t3, t4);

    return result;
}

Rectangle* Pentagon :: operator-(const Triangle& other) const{
    Triangle* third = prevTriangle;
    if (third == nullptr){
        cout << "Invalid Pentagon" << endl;
        return nullptr;
    }
    Triangle* second = third->getprevTriangle();
    if (second == nullptr){
        cout << "Invalid Pentagon" << endl;
        return nullptr;
    }
    Triangle* first = second->getprevTriangle();
    if (first == nullptr || first->getprevTriangle() != nullptr){
        cout << "Invalid Pentagon" << endl;
        return nullptr;
    }

    Triangle* remaining1 = nullptr;
    Triangle* remaining2 = nullptr;

    if (sameTriangleP(first, other)){
        remaining1 = second;
        remaining2 = third;
    }
    else if (sameTriangleP(second, other)){
        remaining1 = first;
        remaining2 = third;
    }
    else if (sameTriangleP(third, other)){
        remaining1 = first;
        remaining2 = second;
    }
    else{
        cout << "Triangle not found in Pentagon" << endl;
        return nullptr;
    }

    Triangle t1(0, remaining1->getl1(),
                  remaining1->getl2(),
                  remaining1->getl3());
    Triangle t2(0, remaining2->getl1(),
                  remaining2->getl2(),
                  remaining2->getl3());

    Rectangle* result = t1 + t2;
    if (result == nullptr){
        cout << "Remaining Triangles do not form a Rectangle" << endl;
        return nullptr;
    }
    return result;
}




