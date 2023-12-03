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

template <class T>
string Node<T>::getType() {

    return string(typeid(data).name());

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
void Node<T>::setValue(Base_Node* val) {

    if (Node<T>* temp = dynamic_cast<Node<T>*>(val)) {
        data = temp->data;
    }

}

template <class T>
void Node<T>::deleteNodeHorizontal() {

    Node<T>* upper_node = this->up, * lower_node = this->down;

    if (upper_node != NULL) {
        upper_node->down = lower_node;
    }

    if (lower_node != NULL) {
        lower_node->up = upper_node;
    }

    delete this;
}

template <class T>
void Node<T>::deleteNodeVertical() {

    Base_Node* left_node = this->left, * right_node = this->right;

    if (left_node != NULL) {
        left_node->right = right_node;
    }

    if (right_node != NULL) {
        right_node->left = left_node;
    }

    delete this;
}

template <class T>
bool Node<T>::operator==(Base_Node& node) {

    if (Node<T>* temp = &dynamic_cast<Node<T>&>(node)) {
        if (data == temp->data) {
            return true;
        }
    }

    return false;
}

template <class T>
bool Node<T>::operator!=(Base_Node& node) {

    if (Node<T>* temp = &dynamic_cast<Node<T>&>(node)) {
        if (data != temp->data) {
            return true;
        }
    }

    return false;
}

template <class T>
bool Node<T>::operator>(Base_Node& node) {

    if (Node<T>* temp = &dynamic_cast<Node<T>&>(node)) {
        if (data > temp->data) {
            return true;
        }
    }

    return false;

}

template <class T>
bool Node<T>::operator<(Base_Node& node) {

    if (Node<T>* temp = &dynamic_cast<Node<T>&>(node)) {
        if (data < temp->data) {
            return true;
        }
    }

    return false;

}

template <class T>
bool Node<T>::operator>=(Base_Node& node) {

    if (Node<T>* temp = &dynamic_cast<Node<T>&>(node)) {
        if (data >= temp->data) {
            return true;
        }
    }

    return false;

}


template <class T>
bool Node<T>::operator<=(Base_Node& node) {

    if (Node<T>* temp = &dynamic_cast<Node<T>&>(node)) {
        if (data <= temp->data) {
            return true;
        }
    }

    return false;

}

template <class T>
void Node<T>::swapNodes(Base_Node& node) {

    if (Node<T>* convert = &dynamic_cast<Node<T>&>(node)) {
        T temp = convert->data;
        convert->data = data;
        data = temp;
    }

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
