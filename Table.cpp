#include "Table.h"

Table::Table(){
    num_of_cols = num_of_rows = 0;
    col_head = NULL;
}

Table::Table(string label) {
    num_of_cols = num_of_rows = 0;
    this->label = label;

    metadata.first = label;
    col_head = NULL;
}

Table::Table(const Table& table) {

    label = table.label;
    col_head = NULL;

    Base_Column* curr_col = table.col_head;
    while (curr_col != NULL) {
        addColumn(curr_col);

        curr_col = curr_col->next_col;
    }

}

Table::Table(pair<string, vector<pair<string, string>>> query, map<string, string> keys) {
    metadata = query;
    this->keys = keys;
    num_of_cols = num_of_rows = 0;

    label = query.first;

    Base_Column* curr = col_head;

    for (int i = 0; i < query.second.size(); i++) {
        string type = query.second.at(i).first;

        num_of_cols++;

        if (i == 0) {

            if (type == "float") {
                bool check = false;
                for (const auto& key : keys) {
                    if (query.second.at(i).second == key.second) {
                        if (key.first == "pk") {
                            col_head = new Primary_Column<float>(type, query.second.at(i).second);
                        }
                        check = true;
                    }
                }

                if (!check)
                    col_head = new Column<float>(type, query.second.at(i).second);
            }
            else if (type == "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >") {
                bool check = false;
                for (const auto& key : keys) {
                    if (query.second.at(i).second == key.second) {
                        if (key.first == "pk") {
                            col_head = new Primary_Column<string>(type, query.second.at(i).second);
                        }
                        check = true;
                    }
                }

                if (!check)
                    col_head = new Column<string>(type, query.second.at(i).second);
            }
            else if (type == "char") {
                bool check = false;
                for (const auto& key : keys) {
                    if (query.second.at(i).second == key.second) {
                        if (key.first == "pk") {
                            col_head = new Primary_Column<char>(type, query.second.at(i).second);
                        }
                        check = true;
                    }
                }

                if (!check)
                    col_head = new Column<char>(type, query.second.at(i).second);
            }
            else if (type == "bool") {
                bool check = false;
                for (const auto& key : keys) {
                    if (query.second.at(i).second == key.second) {
                        if (key.first == "pk") {
                            col_head = new Primary_Column<bool>(type, query.second.at(i).second);
                        }
                        check = true;
                    }
                }

                if (!check)
                    col_head = new Column<bool>(type, query.second.at(i).second);
            }
            else {			//for int case. Removing this gives an error.
                bool check = false;
                for (const auto& key : keys) {
                    if (query.second.at(i).second == key.second) {
                        if (key.first == "pk") {
                            col_head = new Primary_Column<int>(type, query.second.at(i).second);
                        }
                        check = true;
                    }
                }

                if (!check)
                    col_head = new Column<int>(type, query.second.at(i).second);
            }

        }
        else {

            if (i == 1) {
                curr = col_head;
            }
            else if (i > 1) {
                curr = curr->next_col;
            }

            if (type == "float") {
                bool check = false;
                for (const auto& key : keys) {
                    if (query.second.at(i).second == key.second) {
                        if (key.first == "pk") {
                            curr->next_col = new Primary_Column<float>(type, query.second.at(i).second);
                        }
                        check = true;
                    }
                }

                if (!check)
                    curr->next_col = new Column<float>(type, query.second.at(i).second);
            }
            else if (type == "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >") {
                bool check = false;
                for (const auto& key : keys) {
                    if (query.second.at(i).second == key.second) {
                        if (key.first == "pk") {
                            curr->next_col = new Primary_Column<string>(type, query.second.at(i).second);
                        }
                        check = true;
                    }
                }

                if (!check)
                    curr->next_col = new Column<string>(type, query.second.at(i).second);
            }
            else if (type == "char") {
                bool check = false;
                for (const auto& key : keys) {
                    if (query.second.at(i).second == key.second) {
                        if (key.first == "pk") {
                            curr->next_col = new Primary_Column<char>(type, query.second.at(i).second);
                        }
                        check = true;
                    }
                }

                if (!check)
                    curr->next_col = new Column<char>(type, query.second.at(i).second);
            }
            else if (type == "bool") {
                bool check = false;
                for (const auto& key : keys) {
                    if (query.second.at(i).second == key.second) {
                        if (key.first == "pk") {
                            curr->next_col = new Primary_Column<bool>(type, query.second.at(i).second);
                        }
                        check = true;
                    }
                }

                if (!check)
                    curr->next_col = new Column<bool>(type, query.second.at(i).second);
            }
            else {			//for int case. Removing this gives an error.
                bool check = false;
                for (const auto& key : keys) {
                    if (query.second.at(i).second == key.second) {
                        if (key.first == "pk") {
                            curr->next_col = new Primary_Column<int>(type, query.second.at(i).second);
                        }
                        check = true;
                    }
                }

                if(!check)
                    curr->next_col = new Column<int>(type, query.second.at(i).second);
            }

            curr->next_col->prev_col = curr;

        }

    }

}


