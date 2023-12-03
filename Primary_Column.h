#pragma once
#include "Column.h"

template <class T>
class Primary_Column : public Column<T>{

public:
    Primary_Column(string type, string name);
    bool insertAtTail(Base_Node* data);
    bool validate(Base_Node* data);
    Primary_Column<T>* getCopy();

};
