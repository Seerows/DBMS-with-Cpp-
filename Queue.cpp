#include "Queue.h"

template<typename T>
Queue<T>::Queue() {
    top = bottom = nullptr;
    size = 0;
}

template<typename T>
void Queue<T>::enQueue(T data) {
    if (top == nullptr) {
        top = bottom = new Node(data);
    }
    else {
        bottom->next = new Node(data);
        bottom = bottom->next;

    }
    size++;
}

template<typename T>
void Queue<T>::deQueue() {
    if (top == nullptr) {
        std::cout << "The Queue is currently empty!" << std::endl;
    }
    else {
        Node* temp = top;
        top = top->next;
        if (top == nullptr) {
            bottom = nullptr;
        }
        delete temp;
        size--;
    }
}

template<typename T>
T Queue<T>::peek() {
    if (top == nullptr) {
        std::cout << "The Queue is currently empty!" << std::endl;
    }
    else {
        return top->data;
    }
}

template class Queue<std::string>;
//template class Queue<Base_Node*>;
