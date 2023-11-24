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
        cout << current->getValue() << "\n";
        current = current->down;
    }

    cout << endl;

}

template <class T>
bool Column<T>::insertAtTail(Base_Node* node) {

    if (Node<T>* temp = dynamic_cast<Node<T>*>(node)) {
        if (head == NULL) {
            head = tail = temp;
        }
        else {
            tail->down = temp;
            temp->up = tail;
            tail = tail->down;
        }
        num_of_rows++;

        return true;
    }

    cout << "Cannot insert at Tail in Column<T>" << endl;
    return false;

}

template <class T>
bool Column<T>::insertAtTail(T data) {

    if (head == NULL) {
        head = tail = new Node<T>(data);
    }
    else {
        Node<T>* temp = new Node<T>(data);
        tail->down = temp;
        temp->up = tail;
        tail = tail->down;
    }

    num_of_rows++;
    return true;
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


template <class T>
void Column<T>::deleteRow(Base_Node* node) {

    if (Node<T>* temp = dynamic_cast<Node<T>*>(node)) {

        if (head == temp) {
            head = temp->down;
        }

        if (tail == temp) {
            tail = tail->up;
        }

        node->deleteNodeHorizontal();
        num_of_rows--;
    }

}

template <class T>
void Column<T>::deleteColumn() {

    Node<T>* current = head;
    while (current != NULL) {
        Node<T>* temp = current->down;
        current->deleteNodeVertical();

        current = temp;
    }
    head = NULL;
    delete this;
}

template <class T>
void Column<T>::deleteAtTail() {

    if (head != NULL) {

        Node<T>* del = tail;
        tail = tail->up;

        delete del;

        num_of_rows--;

        if (num_of_rows == 0) {
            head = tail = NULL;
        }

    }
    else {
        cout << "There are no elements in the Column<T> to be deleted." << endl;
    }

}

template <class T>
void Column<T>::sort(string order) {

    quickSort(0, num_of_rows - 1, order);

}

template <class T>
void Column<T>::quickSort(int start, int end, string order) {

    if (start >= end) {
        return;
    }

    int pivot = partition(start, end, order);

    quickSort(start, pivot - 1, order);
    quickSort(pivot + 1, end, order);

}

template <class T>
int Column<T>::partition(int start, int end, string order) {

    Node<T>* pivot = operator[](end).getCopy();

    int i = start - 1;

    for (int j = start; j < end; j++) {

        if ((order == "asc") && (operator[](j) <= *pivot)) {
            i++;

            Base_Node::swap(&operator[](i), &operator[](j));
        }
        else if ((order == "desc") && (operator[](j) > *pivot)) {
            i++;

            Base_Node::swap(&operator[](i), &operator[](j));
        }

    }

    Base_Node::swap(&operator[](i + 1), &operator[](end));

    return i + 1;

}

template <class T>
Column<T>::~Column<T>(){
    Node<T>* node = head;

    while(node != NULL){
        Node<T>* next_node = node->down;
        delete node;

        node = next_node;
    }

}


template class Column<int>;
template class Column<char>;
template class Column<string>;
template class Column<bool>;
template class Column<float>;
