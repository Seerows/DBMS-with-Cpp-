#pragma once
#include <iostream>
#include <Base_Node.h>

using namespace std;

template <class T>
class Node : public Base_Node {

public:
    T data;
    Node<T>* down;

    Node(T data);

};

