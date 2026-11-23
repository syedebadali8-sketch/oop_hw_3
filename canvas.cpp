#include "canvas.hpp"
#include <iostream>
using namespace std;

Canvas :: Canvas(){
    nextID = 1;
    clear();
}

void Canvas :: clear(){
    for (int i = 0; i < 40; i++){
        for (int j = 0; j < 80; j++){
            board[i][j] = ' ';
        }
    }
}

void Canvas :: display(){
    for (int i = 0; i < 40; i++){
        for (int j = 0; j < 80; j++){
            cout << board[i][j];
        }
        cout << endl;
    }
}


void Canvas :: addShape(Shape* shape){
    if (shape == nullptr){
        return;
    }

    if (shape->getID() < 0){
        cout << "Invalid Shape ID" << endl;
        return;
    }

    if (shape->getID() == 0){
        shape->setID(nextID);
        nextID++;
    }
    else{
        if (shapes.search(shape->getID()) != nullptr){
            cout << "Shape ID already exists" << endl;
            return;
        }
        if (shape->getID() >= nextID){
            nextID = shape->getID() + 1;
        }
    }
    shapes.insertatend(shape);
}

void Canvas :: removeShape(int id){
    if (shapes.remove(id)){
        cout << "Shape removed successfully" << endl;
    }
    else{
        cout << "Shape not found" << endl;
    }
}

Shape* Canvas :: findShape(int id){
    return shapes.search(id);
}

void Canvas :: history(){
    cout << "Shape History:" << endl;
    shapes.display();
}

void Canvas :: draw(){
    clear();
    shapes.draw(board);
}

