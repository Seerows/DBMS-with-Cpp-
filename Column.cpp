#include "Column.h"

template <class T>
Column<T>::Column(string name) {
    label = name;
    head = NULL;
}

template <class T>
void Column<T>::display() {

    Node<T>* current = head;

    while (current != NULL) {
        cout << current->data << "\t";
        current = current->down;
    }

}

template <class T>
void Column<T>::insertAtTail(T data) {

    if (head == NULL) {
        head = new Node<T>(data);
    }
    else {
        Node<T>* current = head;

        while (current->down != NULL) {
            current = current->down;
        }

        current->down = new Node<T>(data);
    }

}

template <class T>
Node<T>* getHead() {
    return head;
}

template class Column<int>;
template class Column<char>;
template class Column<string>;
template class Column<bool>;
template class Column<float>;
