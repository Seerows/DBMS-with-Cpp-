#pragma once
#include<iostream>
#include <QDebug>
#include "Base_Node.h"
#include "Base_Column.h"

template<typename T>
class Queue{

public:

    class Node {
    public:
        T data;
        Node* next;

        Node() {
            next = NULL;
        }
        Node(T data) {
            this->data = data;
            next = NULL;
        }
    };

    Node* top;
    Node* bottom;
    int size;

    Queue();
    void enQueue(T data);
    void deQueue();
    bool remove(T data);
    T peek();

};