void Table::display() {

    std::cout << "\t\t" << label << ":\n" << endl;

    for (int i = 0; i < num_of_rows; i++) {
        Base_Column* curr_col = col_head;

        while (curr_col != NULL) {
            std::cout << (*curr_col)[i].getValue();
            /*if (Column<int>* col = dynamic_cast<Column<int>*>(curr_col)) {
                cout << (*col)[i].getValue();
            }
            else if (Column<float>* col = dynamic_cast<Column<float>*>(curr_col)) {
                cout << (*col)[i].getValue();
            }
            else if (Column<char>* col = dynamic_cast<Column<char>*>(curr_col)) {
                cout << (*col)[i].getValue();
            }
            else if (Column<string>* col = dynamic_cast<Column<string>*>(curr_col)) {
                cout << (*col)[i].getValue();
            }
            else if (Column<bool>* col = dynamic_cast<Column<bool>*>(curr_col)) {
                cout << (*col)[i].getValue();
            }*/
            cout << "\t";
            curr_col = curr_col->next_col;
        }
        cout << endl;
    }

    cout << endl;
}

void Table::connect() {

    Base_Column* curr_col = col_head;

    while (curr_col->next_col != NULL) {
        Base_Node* node = curr_col->getTail();
        Base_Node* next_node = curr_col->next_col->getTail();

        node->right = next_node;
        next_node->left = node;

        curr_col = curr_col->next_col;
    }

}

void Table::addColumn(pair<string, string> query) {

    if (query.first == "string") {
        query.first = "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >";
    }

    string type = query.first;
    string name = query.second;

    Base_Column* curr = col_head;

    while (curr != NULL && curr->next_col != NULL) {
        curr = curr->next_col;
    }

    if (col_head == NULL) {
        if (type == "float") {
            col_head = new Column<float>(type, name);
        }
        else if (type == "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >" || type == "string") {
            col_head = new Column<string>(type, name);
        }
        else if (type == "char") {
            col_head = new Column<char>(type, name);
        }
        else if (type == "bool") {
            col_head = new Column<bool>(type, name);
        }
        else {			//for int case. Removing this gives an error.
            col_head = new Column<int>(type, name);
        }

    }
    else {

        if (type == "float") {
            curr->next_col = new Column<float>(type, name);

            for (int i = 0; i < num_of_rows; i++) {
                curr->next_col->insertAtTail(0.0f);
            }
        }
        else if (type == "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >" || type == "string") {
            curr->next_col = new Column<string>(type, name);

            for (int i = 0; i < num_of_rows; i++) {
                curr->next_col->insertAtTail(string("NULL"));
            }
        }
        else if (type == "char") {
            curr->next_col = new Column<char>(type, name);

            for (int i = 0; i < num_of_rows; i++) {
                curr->next_col->insertAtTail('?');
            }
        }
        else if (type == "bool") {
            curr->next_col = new Column<bool>(type, name);

            for (int i = 0; i < num_of_rows; i++) {
                curr->next_col->insertAtTail(false);
            }
        }
        else {			//for int case. Removing this gives an error.
            curr->next_col = new Column<int>(type, name);

            for (int i = 0; i < num_of_rows; i++) {
                curr->next_col->insertAtTail(0);
            }
        }

        curr->next_col->prev_col = curr;

        Base_Node* node = curr->getHead();
        Base_Node* next_node = curr->next_col->getHead();

        while (node != NULL && next_node != NULL) {
            node->right = next_node;
            next_node->left = node;

            node = node->getDown();
            next_node = next_node->getDown();
        }
    }

    metadata.second.push_back(query);
    num_of_cols++;

}

