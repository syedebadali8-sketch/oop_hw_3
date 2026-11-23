#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "node.hpp"
#include <iostream>
using namespace std;

class LinkedList{
    private:
        Node* head;
        LinkedList(const LinkedList& other);
        LinkedList& operator=(const LinkedList& other);
    public:
        LinkedList();
        ~LinkedList();
        void insertatend(Shape* shape);
        Shape* search(int id);
        bool remove(int id);
        void display();
        void clear();
        void draw(char canvas[][80]);
};

#endif
