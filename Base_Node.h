#pragma once
#include <iostream>
using namespace std;

class Base_Node{

public:

    Base_Node* right;
    Base_Node* left;
    virtual Base_Node* getDown() = 0;       //unneccessary?
    virtual Base_Node* getUp() = 0;         //unneccessary?

    virtual string getValue() = 0;
    virtual Base_Node* getCopy() = 0;

    virtual void setValue(int val);
    virtual void setValue(float val);
    virtual void setValue(char val);
    virtual void setValue(string val);
    virtual void setValue(bool val);
    virtual bool operator==(Base_Node& node) = 0;
    Base_Node();

};

