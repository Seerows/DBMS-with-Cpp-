#include "Database.h"

Database::Database(Table& table1, Table& table2){

    t1 = &table1;
    t2 = &table2;

    QFile file("Databases.dat");
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);

        out << table1;
        out << table2;
        file.close();
    } else {
        cout << "Cannot open the file for writing." << endl;
    }

}

int temp_rows;

Database::Database(){

    QFile file("Databases.dat");
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);

        pair<string, vector<pair<string, string>>> query1;

        in >> query1.first;

        int num_of_cols, num_of_rows;
        in >> num_of_cols;
        in >> num_of_rows;

        query1.second.resize(num_of_cols);
        in >> query1.second;

        t1 = new Table(query1);
        temp_rows = num_of_rows;
        in >> *t1;

        pair<string, vector<pair<string, string>>> query2;
        in >> query2.first;

        in >> num_of_cols;
        in >> num_of_rows;

        query2.second.resize(num_of_cols);
        in >> query2.second;

        t2 = new Table(query2);
        temp_rows = num_of_rows;
        in >> *t2;

        file.close();

    }
    else{
        cout << "Cannot open the file for reading.\n";
    }

}


void Database::join(){

    cout << "\nJoining Employees and Departments..." << endl;
    temp = t1->join(&(*t1)["Dept_ID"], &(*t2)["ID"]);

}

void Database::commit(){

    QFile file("Databases.dat");
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);

        out << *t1;
        out << *t2;
        file.close();
    } else {
        cout << "Cannot open the file for writing." << endl;
    }


}
