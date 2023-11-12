#include "Node.h"

template <class T>
Node<T>::Node(T data) {
    this->data = data;
    down = up = NULL;
    right = left = NULL;
}

template <class T>
Node<T>* Node<T>::getDown() {
    return down;
}

template <class T>
Node<T>* Node<T>::getUp() {
    return up;
}

template <class T>
Node<T>* Node<T>::getCopy() {

    Node<T>* node = new Node<T>(data);
    return node;

}

template <>
string Node<int>::getValue() {
    return to_string(data);
}

template <>
string Node<float>::getValue() {
    return to_string(data);
}

template <>
string Node<char>::getValue() {
    return string(1, data);
}

template <>
string Node<string>::getValue() {
    return data;
}

template <>
string Node<bool>::getValue() {
    if (data == false) {
        return string("false");
    }
    else {
        return string("true");
    }
}


template <class T>
void Node<T>::setValue(T val) {
    data = val;
}


template <class T>
bool Node<T>::operator==(Base_Node& node) {

    if (Node<T>* temp = &dynamic_cast<Node<T>&>(node)) {
        if (temp->data == data) {
            return true;
        }
    }

    return false;
}

template <class T>
string Node<T>::getType() {

    return string(typeid(data).name());

}

template <class T>
Node<T>::~Node(){
    //cout << "Node destroyed\n";
}


template class Node<int>;
template class Node<string>;
template class Node<char>;
template class Node<float>;
template class Node<bool>;
