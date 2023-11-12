#include "LinkedList.h"

template <class T>
LinkedList<T>::LinkedList(){
    head = 0;
}

template <class T>
void LinkedList<T>::insertToTail(T data){
    if(head == 0){
        head = new LLNode(data);
    }
    else{
        LLNode* current = head;
        while(current->next != 0){
            current = current->next;
        }
        current->next = new LLNode(data);
    }
}

template class LinkedList<Table*>;
