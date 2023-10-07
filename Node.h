#pragma once
#include <iostream>
#include <string>
#include <Base_Node.h>

using namespace std;

template <class T>
class Node : public Base_Node {

public:
    T data;
    Node<T>* down;

    Node(T data);

    Node<T>* getDown();

    string getValue();

    void setValue(T val);
    /*void setValue(int val);
    void setValue(float val);
    void setValue(char val);
    void setValue(string val);
    void setValue(bool val);*/

};

