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
