#pragma once
#include "Column.h"

template <class T>
class Foreign_Column : public Column<T>{

public:
	Column<T>* reference;

	Foreign_Column(string type, string name, Column<T>* reference);
	bool insertAtTail(Base_Node* data);

};

