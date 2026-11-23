#include "rectangle.hpp"
#include <iostream>
using namespace std;

Rectangle :: Rectangle(int id, Triangle first, Triangle second) : Shape(id){
    Triangle* firstCopy = new Triangle(first);
    Triangle* secondCopy = new Triangle(second);
    secondCopy->setprevTriangle(firstCopy);
    prevTriangle = secondCopy;
}