void Table::addColumn(Base_Column* col) {

    if (col_head == NULL) {
        col_head = col->getCopy();
    }
    else {
        Base_Column* curr_col = col_head;

        while (curr_col->next_col != NULL) {
            curr_col = curr_col->next_col;
        }

        curr_col->next_col = col->getCopy();

        curr_col->next_col->prev_col = curr_col;

        Base_Node* node = curr_col->getHead();
        Base_Node* next_node = curr_col->next_col->getHead();

        while (node != NULL && next_node != NULL) {
            node->right = next_node;
            next_node->left = node;

            node = node->getDown();
            next_node = next_node->getDown();
        }
    }

    num_of_cols++;
    num_of_rows = col->num_of_rows;		//this line will cause problems if all columns added do not have the same num_of_rows

    metadata.second.push_back(pair<string, string>(col->type, col->label));
}

void Table::deleteRow(Base_Column* col, Base_Node* node) {

    Base_Column* right_col = col->next_col, * left_col = col->prev_col;
    
    Base_Node* current = node->left;
    while (left_col != NULL) {
        Base_Node* temp_node = current->left;
        left_col->deleteRow(current);

        left_col = left_col->prev_col;
        current = temp_node;
    }

    current = node->right;
    while (right_col != NULL) {
        Base_Node* temp_node = current->right;
        right_col->deleteRow(current);
        
        right_col = right_col->next_col;
        current = temp_node;
    }


    col->deleteRow(node);
    num_of_rows--;

}

void Table::deleteAllRows() {

    Base_Node* current = col_head->getHead();
    while (current != NULL) {
        Base_Node* temp = current->getDown();
        deleteRow(col_head, current);

        current = temp;
    }

}

void Table::deleteColumn(string label) {

    Base_Column* col = getColumn(label);

    if (col == NULL) {
        return;
    }

    if (col == col_head) {
        col_head = col_head->next_col;
    }

    Base_Column* left_col = col->prev_col, * right_col = col->next_col;
    if (left_col != NULL) {
        left_col->next_col = right_col;
    }
    
    if (right_col != NULL) {
        right_col->prev_col = left_col;
    }
    
    col->deleteColumn();
    num_of_cols--;
}

Base_Column& Table::operator[](string label) {

    Base_Column* curr_col = col_head;

    while (curr_col != NULL) {

        if (curr_col->label == label) {
            return *curr_col;
            /*if (Column<int>* col = dynamic_cast<Column<int>*>(curr_col)) {
                return (*col);
            }
            else if (Column<float>* col = dynamic_cast<Column<float>*>(curr_col)) {
                return (*col);
            }
            else if (Column<char>* col = dynamic_cast<Column<char>*>(curr_col)) {
                return (*col);
            }
            else if (Column<string>* col = dynamic_cast<Column<string>*>(curr_col)) {
                return (*col);
            }
            else if (Column<bool>* col = dynamic_cast<Column<bool>*>(curr_col)) {
                return (*col);
            }*/
        }

        curr_col = curr_col->next_col;
    }

    cout << "Column not found." << endl;
    return *curr_col;
}

Base_Column& Table::operator[](int pos) {

    int count = 0;
    Base_Column* curr_col = col_head;
    while (count < pos && curr_col != NULL) {
        count++;
        curr_col = curr_col->next_col;
    }

    if (curr_col != NULL) {
        return *curr_col;
    }

}

