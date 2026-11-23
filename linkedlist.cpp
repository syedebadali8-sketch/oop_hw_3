#include "linkedlist.hpp"
#include <iostream>
using namespace std;

LinkedList :: LinkedList(){
    head = nullptr;
}

void LinkedList :: insertatend(Shape* shape){
    Node* newnode = new Node(shape);
    if (head == nullptr){
        head = newnode;
        return;
    }
    else{
        Node* current = head;
        while (current->getnext() != nullptr){
            current = current->getnext();
        }
        current->setnext(newnode);
    }
}

Shape* LinkedList :: search(int id){
    Node* current = head;
    while (current != nullptr){
        if (current->getdata()->getID() == id){
            return current->getdata();
        }
        current = current->getnext();
    }
    return nullptr;
}

bool LinkedList :: remove(int id){
    if (head == nullptr){
        return false;
    }
    if (head->getdata()->getID() == id){
        Node* temp = head;
        head = head->getnext();
        delete temp;
        return true;
    }
    Node* prev = head;
    Node* current = head->getnext();
    while (current != nullptr){
        if (current->getdata()->getID() == id){
            prev->setnext(current->getnext());
            delete current;
            return true;
        }
        prev = current;
        current = current->getnext();
    }
    return false;
}


void LinkedList :: display(){
    Node* current = head;
    while (current != nullptr){
        cout << "Shape ID: " << current->getdata()->getID();
        cout << " - ";
        current->getdata()->printType();
        cout << endl;
        current = current->getnext();
    }
}


void LinkedList :: clear(){
    while (head != nullptr){
        Node* temp = head;
        head = head->getnext();
        delete temp;
    }
}

LinkedList :: ~LinkedList(){
    clear();
}

void LinkedList :: draw(char canvas[][80]){
    Node* current = head;
    while (current != nullptr){
        current->getdata()->draw(canvas);
        current = current->getnext();
    }
}



