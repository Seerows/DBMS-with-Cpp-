#include "Base_Node.h"

Base_Node::Base_Node() {
    right = left = NULL;
}

void Base_Node::setValue(int val) {}
void Base_Node::setValue(float val) {}
void Base_Node::setValue(char val) {}
void Base_Node::setValue(string val) {}
void Base_Node::setValue(bool val) {}
void Base_Node::setValue(Base_Node* val) {}

void Base_Node::swap(Base_Node* node1, Base_Node* node2, string dir) {

    if (node1 == NULL || node2 == NULL) {
        return;
    }

    node1->swapNodes(*node2);

    if (dir == "LEFT" || dir == "BOTH") {
        swap(node1->left, node2->left, "LEFT");
    }
    
    if(dir == "RIGHT" || dir == "BOTH") {
        swap(node1->right, node2->right, "RIGHT");
    }

}

Base_Node::~Base_Node(){}
