#include "rectangle.hpp"
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

Rectangle :: ~Rectangle(){
    delete prevTriangle;
    prevTriangle = nullptr;
}
