#include "Database.h"

//ignore this method. It is only used to intialize the t1 and t2 pointers.
Database::Database(Table& table1, Table& table2) {

    table_list.insertToTail(&table1);
    table_list.insertToTail(&table2);

    status.resize(11);
}

Database::Database(string name){
    this->name = name;
    num_of_tables = 0;
}

Database::Database(){
    num_of_tables = 0;

    status.resize(11);
}

Database::Database(string name, string username, string password) {

    this->name = name;
    this->username = username;
    this->password = password;
    num_of_tables = 0;

    status.resize(11);

    //Database::pull() should be used after this to pull contents from file :)
}

void Database::addTable(Table* table) {

    table_list.insertToTail(table);

}

bool Database::processQuery(vector<string> words) {
    qDebug() << "\nProcessing...";

    for(int i = 0; i<status.size(); i++){
        status.at(i) = false;
    }

    validateQuery vq;
    bool validate = vq.validate(words);
    qDebug() << "Valid Query.";
    temp_select = NULL;

    if (!validate) {
        status.at(0) = true;
        cout << "Invalid Query." << endl;
        return false;
    }

    if (vq.createCheck) {
        handleCreateQuery(vq.query, vq.keys);
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

    if(vq.commitCheck){
        commit();
    }

    qDebug() << "Processed Successfully!\n";
    return true;
}

bool Database::handleCreateQuery(pair<string, vector< pair<string, string>>> createQuery, map<string, string> keys) {

    auto current = table_list.head;
    while (current != NULL) {
        if (compareStrings(current->data->label, createQuery.first)) {
            status.at(1) = true;
            cout << createQuery.first << " table already exists." << endl;
            return false;
        }

        current = current->next;
    }

    int count = 0;
    Queue<Base_Column*> foreign_keys;
    for (const auto& entry : keys) {
        if(entry.first == "fk" + to_string(count)){
            tuple<string, string, string> parse = parseFk(entry.second);
            string col = get<0>(parse), ref_table = get<1>(parse), ref = get<2>(parse);

            Table* target_table = getTable(ref_table);
            if(target_table == NULL){
                status.at(2) = true;
                cout << "The reference table does not exist." << endl;
                return false;
            }

            Base_Column* target = target_table->getColumn(ref);
            if(target == NULL){
                status.at(3) = true;
                cout << "The reference column does not exist." << endl;
                return false;
            }

            foreign_keys.enQueue(target);
        }
    }


    Table* table;
    if(foreign_keys.size == 0){
        table = new Table(createQuery, keys);
    }
    else{
        table = new Table(createQuery, keys, &foreign_keys);
    }

//    for (int i = 0; i < createQuery.second.size(); i++) {
//        cout << createQuery.second.at(i).first << "--" << createQuery.second.at(i).second << endl;
//    }

    table_list.insertToTail(table);

    return true;

}

bool Database::handleInsertQuery(pair<string, vector<vector<pair<string, string>>>> insertQuery) {

    auto table = getTable(insertQuery.first);

    if (table == NULL) {
        status.at(4) = true;
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

bool Database::handleSelectQuery(pair<string, vector<string>> selectQuery, pair<vector<tuple<string, string, string>>, string> whereQuery, bool whereCheck, pair<string, string> orderQuery, bool orderCheck, pair<pair<string, string>, pair<string, string>> joinQuery, bool joinCheck) {

    auto table = getTable(selectQuery.first);

    if (table == NULL) {
        status.at(5) = true;
        qDebug() << "Invalid Selection Input.";
        return false;
    }

    Table* select = new Table(*table);

    //join work
    if(joinCheck){

        auto join_table1 = select;
        auto join_table2 = getTable(joinQuery.first.second);

        if(join_table1 == NULL || join_table2 == NULL || !compareStrings(joinQuery.first.first, select->label)){
            status.at(5) = true;
            cout << "Invalid Selection Input." << endl;
            return false;
        }

        Base_Column* join_col1 = join_table1->getColumn(joinQuery.second.first);
        Base_Column* join_col2 = join_table2->getColumn(joinQuery.second.second);

        if(join_col1 == NULL || join_col2 == NULL){
            status.at(5) = true;
            cout << "Invalid Selection Input." << endl;
            return false;
        }

        select = select->join(join_col1, join_col2);
    }

    //whereQuery work
    if (whereCheck) {

        qDebug() << "WHERE QUERY";
        qDebug() << get<0>(whereQuery.first.at(0));
        qDebug() << get<1>(whereQuery.first.at(0));
        qDebug() << get<2>(whereQuery.first.at(0));
        qDebug() << whereQuery.second;

        if (whereQuery.second == "or") {
            whereAddUtil(select, whereQuery);
        }
        else if (whereQuery.second == "and" || whereQuery.second == "null" || whereQuery.second == "") {

            pair<vector<tuple<string, string, string>>, string> inverse = whereQuery;
            inverse.second = "or";

            for (int i = 0; i < inverse.first.size(); i++) {
                if (get<1>(inverse.first.at(i)) == "=") {
                    get<1>(inverse.first.at(i)) = "!=";
                }
                else if (get<1>(inverse.first.at(i)) == "!=") {
                    get<1>(inverse.first.at(i)) = "=";
                }
                else if (get<1>(inverse.first.at(i)) == ">") {
                    get<1>(inverse.first.at(i)) = "<=";
                }
                else if (get<1>(inverse.first.at(i)) == "<") {
                    get<1>(inverse.first.at(i)) = ">=";
                }
                else if (get<1>(inverse.first.at(i)) == ">=") {
                    get<1>(inverse.first.at(i)) = "<";
                }
                else if (get<1>(inverse.first.at(i)) == "<=") {
                    get<1>(inverse.first.at(i)) = ">";
                }
            }

            whereDeleteUtil(select, inverse);
        }
    }


    //orderQuery work
    if (orderCheck) {
        Base_Column* curr_col = select->getColumn(orderQuery.first);

        if (curr_col == NULL) {
            status.at(6) = true;
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


    //select Query work
    Table* final_select = new Table(select->label);

    for (int i = 0; i < selectQuery.second.size(); i++) {
        Base_Column* curr_col = select->col_head;

        if (selectQuery.second.at(i) == "*") {
            delete final_select;
            final_select = new Table(*select);
            break;
        }

        while (curr_col != NULL) {
            if (compareStrings(curr_col->label, selectQuery.second.at(i))) {
                final_select->addColumn(curr_col);
                break;
            }

            curr_col = curr_col->next_col;
        }

    }

    final_select->display();
    temp_select = final_select;
    delete select;

    return true;
}

bool Database::handleUpdateQuery(pair<string, vector<pair<string, string>>> updateQuery, pair<vector<tuple<string, string, string>>, string> whereQuery, bool whereCheck) {

    /*for (int i = 0; i < whereQuery.size(); i++) {
        cout << get<0>(whereQuery.at(i)) << "--" << get<1>(whereQuery.at(i)) << "--" << get<2>(whereQuery.at(i)) << endl;
    }*/

    auto table = getTable(updateQuery.first);
    if (table == NULL) {
        status.at(7) = true;
        cout << "Invalid Updation Input." << endl;
        return false;
    }

    //if there is no WHERE statement
    if (!whereCheck) {
        for (int i = 0; i < updateQuery.second.size(); i++) {

            Base_Column* affected = table->getColumn(updateQuery.second.at(i).first);
            if (affected == NULL) {
                status.at(7) = true;
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

        if (whereQuery.second == "or" || whereQuery.second == "null" || whereQuery.second == "") {
            for (int j = 0; j < whereQuery.first.size(); j++) {

                Base_Column* col = table->getColumn(std::get<0>(whereQuery.first.at(j)));
                Base_Column* affected = table->getColumn(updateQuery.second.at(i).first);

                if (col == NULL || affected == NULL) {
                    status.at(7) = true;
                    cout << "Invalid Updation Input." << endl;
                    return false;
                }

                Base_Node* affected_head = affected->getHead();
                Base_Node* head = col->getHead();

                Base_Node* target = convert(col->getHead()->getType(), std::get<2>(whereQuery.first.at(j)));
                Base_Node* replace = convert(affected->getHead()->getType(), updateQuery.second.at(i).second);

                while (head != NULL) {
                    if ((std::get<1>(whereQuery.first.at(j)) == "=") && (*head == *target)) {
                        if (!(affected->validate(replace))) {
                            return false;
                        }
                        affected_head->setValue(replace);
                    }
                    else if ((std::get<1>(whereQuery.first.at(j)) == "!=") && (*head != *target)) {
                        if (!(affected->validate(replace))) {
                            return false;
                        }
                        affected_head->setValue(replace);
                    }
                    else if ((std::get<1>(whereQuery.first.at(j)) == ">") && (*head > *target)) {
                        if (!(affected->validate(replace))) {
                            return false;
                        }
                        affected_head->setValue(replace);
                    }
                    else if ((std::get<1>(whereQuery.first.at(j)) == "<") && (*head < *target)) {
                        if (!(affected->validate(replace))) {
                            return false;
                        }
                        affected_head->setValue(replace);
                    }
                    else if ((std::get<1>(whereQuery.first.at(j)) == ">=") && (*head >= *target)) {
                        if (!(affected->validate(replace))) {
                            return false;
                        }
                        affected_head->setValue(replace);
                    }
                    else if ((std::get<1>(whereQuery.first.at(j)) == "<=") && (*head <= *target)) {
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
        else if (whereQuery.second == "and") {

            pair<vector<tuple<string, string, string>>, string> inverse = whereQuery;
            inverse.second = "or";

            for (int i = 0; i < inverse.first.size(); i++) {
                if (get<1>(inverse.first.at(i)) == "=") {
                    get<1>(inverse.first.at(i)) = "!=";
                }
                else if (get<1>(inverse.first.at(i)) == "!=") {
                    get<1>(inverse.first.at(i)) = "=";
                }
                else if (get<1>(inverse.first.at(i)) == ">") {
                    get<1>(inverse.first.at(i)) = "<=";
                }
                else if (get<1>(inverse.first.at(i)) == "<") {
                    get<1>(inverse.first.at(i)) = ">=";
                }
                else if (get<1>(inverse.first.at(i)) == ">=") {
                    get<1>(inverse.first.at(i)) = "<";
                }
                else if (get<1>(inverse.first.at(i)) == "<=") {
                    get<1>(inverse.first.at(i)) = ">";
                }
            }


            Base_Column* affected = table->getColumn(updateQuery.second.at(i).first);
            if (affected == NULL) {
                status.at(7) = true;
                cout << "Invalid Updation Input." << endl;
                return false;
            }

            Base_Node* affected_head = affected->getHead();
            Base_Node* replace = convert(affected->getHead()->getType(), updateQuery.second.at(i).second);

            Queue<Base_Node*> queue;
            Base_Node* temp = affected_head;
            while (temp != NULL) {
                queue.enQueue(temp);
                temp = temp->getDown();
            }

            for (int j = 0; j < inverse.first.size(); j++) {
                Base_Column* col = table->getColumn(std::get<0>(inverse.first.at(j)));

                affected_head = affected->getHead();

                if (col == NULL) {
                    status.at(7) = true;
                    cout << "Invalid Updation Input." << endl;
                    return false;
                }

                Base_Node* head = col->getHead();

                Base_Node* target = convert(col->getHead()->getType(), std::get<2>(inverse.first.at(j)));

                while (head != NULL) {
                    if ((std::get<1>(inverse.first.at(j)) == "=") && (*head == *target)) {
                        queue.remove(affected_head);
                    }
                    else if ((std::get<1>(inverse.first.at(j)) == "!=") && (*head != *target)) {
                        queue.remove(affected_head);
                    }
                    else if ((std::get<1>(inverse.first.at(j)) == ">") && (*head > *target)) {
                        queue.remove(affected_head);
                    }
                    else if ((std::get<1>(inverse.first.at(j)) == "<") && (*head < *target)) {
                        queue.remove(affected_head);
                    }
                    else if ((std::get<1>(inverse.first.at(j)) == ">=") && (*head >= *target)) {
                        queue.remove(affected_head);
                    }
                    else if ((std::get<1>(inverse.first.at(j)) == "<=") && (*head <= *target)) {
                        queue.remove(affected_head);
                    }

                    affected_head = affected_head->getDown();
                    head = head->getDown();
                }

            }

            while (queue.size != 0) {
                Base_Node* temp2 = queue.peek();
                if (!(affected->validate(replace))) {
                    return false;
                }
                temp2->setValue(replace);
                queue.deQueue();
            }
        }


    }

    return true;
}

bool Database::handleAlterQuery(pair<string, vector<pair<string, string>>> alterQuery) {

    auto table = getTable(alterQuery.first);

    if (table == NULL) {
        status.at(8) = true;
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

bool Database::handleDeleteQuery(string deleteQuery, pair<vector<tuple<string, string, string>>, string> whereQuery, bool whereCheck) {

    auto table = getTable(deleteQuery);

    if (table == NULL) {
        status.at(8) = true;
        cout << "Invalid Deletion Input." << endl;
        return false;
    }

    if (!whereCheck) {
        table->deleteAllRows();

        return true;
    }


    if (whereQuery.second == "or" || whereQuery.second == "null" || whereQuery.second == "") {
        whereDeleteUtil(table, whereQuery);
    }
    else if (whereQuery.second == "and") {
        pair<vector<tuple<string, string, string>>, string> inverse = whereQuery;
        inverse.second = "or";

        for (int i = 0; i < inverse.first.size(); i++) {
            if (get<1>(inverse.first.at(i)) == "=") {
                get<1>(inverse.first.at(i)) = "!=";
            }
            else if (get<1>(inverse.first.at(i)) == "!=") {
                get<1>(inverse.first.at(i)) = "=";
            }
            else if (get<1>(inverse.first.at(i)) == ">") {
                get<1>(inverse.first.at(i)) = "<=";
            }
            else if (get<1>(inverse.first.at(i)) == "<") {
                get<1>(inverse.first.at(i)) = ">=";
            }
            else if (get<1>(inverse.first.at(i)) == ">=") {
                get<1>(inverse.first.at(i)) = "<";
            }
            else if (get<1>(inverse.first.at(i)) == "<=") {
                get<1>(inverse.first.at(i)) = ">";
            }
        }

        whereAddUtil(table, inverse);

        auto current = table_list.head;
        while (!compareStrings(current->data->label, table->label)) {

            current = current->next;
        }
        delete current->data;

        current->data = table;

    }

    return true;

}

bool Database::handleDropQuery(string dropTableQuery) {

    auto table = getTable(dropTableQuery);

    if (table == NULL) {
        status.at(9) = true;
        cout << "Invalid Drop Query.\n";
        return false;
    }

    table_list.deleteNode(table);

    return true;

}

bool Database::whereDeleteUtil(Table* table, pair<vector<tuple<string, string, string>>, string> whereQuery) {

    for (int i = 0; i < whereQuery.first.size(); i++) {
        Base_Column* col = table->getColumn(get<0>(whereQuery.first.at(i)));
        if (col == NULL) {
            status.at(10) = true;
            cout << "Invalid Where Query." << endl;
            return false;
        }

        Base_Node* target = convert(col->getHead()->getType(), get<2>(whereQuery.first.at(i)));

        Base_Node* current = col->getHead();
        while (current != NULL) {
            Base_Node* temp = current->getDown();
            if ((std::get<1>(whereQuery.first.at(i)) == "=") && (*current == *target)) {
                table->deleteRow(col, current);
            }
            else if ((std::get<1>(whereQuery.first.at(i)) == "!=") && (*current != *target)) {
                table->deleteRow(col, current);
            }
            else if ((std::get<1>(whereQuery.first.at(i)) == ">") && (*current > *target)) {
                table->deleteRow(col, current);
            }
            else if ((std::get<1>(whereQuery.first.at(i)) == "<") && (*current < *target)) {
                table->deleteRow(col, current);
            }
            else if ((std::get<1>(whereQuery.first.at(i)) == ">=") && (*current >= *target)) {
                table->deleteRow(col, current);
            }
            else if ((std::get<1>(whereQuery.first.at(i)) == "<=") && (*current <= *target)) {
                table->deleteRow(col, current);
            }

            current = temp;
        }

    }

    return true;
}

bool Database::whereAddUtil(Table*& table, pair<vector<tuple<string, string, string>>, string> whereQuery) {

    Table* temp_table = new Table(table->metadata);

    for (int i = 0; i < whereQuery.first.size(); i++) {
        Base_Column* col = table->getColumn(get<0>(whereQuery.first.at(i)));

        if (col == NULL) {
            status.at(10) = true;
            cout << "Invalid Where Query." << endl;
            return false;
        }

        Base_Node* target = convert(col->getHead()->getType(), get<2>(whereQuery.first.at(i)));

        Base_Node* current = col->getHead();
        while (current != NULL) {
            Queue<Base_Node*> queue;

            Base_Node* iterate = current;

            while (iterate->left != NULL) {
                iterate = iterate->left;
            }

            while (iterate != NULL) {
                queue.enQueue(iterate->getCopy());
                iterate = iterate->right;
            }

            Base_Node* temp = current->getDown();
            if ((std::get<1>(whereQuery.first.at(i)) == "=") && (*current == *target)) {
                temp_table->addRow(queue, temp_table->col_head);
                table->deleteRow(col, current);
            }
            else if ((std::get<1>(whereQuery.first.at(i)) == "!=") && (*current != *target)) {
                temp_table->addRow(queue, temp_table->col_head);
                table->deleteRow(col, current);
            }
            else if ((std::get<1>(whereQuery.first.at(i)) == ">") && (*current > *target)) {
                temp_table->addRow(queue, temp_table->col_head);
                table->deleteRow(col, current);
            }
            else if ((std::get<1>(whereQuery.first.at(i)) == "<") && (*current < *target)) {
                temp_table->addRow(queue, temp_table->col_head);
                table->deleteRow(col, current);
            }
            else if ((std::get<1>(whereQuery.first.at(i)) == ">=") && (*current >= *target)) {
                temp_table->addRow(queue, temp_table->col_head);
                table->deleteRow(col, current);
            }
            else if ((std::get<1>(whereQuery.first.at(i)) == "<=") && (*current <= *target)) {
                temp_table->addRow(queue, temp_table->col_head);
                table->deleteRow(col, current);
            }

            current = temp;
        }

    }

    table = temp_table;

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

int temp_rows;
int temp_keys;

void Database::pull(){

    QString db_name = QString::fromStdString(name);
    db_name += ".dat";
    QFile file(db_name);

    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);

        in >> username;
        in >> password;

        while(!in.atEnd()){

            pair<string, vector<pair<string, string>>> query1;
            map<string, string> keys;

            in >> query1.first;

            int num_of_cols, num_of_rows, num_of_keys;
            in >> num_of_cols;
            in >> num_of_rows;

            query1.second.resize(num_of_cols);
            in >> query1.second;

            in >> num_of_keys;
            temp_keys = num_of_keys;
            in >> keys;

            handleCreateQuery(query1, keys);

            auto current = table_list.head;
            while(current->next != NULL){
                current = current->next;
            }

            temp_rows = num_of_rows;
            Table* t1 = current->data;
            in >> *t1;
        }

        file.close();

    }
    else{
        cout << "Cannot open the file for reading.\n";
    }

}

void Database::commit(){

    QString db_name = QString::fromStdString(name);
    db_name += ".dat";
    QFile file(db_name);

    if (file.open(QIODevice::WriteOnly | QFile::Truncate)) {
        QDataStream out(&file);

        out << username;
        out << password;

        auto current = table_list.head;

        while(current != 0){
            out << *(current->data);
            current = current->next;
        }

        file.close();
    } else {
        cout << "Cannot open the file for writing." << endl;
    }


}

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

    if (type == "float" || type == "f") {
        float data = stof(value);
        return (new Node<float>(data));
    }
    else if (type == "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >" || type == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE") {
        return (new Node<string>(value));
    }
    else if (type == "char" || type == "c") {
        char data = value.at(0);
        return (new Node<char>(data));
    }
    else if (type == "bool" || type == "b") {
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

tuple<string, string, string> Database::parseFk(string s1) {
    int i = 0;
    tuple<std::string, std::string, std::string> t1;
    string col, table, refCol;

    while (s1[i] != '.') {
        col = col + s1[i];
        i++;
    }
    i++;
    while (s1[i] != '(') {
        table = table + s1[i];
        i++;
    }
    i++;
    while (s1[i] != ')') {
        refCol = refCol + s1[i];
        i++;
    }

    t1 = make_tuple(col, table, refCol);
    return t1;

}

