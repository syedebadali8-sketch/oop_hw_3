#include "rectangle.hpp"
#include "pentagon.hpp"
#include <iostream>
using namespace std;

Rectangle :: Rectangle(int id, Triangle first, Triangle second) : Shape(id){
    Triangle* firstCopy = new Triangle(first);
    Triangle* secondCopy = new Triangle(second);
    secondCopy->setprevTriangle(firstCopy);
    prevTriangle = secondCopy;
}

Rectangle :: Rectangle(const Rectangle& other) : Shape(other.ID){
    if (other.prevTriangle == nullptr){
        prevTriangle = nullptr;
    }
    else{ 
        prevTriangle = new Triangle(*other.prevTriangle);
    }
}

Rectangle& Rectangle :: operator=(const Rectangle& other){
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

void Rectangle :: draw(char canvas[][80]){
    Triangle* current = prevTriangle;
    while (current != nullptr){
        current->draw(canvas);
        current = current->getprevTriangle();
    }
}

Rectangle :: ~Rectangle(){
    delete prevTriangle;
    prevTriangle = nullptr;
}

bool samePointR(Point a, Point b){
    return a.getx() == b.getx() && a.gety() == b.gety();
}

bool sameLineR(Line a, Line b){
    return (samePointR(a.getp1(), b.getp1()) &&
            samePointR(a.getp2(), b.getp2())) ||
           (samePointR(a.getp1(), b.getp2()) &&
            samePointR(a.getp2(), b.getp1()));
}

bool hasLineR(Triangle t, Line line){
    return sameLineR(t.getl1(), line) ||
           sameLineR(t.getl2(), line) ||
           sameLineR(t.getl3(), line);
}

Pentagon* Rectangle :: operator+(const Triangle& other) const{
    if (prevTriangle == nullptr ||
        prevTriangle->getprevTriangle() == nullptr){
        cout << "Invalid Rectangle" << endl;
        return nullptr;
    }

    Triangle* second = prevTriangle;
    Triangle* first = second->getprevTriangle();

    Line a = other.getl1();
    Line b = other.getl2();
    Line c = other.getl3();
    Line shared = a;
    bool found = false;
    if (hasLineR(*first, a) != hasLineR(*second, a)){
        shared = a;
        found = true;
    }
    else if (hasLineR(*first, b) != hasLineR(*second, b)){
        shared = b;
        found = true;
    }
    else if (hasLineR(*first, c) != hasLineR(*second, c)){
        shared = c;
        found = true;
    }

    if (found == false){
        cout << "Triangle must share an outer Rectangle edge" << endl;
        return nullptr;
    }

    Point p = shared.getp1();
    Point q = shared.getp2();

    Point r = a.getp1();

    if (samePointR(r, p) || samePointR(r, q)){
        r = a.getp2();
    }

    if (samePointR(r, p) || samePointR(r, q)){
        r = b.getp1();
    }

    if (samePointR(r, p) || samePointR(r, q)){
        r = b.getp2();
    }
    Triangle* attached = first;

    if (hasLineR(*second, shared)){
        attached = second;
    }
    Line insideLine = attached->getl1();
    Point s = insideLine.getp1();

    if (samePointR(s, p) || samePointR(s, q)){
        s = insideLine.getp2();
    }

    if (samePointR(s, p) || samePointR(s, q)){
        insideLine = attached->getl2();
        s = insideLine.getp1();
    }

    if (samePointR(s, p) || samePointR(s, q)){
        s = insideLine.getp2();
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
        cout << "Triangle must be outside the Rectangle" << endl;
        return nullptr;
    }
    Triangle t1(0, first->getl1(), first->getl2(), first->getl3());
    Triangle t2(0, second->getl1(), second->getl2(), second->getl3());
    Triangle t3(0, other.getl1(), other.getl2(), other.getl3());
    Pentagon* result = new Pentagon(0, t1, t2, t3);

    return result;
}
