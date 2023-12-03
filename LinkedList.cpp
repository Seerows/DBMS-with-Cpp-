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

template <class T>
void LinkedList<T>::deleteNode(T data) {

    LLNode* current = head, *prev = head;
    while (current != NULL) {
        if (current->data == data) {
            if (current == head) {
                head = head->next;
            }
            prev->next = current->next;
            delete current;
            return;
        }

        prev = current;
        current = current->next;
    }

    cout << "Table to be deleted was not found in the LinkedList." << endl;

}

template class LinkedList<Table*>;
