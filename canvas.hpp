#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "linkedlist.hpp"
using namespace std;

class Canvas{
    private:
        char board[40][80];
        LinkedList shapes;
        int nextID;
    public:
        Canvas();
        void clear();
        void draw();
        void display();
        void addShape(Shape* shape);
        void removeShape(int id);
        Shape* findShape(int id);
        void history();
};

#endif
