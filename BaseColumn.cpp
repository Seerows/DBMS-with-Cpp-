#include "BaseColumn.h"

BaseColumn::BaseColumn() {
	next_col = NULL;
}

void BaseColumn::display() {}

void BaseColumn::insertAtTail(int) {}

void BaseColumn::insertAtTail(string){}

void BaseColumn::insertAtTail(char){}

void BaseColumn::insertAtTail(bool){}

void BaseColumn::insertAtTail(float){}