#ifndef COLUMN_H
#define COLUMN_H

#include <iostream>
#include "Base_Column.h"
#include "Node.h"

using namespace std;

template <class T>
class Column : public Base_Column {

private:
    void quickSort(int start, int end, string order);
    int partition(int start, int end, string order);
    
public:
    Node<T>* head;
    Node<T>* tail;

    Column<T>(string type, string name);
    ~Column<T>();

    Column<T>* getCopy();
    virtual bool insertAtTail(Base_Node* node);
    virtual bool insertAtTail(T data);
    void deleteAtTail();
    void deleteRow(Base_Node* node);
    void deleteColumn();
    void sort(string order);

    Node<T>* getHead();
    Node<T>* getTail();

    Node<T>& operator[](int index);
    void display();

};

#endif // COLUMN_H
