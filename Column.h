#pragma once
#include <iostream>
#include <Base_Column.h>
#include <Node.h>

using namespace std;

template <class T>
class Column : public Base_Column {

public:
    Node<T>* head;
    Node<T>* tail;

    Column<T>(string type, string name);

    Column<T>* getCopy(); 
    void insertAtTail(Base_Node* node);
    void insertAtTail(T data);
    void deleteAtTail();

    Node<T>* getHead();
    Node<T>* getTail();

    Node<T>& operator[](int index);
    void display();

};

