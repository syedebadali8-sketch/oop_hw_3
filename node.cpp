#include "node.hpp"
#include <iostream>
using namespace std;

Node :: Node(Shape* value){
    data = value;
    next = nullptr;
}

Shape* Node ::getdata() const{
    return data;
}

Node* Node::getnext() const{
    return next;
}

void Node:: setnext(Node* n){
    next = n;
}

Node :: ~Node(){
    delete data;
    data = nullptr;
}

