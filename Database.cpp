#include "Database.h"

//ignore this method. It is only used to intialize the t1 and t2 pointers.
Database::Database(Table& table1, Table& table2){

    table_list.insertToTail(&table1);
    table_list.insertToTail(&table2);

}


Database::Database(string name){

    this->name = name;

    //Database::pull() should be used after this to pull contents from file :)
}

void Database::addTable(Table* table) {

    table_list.insertToTail(table);

}

bool Database::processQuery(vector< string> words){

    validateQuery vq;
    bool validate = vq.validate(words);

    if (!validate) {
        return false;
    }

    if (vq.createCheck) {
        return handleCreateQuery(vq.query);
    }
    else if (vq.insertCheck) {
        return handleInsertQuery(vq.InsertQuery);
    }
    else if (vq.selectCheck) {
        return handleSelectQuery(vq.selectQuery);
    }
    else if (vq.updateCheck) {
        return handleUpdateQuery(vq.updateQuery, vq.whereSelect);
    }

}

bool Database::handleCreateQuery(pair<string, vector< pair<string, string>>> createQuery) {

    Table* table = new Table(createQuery);

    /*for (int i = 0; i < vq.query.second.size(); i++) {
        cout << vq.query.second.at(i).first << "--" << vq.query.second.at(i).second << endl;
    }*/

    table_list.insertToTail(table);
    return true;

}

bool Database::handleInsertQuery(pair<string, vector< vector<pair<string, string>>>> insertQuery) {

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

        cout << endl << endl;
    }

    return true;
}

bool Database::handleSelectQuery(pair<string, vector<string>> selectQuery) {

    auto table = getTable(selectQuery.first);

    if (table == NULL) {
        cout << "Invalid Selection Input." << endl;
        return false;
    }

    for (int i = 0; i < selectQuery.second.size(); i++) {
        Base_Column* curr_col = table->col_head;

        if (selectQuery.second.at(i) == "*") {
            table->display();
        }
        else {
            while (curr_col != NULL) {

                if (compareStrings(curr_col->label, selectQuery.second.at(i))) {
                    curr_col->display();
                    break;
                }

                curr_col = curr_col->next_col;
            }
        }

    }

    return true;
}

//continue here
bool Database::handleUpdateQuery(pair<string, vector< pair<string, string>>> updateQuery, vector<tuple<string, string, string>> whereQuery) {

    /*
    UPDATE your_table_name
    SET your_column = your_value
    WHERE your_condition;
    */

    cout << updateQuery.first << endl << endl;

    for (int i = 0; i < updateQuery.second.size(); i++) {
        cout << updateQuery.second.at(i).first << "--" << updateQuery.second.at(i).second << endl;
    }

    cout << endl;

    for (int i = 0; i < whereQuery.size(); i++) {
        cout << std::get<0>(whereQuery.at(i)) << "--" << std::get<1>(whereQuery.at(i)) << "--" << std::get<2>(whereQuery.at(i)) << endl;
    }
    cout << endl;


    auto table = getTable(updateQuery.first);

    if (table == NULL) {
        cout << "Invalid Updation Input." << endl;
        return false;
    }

    //Base_Column* curr_col = table->getColumn(whereQuery)
    return true;
}

void Database::printTables() {

    auto current = table_list.head;

    while (current != NULL) {
        current->data->display();
        current = current->next;
    }

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
