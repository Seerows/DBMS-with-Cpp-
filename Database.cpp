#include "Database.h"

//ignore this method. It is only used to intialize the t1 and t2 pointers.
Database::Database(Table& table1, Table& table2){

    table_list.insertToTail(&table1);
    table_list.insertToTail(&table2);

}


Database::Database(string name){

    this->name = name;
    num_of_tables = 0;

    //Database::pull() should be used after this to pull contents from file :)
}

void Database::addTable(Table* table) {

    table_list.insertToTail(table);

}

bool Database::processQuery(vector<string> words){

    validateQuery vq;
    bool validate = vq.validate(words);

    if (!validate) {
        return false;
    }

    if (vq.createCheck) {
        handleCreateQuery(vq.query, vq.keys, vq.pkeyCheck, vq.fkeyCheck);
    }
    
    if (vq.insertCheck) {
        handleInsertQuery(vq.InsertQuery);
    }
    
    if (vq.selectCheck) {
        handleSelectQuery(vq.selectQuery, vq.whereSelect, vq.whereCheck, vq.orderSelect, vq.orderCheck, vq.joinSelect, vq.joinCheck);
    }
    
    if (vq.updateCheck) {
        handleUpdateQuery(vq.updateQuery, vq.whereSelect, vq.whereCheck);
    }

    if (vq.alterCheck) {
        handleAlterQuery(vq.alterQuery);
    }

    if (vq.deleteCheck) {
        handleDeleteQuery(vq.deleteQuery, vq.whereSelect, vq.whereCheck);
    }

    if (vq.dropTableCheck) {
        handleDropQuery(vq.dropTableQuery);
    }

    return true;

}

bool Database::handleCreateQuery(pair<string, vector< pair<string, string>>> createQuery, map<string, string> keys, bool primaryKeyCheck, bool foreignKeyCheck) {

    auto current = table_list.head;
    while (current != NULL) {
        if (compareStrings(current->data->label, createQuery.first)) {
            cout << createQuery.first << " table already exists." << endl;
            return false;
        }

        current = current->next;
    }

    for (const auto& entry : keys) {
        std::cout << "Key: " << entry.first << ", Value: " << entry.second << "\n";
    }

    Table* table = new Table(createQuery, keys);

    /*for (int i = 0; i < createQuery.second.size(); i++) {
        cout << createQuery.second.at(i).first << "--" << createQuery.second.at(i).second << endl;
    }*/

    table_list.insertToTail(table);
    return true;

}

bool Database::handleInsertQuery(pair<string, vector<vector<pair<string, string>>>> insertQuery) {

    auto table = getTable(insertQuery.first);

    if (table == NULL) {
        cout << "Invalid Insertion Input." << endl;
        return false;
    }

    for (int i = 0; i < insertQuery.second.size(); i++) {
        Queue<Base_Node*> inputs;
        for (int j = 0; j < insertQuery.second.at(i).size(); j++) {
            //cout << insertQuery.second.at(i).at(j).first << ", " << insertQuery.second.at(i).at(j).second << endl;
            inputs.enQueue(convert(insertQuery.second.at(i).at(j).first, insertQuery.second.at(i).at(j).second));
        }
        table->addRow(inputs, table->col_head);
    }

    return true;
}

bool Database::handleSelectQuery(pair<string, vector<string>> selectQuery, vector<tuple<string, string, string>> whereQuery, bool whereCheck, pair<string, string> orderQuery, bool orderCheck, pair<pair<string, string>, pair<string, string>> joinSelect, bool joinCheck){

    /*cout << joinSelect.first.first << "--" << joinSelect.first.second << endl;
    cout << joinSelect.second.first << "--" << joinSelect.second.second << endl;*/

    auto table = getTable(selectQuery.first);

    if (table == NULL) {
        cout << "Invalid Selection Input." << endl;
        return false;
    }

    Table* select = new Table(table->label);
    for (int i = 0; i < selectQuery.second.size(); i++) {
        Base_Column* curr_col = table->col_head;
        
        if (selectQuery.second.at(i) == "*") {
            delete select;
            select = new Table(*table);
            continue;
        }

        while (curr_col != NULL) {
            if (compareStrings(curr_col->label, selectQuery.second.at(i))) {
                select->addColumn(curr_col);
                break;
            }

            curr_col = curr_col->next_col;
        }
        
    }

    //whereQuery work
    //add the inverse on the AND & OR operator later.

    if (whereCheck) {
        vector<tuple<string, string, string>> inverse = whereQuery;
        for (int i = 0; i < inverse.size(); i++) {
            if (get<1>(inverse.at(i)) == "=") {
                get<1>(inverse.at(i)) = "!=";
            }
            else if (get<1>(inverse.at(i)) == "!=") {
                get<1>(inverse.at(i)) = "=";
            }
            else if (get<1>(inverse.at(i)) == ">") {
                get<1>(inverse.at(i)) = "<=";
            }
            else if (get<1>(inverse.at(i)) == "<") {
                get<1>(inverse.at(i)) = ">=";
            }
            else if (get<1>(inverse.at(i)) == ">=") {
                get<1>(inverse.at(i)) = "<";
            }
            else if (get<1>(inverse.at(i)) == "<=") {
                get<1>(inverse.at(i)) = ">";
            }
        }

        whereDeleteUtil(select, inverse);
    }
    

    //orderQuery work

    if (orderCheck) {
        Base_Column* curr_col = select->getColumn(orderQuery.first);

        if (curr_col == NULL) {
            cout << "Invalid Order Query." << endl;
            return false;
        }


        if (compareStrings(orderQuery.second, "asc")) {
            curr_col->sort("asc");
        }
        else if (compareStrings(orderQuery.second, "desc")) {
            curr_col->sort("desc");
        }
    }
    

    select->display();

    if (select != table) {
        delete select;
    }

    return true;
}

