#ifndef BASE_COLUMN_H
#define BASE_COLUMN_H

#include <iostream>
#include "Node.h"

using namespace std;

class Base_Column {

public:
    Base_Column* next_col;
    Base_Column* prev_col;

    string label;
    string type;
    int num_of_rows;

    Base_Column();
    virtual void display() = 0;

    virtual Base_Node& operator[](int index) = 0;

    virtual Base_Node* getHead() = 0;
    virtual Base_Node* getTail() = 0;
    virtual Base_Column* getCopy() = 0;

    virtual void insertAtTail(int);
    virtual void insertAtTail(string);
    virtual void insertAtTail(char);
    virtual void insertAtTail(float);
    virtual void insertAtTail(bool);

    virtual void insertAtTail(Base_Node*) = 0;
    virtual void deleteAtTail() = 0;

};

#endif // BASE_COLUMN_H
