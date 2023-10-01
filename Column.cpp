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
        current = current->next;
    }

}

template <class T>
void Column<T>::insertAtTail(T data) {

    if (head == NULL) {
        head = new Node<T>(data);
    }
    else {
        Node<T>* current = head;

        while (current->next != NULL) {
            current = current->next;
        }

        current->next = new Node<T>(data);
    }

}

template class Column<int>;
template class Column<char>;
template class Column<string>;
template class Column<bool>;
template class Column<float>;
