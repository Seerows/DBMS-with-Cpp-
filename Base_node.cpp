#include "Base_Node.h"

Base_Node::Base_Node() {
    right = left = NULL;
}

void Base_Node::setValue(int val) {}
void Base_Node::setValue(float val) {}
void Base_Node::setValue(char val) {}
void Base_Node::setValue(string val) {}
void Base_Node::setValue(bool val) {}

Base_Node::~Base_Node(){}
