#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include "Table.h"
#include "Database.h"
#include "Dependencies.h"
using namespace std;

void writingtoFile();
void readingFromFile();

int main(int argc, char *argv[]){

//the following 4 lines make a new user and create a new file without any tables
    Database d1("Mussab_DB");
    d1.username = "Mussab";
    d1.password = "Mussab123";
    d1.commit();


//the following code reads all the contents of the Mussab_DB.dat file and stores them in the appropriate variables.
//you have to first run the above 4 lines of code to actually create the file.
//    Database d1("Mussab_DB");
//    d1.pull();
//    cout << "Name: " << d1.name << endl;
//    cout << "Username: " << d1.username << endl;
//    cout << "Password: " << d1.password << endl << endl;
//    d1.printTables();

    return 0;

}


//ignore these functions

void writingtoFile(){

    pair<string, vector<pair<string, string>>> query;

    query.first = "Employees";
    query.second.push_back(pair<string, string>("int", "ID"));
    query.second.push_back(pair<string, string>("class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >", "Name"));
    query.second.push_back(pair<string, string>("char", "Grade"));
    query.second.push_back(pair<string, string>("int", "Dept_ID"));

    Table employees(query);

    employees.addRow(5, string("Row1"), 'A', 2);
    employees.addRow(6, string("Row2"), 'C', 1);
    employees.addRow(1, string("Row3"), 'D', 4);
    employees.addRow(4, string("Row4"), 'E', 3);
    employees.addRow(7, string("Row5"), 'F', 1);

    employees.addColumn(pair<string, string>("bool", "Employed"));
    employees.addColumn(pair<string, string>("float", "Salary"));

    employees.addRow(9, string("Row6"), 'U', 2, true, 900.2f);

    employees.display();
    cout << endl;

    pair<string, vector<pair<string, string>>> query2;

    query2.first = "Departments";
    query2.second.push_back(pair<string, string>("int", "ID"));
    query2.second.push_back(pair<string, string>("class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >", "Name"));
    query2.second.push_back(pair<string, string>("float", "Pay"));

    Table departments(query2);

    departments.addRow(1, string("CS"), 57.5f);
    departments.addRow(2, string("EE"), 39.4f);
    departments.addRow(3, string("AI"), 47.2f);
    departments.addRow(4, string("CYS"), 98.3f);

    departments.display(); 

    Database d1("Arqam_DB");   //the name of the database will be taken from the file containing the list of all Databases.
    d1.username = "Arqam";
    d1.password = "Arqam123";
    d1.addTable(&employees);
    d1.addTable(&departments);
    d1.commit();
}

void readingFromFile(){

    Database d1("Arqam_DB");
    d1.pull();                  //pulls all the contents of the Database from the file.
    cout << "Name: " << d1.name << endl;
    cout << "Username: " << d1.username << endl;
    cout << "Password: " << d1.password << endl << endl;
    d1.printTables();

}
