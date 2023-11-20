#include "Primary_Column.h"

template <class T>
Primary_Column<T>::Primary_Column(string type, string name) : Column<T>(type, name) {}

template <class T>
bool Primary_Column<T>::validate(Base_Node* data) {

	Node<T>* current = this->head;
	while (current != NULL) {
		if (*current == *data) {
			cout << "Not a unique value." << endl;
			return false;
		}

		current = current->down;
	}

	return true;

}

template <class T>
bool Primary_Column<T>::insertAtTail(Base_Node* data) {

	if (!validate(data)) {
		return false;
	}

	return Column<T>::insertAtTail(data);
	
}

template class Primary_Column<int>;
template class Primary_Column<char>;
template class Primary_Column<string>;
template class Primary_Column<bool>;
template class Primary_Column<float>;
