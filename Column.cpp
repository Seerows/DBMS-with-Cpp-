#include "Column.h"

template <class T>
Column<T>::Column(string name) {
    label = name;
    head = tail = NULL;
}

template <class T>
void Column<T>::display() {

    //Base_Node* current = head;


    Node<T>* current = head;

    while (current != NULL) {
        cout << current->data << "\t";
        current = current->down;
    }

    cout << endl;

}

template <class T>
void Column<T>::insertAtTail(T data) {

    if (head == NULL) {
        head = tail = new Node<T>(data);
    }
    else {
        Node<T>* current = head;

        while (current->down != NULL) {
            current = current->down;
        }

        current->down = tail = new Node<T>(data);
    }

}

template <class T>
Node<T>* Column<T>::getHead() {
    return head;
}

template <class T>
Node<T>* Column<T>::getTail() {
    return tail;
}


template <class T>
Base_Node& Column<T>::operator[](int index) {

    int count = 0;
    Node<T>* current = head;
        
    while (count++ < index && current->down != NULL) {
        current = current->down;
    }
    
    return *(current);
}

template class Column<int>;
template class Column<char>;
template class Column<string>;
template class Column<bool>;
template class Column<float>;
