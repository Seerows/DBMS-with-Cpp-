#include "Foreign_Column.h"

template <class T>
Foreign_Column<T>::Foreign_Column(string type, string name, Base_Column* reference) : Column<T>(type, name) {

    if(Column<T>* col = dynamic_cast<Column<T>*>(reference)){
        this->reference = col;
    }
    else{
        cout << "Failed dynamic cast in Foreign Column." << endl;
    }
}

template <class T>
bool Foreign_Column<T>::validate(Base_Node* data){

    Node<T>* current = reference->head;

    while (current != NULL) {
        if (*current == *data) {
            return true;
        }

        current = current->down;
    }

    cout << "Value does not exist in column referenced by foreign key." << endl;
    return false;
}

template <class T>
bool Foreign_Column<T>::insertAtTail(Base_Node* data) {

    if (!validate(data)) {
        return false;
    }

    return Column<T>::insertAtTail(data);
}

template <class T>
Foreign_Column<T>* Foreign_Column<T>::getCopy(){
    Foreign_Column<T>* copy = new Foreign_Column<T>(Column<T>::type, Column<T>::label, reference);

    Node<T>* current = Column<T>::head;

    while (current != NULL) {
        copy->insertAtTail(current->getCopy());
        current = current->down;
    }

    return copy;

}

template class Foreign_Column<int>;
template class Foreign_Column<char>;
template class Foreign_Column<string>;
template class Foreign_Column<bool>;
template class Foreign_Column<float>;