bool Database::handleUpdateQuery(pair<string, vector<pair<string, string>>> updateQuery, vector<tuple<string, string, string>> whereQuery, bool whereCheck) {

    /*
    UPDATE your_table_name
    SET your_column = your_value
    WHERE your_condition;
    */

    /*for (int i = 0; i < whereQuery.size(); i++) {
        cout << get<0>(whereQuery.at(i)) << "--" << get<1>(whereQuery.at(i)) << "--" << get<2>(whereQuery.at(i)) << endl;
    }*/

    auto table = getTable(updateQuery.first);
    if (table == NULL) {
        cout << "Invalid Updation Input." << endl;
        return false;
    }


    //if there is no WHERE statement
    if (!whereCheck) {
        for (int i = 0; i < updateQuery.second.size(); i++) {
            Base_Column* affected = table->getColumn(updateQuery.second.at(i).first);
            if (affected == NULL) {
                cout << "Invalid Updation Input." << endl;
                return false;
            }

            Base_Node* affected_head = affected->getHead();

            Base_Node* replace = convert(affected->getHead()->getType(), updateQuery.second.at(i).second);

            while (affected_head != NULL) {
                if (!(affected->validate(replace))) {
                    return false;
                }
                affected_head->setValue(replace);

                affected_head = affected_head->getDown();
            }

        }
        return true;
    }


    //if there is a WHERE statement
    for (int i = 0; i < updateQuery.second.size(); i++) {
        
        for (int j = 0; j < whereQuery.size(); j++) {
            
            Base_Column* col = table->getColumn(std::get<0>(whereQuery.at(j)));
            Base_Column* affected = table->getColumn(updateQuery.second.at(i).first);

            if (col == NULL || affected == NULL) {
                cout << "Invalid Updation Input." << endl;
                return false;
            }

            Base_Node* affected_head = affected->getHead();
            Base_Node* head = col->getHead();

            Base_Node* target = convert(col->getHead()->getType(), std::get<2>(whereQuery.at(j)));
            Base_Node* replace = convert(affected->getHead()->getType(), updateQuery.second.at(i).second);

            while (head != NULL) {
                if ((std::get<1>(whereQuery.at(j)) == "=") && (*head == *target)) {
                    if (!(affected->validate(replace))) {
                        return false;
                    }
                    affected_head->setValue(replace);
                }
                else if ((std::get<1>(whereQuery.at(j)) == ">") && (*head > *target)) {
                    if (!(affected->validate(replace))) {
                        return false;
                    }
                    affected_head->setValue(replace);
                }
                else if ((std::get<1>(whereQuery.at(j)) == "<") && (*head < *target)) {
                    if (!(affected->validate(replace))) {
                        return false;
                    }
                    affected_head->setValue(replace);
                }
                else if ((std::get<1>(whereQuery.at(j)) == ">=") && (*head >= *target)) {
                    if (!(affected->validate(replace))) {
                        return false;
                    }
                    affected_head->setValue(replace);
                }
                else if ((std::get<1>(whereQuery.at(j)) == "<=") && (*head <= *target)) {
                    if (!(affected->validate(replace))) {
                        return false;
                    }
                    affected_head->setValue(replace);
                }

                affected_head = affected_head->getDown();
                head = head->getDown();
            }

        }
        
    }

    return true;
}

bool Database::handleAlterQuery(pair<string, vector<pair<string, string>>> alterQuery) {

    auto table = getTable(alterQuery.first);

    if (table == NULL) {
        cout << "Invalid Alteration Input." << endl;
        return false;
    }

    cout << alterQuery.first << endl;
    for (int i = 0; i < alterQuery.second.size(); i++) {
        cout << alterQuery.second.at(i).first << " " << alterQuery.second.at(i).second << endl;
    }

    for (int i = 0; i < alterQuery.second.size(); i++) {
        if (alterQuery.second.at(i).first == "drop") {
            table->deleteColumn(alterQuery.second.at(i).second);
        }
        else {
            table->addColumn(pair<string, string>(alterQuery.second.at(i).first, alterQuery.second.at(i).second));
        }
    }

    return true;

}

