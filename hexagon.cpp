#include "hexagon.hpp"
#include "pentagon.hpp"
#include "rectangle.hpp"
#include <iostream>
using namespace std;

Hexagon :: Hexagon(int id, Triangle first, Triangle second, Triangle third, Triangle fourth) : Shape(id){
    Triangle* firstCopy = new Triangle(first);
    Triangle* secondCopy = new Triangle(second);
    Triangle* thirdCopy = new Triangle(third);
    Triangle* fourthCopy = new Triangle(fourth);
    secondCopy->setprevTriangle(firstCopy);
    thirdCopy->setprevTriangle(secondCopy);
    fourthCopy->setprevTriangle(thirdCopy);
    prevTriangle = fourthCopy;
}

Hexagon :: ~Hexagon(){
    delete prevTriangle;
    prevTriangle = nullptr;
}

Hexagon :: Hexagon(const Hexagon& other) : Shape(other.ID){
    if (other.prevTriangle == nullptr){
        prevTriangle = nullptr;
    }
    else{
        prevTriangle = new Triangle(*other.prevTriangle);
    }
}

Hexagon& Hexagon :: operator=(const Hexagon& other){
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

void Hexagon :: draw(char canvas[][80]){
    Triangle* current = prevTriangle;

    while (current != nullptr){
        current->draw(canvas);
        current = current->getprevTriangle();
    }
}

bool samePointH(Point a, Point b){
    return a.getx() == b.getx() &&
           a.gety() == b.gety();
}

bool sameLineH(Line a, Line b){
    return (samePointH(a.getp1(), b.getp1()) && samePointH(a.getp2(), b.getp2())) || (samePointH(a.getp1(), b.getp2()) && samePointH(a.getp2(), b.getp1()));
}

bool hasLineH(const Triangle& t, Line line){
    return sameLineH(t.getl1(), line) || sameLineH(t.getl2(), line) || sameLineH(t.getl3(), line);
}

bool sameTriangleH(const Triangle& a, const Triangle& b){
    return hasLineH(a, b.getl1()) && hasLineH(a, b.getl2()) && hasLineH(a, b.getl3());
}

Pentagon* Hexagon :: operator-(const Triangle& other) const{
    Triangle* fourth = prevTriangle;
    if (fourth == nullptr){
        cout << "Invalid Hexagon" << endl;
        return nullptr;
    }
    Triangle* third = fourth->getprevTriangle();
    if (third == nullptr){
        cout << "Invalid Hexagon" << endl;
        return nullptr;
    }

    Triangle* second = third->getprevTriangle();
    if (second == nullptr){
        cout << "Invalid Hexagon" << endl;
        return nullptr;
    }

    Triangle* first = second->getprevTriangle();
    if (first == nullptr || first->getprevTriangle() != nullptr){
        cout << "Invalid Hexagon" << endl;
        return nullptr;
    }

    Triangle* remaining1 = nullptr;
    Triangle* remaining2 = nullptr;
    Triangle* remaining3 = nullptr;
    if (sameTriangleH(*first, other)){
        remaining1 = second;
        remaining2 = third;
        remaining3 = fourth;
    }
    else if (sameTriangleH(*second, other)){
        remaining1 = first;
        remaining2 = third;
        remaining3 = fourth;
    }
    else if (sameTriangleH(*third, other)){
        remaining1 = first;
        remaining2 = second;
        remaining3 = fourth;
    }
    else if (sameTriangleH(*fourth, other)){
        remaining1 = first;
        remaining2 = second;
        remaining3 = third;
    }
    else{
        cout << "Triangle not found in Hexagon" << endl;
        return nullptr;
    }

    Triangle t1(0, remaining1->getl1(), remaining1->getl2(),remaining1->getl3());
    Triangle t2(0, remaining2->getl1(),remaining2->getl2(), remaining2->getl3());
    Triangle t3(0, remaining3->getl1(), remaining3->getl2(), remaining3->getl3());

    Rectangle* rectangle = t1 + t2;

    Triangle extra = t3;

    if (rectangle == nullptr){
        rectangle = t1 + t3;
        extra = t2;
    }

    if (rectangle == nullptr){
        rectangle = t2 + t3;
        extra = t1;
    }

    if (rectangle == nullptr){
        cout << "Remaining Triangles do not form a Pentagon" << endl;
        return nullptr;
    }

    Pentagon* result = *rectangle + extra;
    delete rectangle;
    if (result == nullptr){
        cout << "Remaining Triangles do not form a Pentagon" << endl;
        return nullptr;
    }

    return result;
}



