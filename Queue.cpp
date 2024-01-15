#include "Queue.h"

template<typename T>
Queue<T>::Queue() {
    top = bottom = NULL;
    size = 0;
}

template<typename T>
void Queue<T>::enQueue(T data) {
    if (top == NULL) {
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

    if (top == NULL) {
        std::cout << "The Queue is currently empty!" << std::endl;
    }
    else {
        Node* temp = top;
        top = top->next;
        if (top == NULL) {
            bottom = NULL;
        }
        size--;
    }
}

template<typename T>
T Queue<T>::peek() {
    if (top == NULL) {
        std::cout << "The Queue is currently empty!" << std::endl;
    }
    else {
        return top->data;
    }
}

template <>
bool Queue<Base_Node*>::remove(Base_Node* data) {
    Node* tempQueue = NULL;
    bool found = false;

    while (size != 0) {

        Base_Node* current = peek();
        deQueue();
        if (current == data) {
            found = true;
        }
        else {
            if (tempQueue == NULL) {
                tempQueue = new Node(current);
            } else {
                Node* newNode = new Node(current);
                newNode->next = tempQueue;
                tempQueue = newNode;
            }
        }
    }

    while (tempQueue != NULL) {
        enQueue(tempQueue->data);
        Node* temp = tempQueue;
        tempQueue = tempQueue->next;
        delete temp;
    }

    return found;

}

template class Queue<std::string>;
template class Queue<Base_Node*>;
template class Queue<Base_Column*>;
