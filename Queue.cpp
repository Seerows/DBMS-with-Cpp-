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
        delete temp;
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

template <typename T>
bool Queue<T>::remove(T data) {

    Node* current = top;
    Node* prev = NULL;
    while ((current != NULL) && current->data != data) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        return false;
    }

    if (current == top) {
        top = current->next;
    }
    else if (current == bottom) {
        bottom = prev;
    }
    else {
        prev->next = current->next;
    }

    delete current;
    size--;
    return true;

}

template class Queue<std::string>;
template class Queue<Base_Node*>;
