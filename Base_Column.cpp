#include "Base_Column.h"

Base_Column::Base_Column() {
    next_col = prev_col = NULL;
    num_of_rows = 0;
}

void Base_Column::display() {}
bool Base_Column::insertAtTail(int) { return false;  }
bool Base_Column::insertAtTail(string) { return false; }
bool Base_Column::insertAtTail(char) { return false; }
bool Base_Column::insertAtTail(bool) { return false; }
bool Base_Column::insertAtTail(float) { return false; }

bool Base_Column::validate(Base_Node*) {  return true; }

Base_Column::~Base_Column(){}
