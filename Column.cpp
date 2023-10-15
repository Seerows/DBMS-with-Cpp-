#include "Column.h"

template <class T>
Column<T>::Column(string type, string name) {
    label = name;
    this->type = type;
    head = tail = NULL;
}

template <class T>
void Column<T>::display() {

    Node<T>* current = head;

    while (current != NULL) {
        cout << current->data << "\t";
        current = current->down;
    }

    cout << endl;

}

template <class T>
void Column<T>::insertAtTail(Base_Node* node) {

    if (Node<T>* temp = dynamic_cast<Node<T>*>(node)) {
        if (head == NULL) {
            head = tail = temp;
        }
        else {
            tail->down = temp;
            tail = tail->down;
        }
        num_of_rows++;
    }
    else {
        cout << "Cannot insert at Tail in Column<T>" << endl;
    }
    
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

    num_of_rows++;
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
Node<T>& Column<T>::operator[](int index) {

    int count = 0;
    Node<T>* current = head;
        
    while (count++ < index && current->down != NULL) {
        current = current->down;
    }
    
    return *(current);
}

template <class T>
Column<T>* Column<T>::getCopy() {

    Column<T>* copy = new Column<T>(type, label);

    Node<T>* current = head;
    while (current != NULL) {
        copy->insertAtTail(current->getCopy());

        current = current->down;
    }

    return copy;
}

template class Column<int>;
template class Column<char>;
template class Column<string>;
template class Column<bool>;
template class Column<float>;
