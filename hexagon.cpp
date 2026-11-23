#include "hexagon.hpp"
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

