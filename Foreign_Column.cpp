#include "Foreign_Column.h"

template <class T>
Foreign_Column<T>::Foreign_Column(string type, string name, Column<T>* reference) : Column<T>(type, name), reference(reference) {}

template <class T>
bool Foreign_Column<T>::insertAtTail(Base_Node* data) {

	Node<T>* current = reference->head;
	while (current != NULL) {
		if (*current == *data) {
			return Column<T>::insertAtTail(data);
		}

		current = current->down;
	}

	cout << "Value does not exist in column referenced by foreign key." << endl;
	return false;

}


template class Foreign_Column<int>;
template class Foreign_Column<char>;
template class Foreign_Column<string>;
template class Foreign_Column<bool>;
template class Foreign_Column<float>;