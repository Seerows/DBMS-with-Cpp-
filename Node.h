#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include "Base_Node.h"

using namespace std;

template <class T>
class Node : public Base_Node {

public:
    T data;
    Node<T>* down;
    Node<T>* up;

    Node(T data);

    Node<T>* getCopy();
    Node<T>* getDown();
    Node<T>* getUp();

    string getValue();

    void setValue(T val);

    bool operator==(Base_Node& node);
};

#endif // NODE_H
