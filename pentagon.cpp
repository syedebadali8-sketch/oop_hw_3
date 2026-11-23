#include "pentagon.hpp"
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


