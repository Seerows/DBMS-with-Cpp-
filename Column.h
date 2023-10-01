#pragma once
#include <iostream>
#include <BaseColumn.h>
#include <Node.h>

using namespace std;

template <class T>
class Column : public BaseColumn {

public:
    Node<T>* head;

    Column<T>(string name);
    void insertAtTail(T data);

    void display();


};

