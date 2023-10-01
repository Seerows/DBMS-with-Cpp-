#include "Node.h"

template <class T>
Node<T>::Node(T data) {
    this->data = data;
    next = NULL;
}

template class Node<int>;
template class Node<string>;
template class Node<char>;
template class Node<float>;
template class Node<bool>;