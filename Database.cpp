#include "Database.h"

//ignore this method. It is only used to intialize the t1 and t2 pointers.
Database::Database(Table& table1, Table& table2){

    table_list.insertToTail(&table1);
    table_list.insertToTail(&table2);

}


Database::Database(string name){

    this->name = name;
    t1 = t2 = temp = NULL;

    //Database::pull() should be used after this to pull contents from file :)
}

int temp_rows;

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

            in >> query1.first;

            int num_of_cols, num_of_rows;
            in >> num_of_cols;
            in >> num_of_rows;

            query1.second.resize(num_of_cols);
            in >> query1.second;

            Table* t1 = new Table(query1);
            temp_rows = num_of_rows;
            in >> *t1;

            table_list.insertToTail(t1);

        }

        file.close();

    }
    else{
        cout << "Cannot open the file for reading.\n";
    }

}


void Database::join(){

    cout << "\nJoining Employees and Departments..." << endl;
    temp = t1->join(&(*t1)["Dept_ID"], &(*t2)["ID"]);
    temp->display();

}

void Database::commit(){

    QString db_name = QString::fromStdString(name);
    db_name += ".dat";
    QFile file(db_name);

    if (file.open(QIODevice::WriteOnly)) {
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

void Database::addTable(Table* table){

    table_list.insertToTail(table);

}

void Database::printTables(){

    auto current = table_list.head;

    while(current != NULL){
        current->data->display();
        current = current->next;
    }

}
