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
    virtual ~Base_Column();
    virtual void display() = 0;

    virtual Base_Node& operator[](int index) = 0;

    virtual Base_Node* getHead() = 0;
    virtual Base_Node* getTail() = 0;
    virtual Base_Column* getCopy() = 0;
    virtual void deleteRow(Base_Node* node) = 0;
    virtual void deleteColumn() = 0;
    virtual void sort(string order) = 0;

    virtual bool insertAtTail(int);
    virtual bool insertAtTail(string);
    virtual bool insertAtTail(char);
    virtual bool insertAtTail(float);
    virtual bool insertAtTail(bool);

    virtual bool insertAtTail(Base_Node*) = 0;
    virtual void deleteAtTail() = 0;
    virtual bool validate(Base_Node*);

};

#endif // BASE_COLUMN_H