Table* Table::join(Base_Column* foreign, Base_Column* reference) {

    Table* t1 = new Table(label);
    Base_Column* curr_col = col_head;

    while (curr_col != foreign) {
        t1->addColumn(curr_col);

        curr_col = curr_col->next_col;
    }

    //for all the columns behind the reference column
    curr_col = reference->prev_col;

    while (curr_col != NULL) {
        Base_Column* add;
        Base_Node* foreign_node = foreign->getHead();

        if (Column<float>* col = dynamic_cast<Column<float>*>(curr_col)) {
            add = new Column<float>(curr_col->type, curr_col->label);
        }
        else if (Column<char>* col = dynamic_cast<Column<char>*>(curr_col)) {
            add = new Column<char>(curr_col->type, curr_col->label);
        }
        else if (Column<string>* col = dynamic_cast<Column<string>*>(curr_col)) {
            add = new Column<string>(curr_col->type, curr_col->label);
        }
        else if (Column<bool>* col = dynamic_cast<Column<bool>*>(curr_col)) {
            add = new Column<bool>(curr_col->type, curr_col->label);
        }
        else {			//for int case, removing this gives an error.
            add = new Column<int>(curr_col->type, curr_col->label);
        }

        while (foreign_node != NULL) {
            Base_Node* reference_node = reference->getHead();
            Base_Node* current_node = curr_col->getHead();

            while (reference_node != NULL) {
                if (*reference_node == *foreign_node) {
                    add->insertAtTail(current_node->getCopy());
                    break;
                }

                reference_node = reference_node->getDown();
                current_node = current_node->getDown();
            }


            foreign_node = foreign_node->getDown();
        }

        t1->addColumn(add);
        curr_col = curr_col->prev_col;
    }

    //for all the columns ahead of the reference column
    curr_col = reference->next_col;

    while (curr_col != NULL) {
        Base_Column* add;
        Base_Node* foreign_node = foreign->getHead();

        if (Column<float>* col = dynamic_cast<Column<float>*>(curr_col)) {
            add = new Column<float>(curr_col->type, curr_col->label);
        }
        else if (Column<char>* col = dynamic_cast<Column<char>*>(curr_col)) {
            add = new Column<char>(curr_col->type, curr_col->label);
        }
        else if (Column<string>* col = dynamic_cast<Column<string>*>(curr_col)) {
            add = new Column<string>(curr_col->type, curr_col->label);
        }
        else if (Column<bool>* col = dynamic_cast<Column<bool>*>(curr_col)) {
            add = new Column<bool>(curr_col->type, curr_col->label);
        }
        else {			//for int case, removing this gives an error.
            add = new Column<int>(curr_col->type, curr_col->label);
        }

        while (foreign_node != NULL) {
            Base_Node* reference_node = reference->getHead();
            Base_Node* current_node = curr_col->getHead();

            while (reference_node != NULL) {
                if (*reference_node == *foreign_node) {
                    add->insertAtTail(current_node->getCopy());
                    break;
                }

                reference_node = reference_node->getDown();
                current_node = current_node->getDown();
            }


            foreign_node = foreign_node->getDown();
        }

        t1->addColumn(add);
        curr_col = curr_col->next_col;
    }

    t1->num_of_rows = this->num_of_rows;

    curr_col = foreign->next_col;
    while (curr_col != NULL) {
        t1->addColumn(curr_col);

        curr_col = curr_col->next_col;
    }

    return t1;

}

bool Table::addRow(Queue<Base_Node*> inputs, Base_Column* current, int counter) {
    
    string type = inputs.peek()->getType();

    if (type == "i") {
        type = "int";
    }
    else if (type == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE") {
        type = "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >";
    }
    else if (type == "c") {
        type = "char";
    }
    else if (type == "b") {
        type = "bool";
    }
    else if (type == "f") {
        type = "float";
    }


    if (metadata.second.at(counter).first == type) {
        int size = inputs.size;
        if (size > 1) {
            if (!current->insertAtTail(inputs.peek())) {
                return false;
            }
            inputs.deQueue();

            counter++;
        }

        if (inputs.size == 1 && addRow(inputs.peek(), current->next_col, counter)) {
            return true;
        }
        
        if(inputs.size > 1 && addRow(inputs, current->next_col, counter)){
            return true;
        }

        if (size == inputs.size + 1) {
            counter--;
            current->deleteAtTail();
        }
    }

    //cout << "Row cannot be added." << endl;
    return false;

}

bool Table::addRow(Base_Node* data, Base_Column* current, int counter) {
    
    string type = data->getType();

    if (type == "i") {
        type = "int";
    }
    else if (type == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE") {
        type = "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >";
    }
    else if (type == "c") {
        type = "char";
    }
    else if (type == "b") {
        type = "bool";
    }
    else if (type == "f") {
        type = "float";
    }

    if ((metadata.second.at(counter).first == type) && (counter == num_of_cols - 1) && current->insertAtTail(data)) {
        num_of_rows++;
        connect();
        return true;
    }
    
    cout << "Row cannot be added." << endl;
    return false;

}

Base_Column* Table::getColumn(string label) {

    auto curr_col = col_head;
    while (curr_col != NULL) {
        if (compareStrings(curr_col->label, label)) {
            return curr_col;
        }
        curr_col = curr_col->next_col;
    }

    return NULL;
}

bool Table::compareStrings(string str1, string str2) {

    for (char& c : str1) {
        c = std::toupper(c);
    }
    for (char& c : str2) {
        c = std::toupper(c);
    }

    if (str1 == str2) {
        return true;
    }

    return false;
}

Table::~Table() {
    Base_Column* col = col_head;

    while (col != NULL) {
        Base_Column* next_col = col->next_col;
        delete col;

        col = next_col;
    }

}