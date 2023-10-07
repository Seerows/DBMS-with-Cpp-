#pragma once
#include <iostream>
#include <variant>
using namespace std;

class Base_Node{

public:

    Base_Node* right;
    Base_Node* left;
    virtual Base_Node* getDown() = 0;       //unneccessary?

    virtual string getValue() = 0;
    virtual void setValue(int val);
    virtual void setValue(float val);
    virtual void setValue(char val);
    virtual void setValue(string val);
    virtual void setValue(bool val);
    Base_Node();

};

