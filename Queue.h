#ifndef QUEUE_H
#define QUEUE_H


#pragma once
#include<iostream>
//#include "Base_Node.h"

template<typename T>
class Queue {

public:

    class Node {
    public:
        T data;
        Node* next;

        Node() {
            next = nullptr;
        }
        Node(T data) {
            this->data = data;
            next = nullptr;
        }
    };

    Node* top;
    Node* bottom;
    int size;

    Queue();
    void enQueue(T data);

    void deQueue();

    T peek();

};
#endif // QUEUE_H
