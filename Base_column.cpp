#include "Base_Column.h"

Base_Column::Base_Column() {
    next_col = prev_col = NULL;
    num_of_rows = 0;
}

void Base_Column::display() {}
void Base_Column::insertAtTail(int) {}
void Base_Column::insertAtTail(string) {}
void Base_Column::insertAtTail(char) {}
void Base_Column::insertAtTail(bool) {}
void Base_Column::insertAtTail(float) {}
