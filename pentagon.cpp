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