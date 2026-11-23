#ifndef NODE_HPP
#define NODE_HPP

#include "shape.hpp"
using namespace std;

class Node{
    private:
        Shape* data;
        Node* next;
    public:
        Node(Shape* value);
        Shape* getdata() const;
        Node* getnext() const;
        void setnext(Node* n);
        ~Node();
};

#endif
