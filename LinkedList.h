#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Table.h"

template <class T>
class LinkedList{

private:

    class LLNode{
    public:
        T data;
        LLNode* next;

        LLNode(T data){
            this->data = data;
            next = 0;
        }
    };

public:
    LLNode* head;
    LinkedList();
    void insertToTail(T data);
    void deleteNode(T data);

};

#endif // LINKEDLIST_H
