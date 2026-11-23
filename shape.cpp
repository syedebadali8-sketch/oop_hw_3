#include "shape.hpp"
#include <iostream>
using namespace std;

Shape :: Shape(int id){
    ID = id;
    prevTriangle = nullptr;
}

Shape :: ~Shape(){

}

int Shape :: getID() const{
    return ID;
}

void Shape :: setID(int id){
    ID = id;
}
