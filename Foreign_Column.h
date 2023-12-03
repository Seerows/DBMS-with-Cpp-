#pragma once
#include "Column.h"
#include <QDebug>

template <class T>
class Foreign_Column : public Column<T>{

public:
    Column<T>* reference;

    Foreign_Column(string type, string name, Base_Column* reference);
    bool validate(Base_Node* data);
    bool insertAtTail(Base_Node* data);
    Foreign_Column<T>* getCopy() override;

};

