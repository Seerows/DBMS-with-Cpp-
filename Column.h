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

    Column<T>(string name);

    void insertAtTail(T data);

    //stuck here
    Node<T>* getHead();
    Node<T>* getTail();

    Node<T>& operator[](int index);
    void display();

};