bool Database::handleDeleteQuery(string deleteQuery, vector<tuple<string, string, string>> whereQuery, bool whereCheck) {

    auto table = getTable(deleteQuery);
    
    if (table == NULL) {
        cout << "Invalid Deletion Input." << endl;
        return false;
    }

    if (!whereCheck) {
        table->deleteAllRows();

        return true;
    }

    whereDeleteUtil(table, whereQuery);
    
    return true;

}

bool Database::handleDropQuery(string dropTableQuery) {

    auto table = getTable(dropTableQuery);

    if (table == NULL) {
        cout << "Invalid Drop Query.\n";
        return false;
    }

    table_list.deleteNode(table);

    return true;

}

bool Database::whereDeleteUtil(Table* table, vector<tuple<string, string, string>> whereQuery) {

    for (int i = 0; i < whereQuery.size(); i++) {
        Base_Column* col = table->getColumn(get<0>(whereQuery.at(i)));
        if (col == NULL) {
            cout << "Invalid Where Query." << endl;
            return false;
        }

        Base_Node* target = convert(col->getHead()->getType(), get<2>(whereQuery.at(i)));

        Base_Node* current = col->getHead();
        while (current != NULL) {
            Base_Node* temp = current->getDown();
            if ((std::get<1>(whereQuery.at(i)) == "=") && (*current == *target)) {
                table->deleteRow(col, current);
            }
            else if ((std::get<1>(whereQuery.at(i)) == "!=") && (*current != *target)) {
                table->deleteRow(col, current);
            }
            else if ((std::get<1>(whereQuery.at(i)) == ">") && (*current > *target)) {
                table->deleteRow(col, current);
            }
            else if ((std::get<1>(whereQuery.at(i)) == "<") && (*current < *target)) {
                table->deleteRow(col, current);
            }
            else if ((std::get<1>(whereQuery.at(i)) == ">=") && (*current >= *target)) {
                table->deleteRow(col, current);
            }
            else if ((std::get<1>(whereQuery.at(i)) == "<=") && (*current <= *target)) {
                table->deleteRow(col, current);
            }

            current = temp;
        }

    }

    return true;
}

void Database::printTables() {
    auto current = table_list.head;
    
    while (current != NULL) {
        current->data->display();
        current = current->next;
    }

    //auto curr_col = current->data->col_head;
    //while (curr_col != NULL) {
    //    curr_col->display();

    //    curr_col = curr_col->next_col;
    //}
}


//int temp_rows;
//
//void Database::pull(){
//
//    QString db_name = QString::fromStdString(name);
//    db_name += ".dat";
//    QFile file(db_name);
//
//    if (file.open(QIODevice::ReadOnly)) {
//        QDataStream in(&file);
//
//        in >> username;
//        in >> password;
//
//        while(!in.atEnd()){
//
//            pair<string, vector<pair<string, string>>> query1;
//
//            in >> query1.first;
//
//            int num_of_cols, num_of_rows;
//            in >> num_of_cols;
//            in >> num_of_rows;
//
//            query1.second.resize(num_of_cols);
//            in >> query1.second;
//
//            Table* t1 = new Table(query1);
//            temp_rows = num_of_rows;
//            in >> *t1;
//
//            table_list.insertToTail(t1);
//
//        }
//
//        file.close();
//
//    }
//    else{
//        cout << "Cannot open the file for reading.\n";
//    }
//
//}


void Database::join(){

    //cout << "\nJoining Employees and Departments..." << endl;
    //temp = t1->join(&(*t1)["Dept_ID"], &(*t2)["ID"]);
    //temp->display();

}

//void Database::commit(){
//
//    QString db_name = QString::fromStdString(name);
//    db_name += ".dat";
//    QFile file(db_name);
//
//    if (file.open(QIODevice::WriteOnly)) {
//        QDataStream out(&file);
//
//        out << username;
//        out << password;
//
//        auto current = table_list.head;
//
//        while(current != 0){
//            out << *(current->data);
//            current = current->next;
//        }
//
//        file.close();
//    } else {
//        cout << "Cannot open the file for writing." << endl;
//    }
//
//
//}

Table* Database::getTable(string label) {

    auto current = table_list.head;
    while (current != NULL) {
        if (compareStrings(current->data->label, label)) {
            return current->data;
        }

        current = current->next;
    }

    return NULL;
}

//put into Dependencies later.
bool Database::compareStrings(string str1, string str2) {

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

Base_Node* Database::convert(string type, string value) {

    if (type == "float") {
        float data = stof(value);
        return (new Node<float>(data));
    }
    else if (type == "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >") {
        return (new Node<string>(value));
    }
    else if (type == "char") {
        char data = value.at(0);
        return (new Node<char>(data));
    }
    else if (type == "bool") {
        bool data;
        if (value == "true") {
            data = true;
        }
        else {
            data = false;
        }
        return (new Node<bool>(data));
    }
    else {
        int data = stoi(value);
        return (new Node<int>(data));
    }
}
